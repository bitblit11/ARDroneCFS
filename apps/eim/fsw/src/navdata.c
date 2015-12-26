/*==============================================================================
Copyright (c) 2015, Windhover Labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of EIM nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>
#include "events.h"
#include "cfe.h"
#include "eim_platform_cfg.h"
#include "app.h"
#include <string.h>
#include "navdata.h"
#include "navcmds.h"



/* Local variables */
int8        			tempBuffer[EIM_MAX_NAV_BUFFER_SIZE];
uint32					navSequence;
struct sockaddr_in 		addrNav;



void EIM_NavDataTlm_delete_callback(void);
void EIM_ResetTlmConnection(void);
int32 EIM_ReadTelem(void);
boolean EIM_GetMaskFromState( uint32 state, uint32 mask );



void EIM_NavDataTlmMain(void)
{
	int32 Status = CFE_SUCCESS;
	struct sockaddr_in 		addrNav;
    uint32 RunStatus = CFE_ES_APP_RUN;

	Status = CFE_ES_RegisterChildTask();
	if(Status != CFE_SUCCESS)
	{
		CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
			"EIM: Failed to register telemetry listener task.");

		CFE_ES_ExitChildTask();
	}

    /*
    ** Install the delete handler
    */
    OS_TaskInstallDeleteHandler((void *)(&EIM_NavDataTlm_delete_callback));

    /* Create sockets */
    EIM_AppData.NavSocketID = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(EIM_AppData.NavSocketID < 0)
    {
    	CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,"EIM: Create Nav telemetry socket failed = %d", errno);
		CFE_ES_ExitChildTask();
    }
    //EIM_AppData.ATCmdSocketID = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //if(EIM_AppData.ATCmdSocketID < 0)
    //{
    //	CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,"EIM: Create Nav command socket failed = %d", errno);
	//	CFE_ES_ExitChildTask();
    //}

	memset((char *) &addrNav, 0, sizeof(addrNav));
	addrNav.sin_family      = AF_INET;
    addrNav.sin_port        = htons(EIM_NAV_DATA_PORT+100);
    addrNav.sin_addr.s_addr = htonl(INADDR_ANY);

	OS_printf("EIM: Binding NAV socket.\n");
	if ( bind(EIM_AppData.NavSocketID, (struct sockaddr *) &addrNav,
			sizeof(addrNav)) < 0)
	{
		CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
                          "EIM: Failed to bind NAV command socket.  errno: %d", errno);
		CFE_ES_ExitChildTask();
	}

	/* Set addresses */
	//bzero((char *) &EIM_AppData.CmdSocketAddress, sizeof(EIM_AppData.CmdSocketAddress));
	//EIM_AppData.CmdSocketAddress.sin_family      = AF_INET;
	//EIM_AppData.CmdSocketAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
	//EIM_AppData.CmdSocketAddress.sin_port        = htons(0);

	//bzero((char *) &EIM_AppData.CmdARDroneAddress, sizeof(EIM_AppData.CmdARDroneAddress));
	//EIM_AppData.CmdARDroneAddress.sin_family      = AF_INET;
	//EIM_AppData.CmdARDroneAddress.sin_addr.s_addr = inet_addr(EIM_WIFI_IP);
	//EIM_AppData.CmdARDroneAddress.sin_port        = htons(EIM_AT_PORT);

	//if ( bind(EIM_AppData.ATCmdSocketID,
    //          (struct sockaddr *) &EIM_AppData.CmdSocketAddress,
	//		  sizeof(EIM_AppData.CmdSocketAddress)) < 0)
	//{
	//	CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
    //                      "EIM: Failed to bind command socket.  errno: %d", errno);
	//	CFE_ES_ExitChildTask();
	//}
//
	//EIM_InitATCmdSockets();

	OS_TaskDelay(100);
	EIM_ResetTlmConnection();

	if(CFE_ES_RunLoop(&RunStatus) == FALSE)
	{
		EIM_AppData.Hk.NavDataState = EIM_NAVDATA_FAILED;
	}
	else
	{
		EIM_AppData.Hk.NavDataState = EIM_NAVDATA_ENABLED;
	}

	while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
		EIM_ReadTelem();

		if(EIM_AppData.Hk.ARDroneState.CommWatchdog == TRUE)
		{
			if(EIM_AppData.Hk.ARDrone2TimedOut == FALSE)
			{
				CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR, "EIM: ARDrone timedout.  Resetting watchdog.");
				EIM_AppData.Hk.ARDrone2TimedOut = TRUE;
			}
			EIM_cmdComWdg();
		}
		else
		{
			if(EIM_AppData.Hk.ARDrone2TimedOut == TRUE)
			{
				CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR, "EIM: ARDrone watchdog reset.");
				EIM_AppData.Hk.ARDrone2TimedOut = FALSE;
			}
		}
    }

	close(EIM_AppData.ATCmdSocketID);
	close(EIM_AppData.NavSocketID);
	EIM_AppData.ATCmdSocketID = 0;
	EIM_AppData.NavSocketID = 0;
	EIM_AppData.Hk.NavDataState = EIM_NAVDATA_DISABLED;

    CFE_ES_ExitApp(RunStatus);
}



boolean EIM_GetMaskFromState( uint32 state, uint32 mask )
{
  return state & mask ? TRUE : FALSE;
}



void EIM_ResetTlmConnection(void)
{
	int status = 0;
	struct sockaddr_in si_tmp;
	char cBuf[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int len=14;

	OS_printf("EIM: Sending reset message.\n");

    memset((char *) &si_tmp, 0, sizeof(si_tmp));
    si_tmp.sin_family      = AF_INET;
    inet_aton(EIM_WIFI_IP, &si_tmp.sin_addr);
    si_tmp.sin_port        = htons(EIM_NAV_DATA_PORT);

	status = sendto(EIM_AppData.NavSocketID, cBuf, len, 0,
				(struct sockaddr *) &si_tmp, sizeof(si_tmp) );
	if ( status < 0 )
	{
		CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR, "EIM: Failed to send NAVDATA reset.  errno: %d", errno);
		CFE_ES_ExitChildTask();
	}
	else
	{
		OS_printf("EIM: Reset message sent.\n");
	}
}



NavData_Option_t * EIM_NavdataUnpackOption(NavData_Option_t* navdata_ptr,
		CFE_SB_Msg_t *unpack_ptr,
        uint32 unpack_opt_size)
{
    uint32 srcSize = navdata_ptr->size - 4;
    uint32 destSize = unpack_opt_size - CFE_SB_TLM_HDR_SIZE;

    uint32 minSize = (srcSize < destSize ? srcSize : destSize);

    char * destPtr = (char *)unpack_ptr + CFE_SB_TLM_HDR_SIZE;
    char * srcPtr = (char *)navdata_ptr + 4;

    memcpy(destPtr, srcPtr, minSize);

    char * nextOptPtr = (char *)navdata_ptr + navdata_ptr->size;
    return ((NavData_Option_t *) nextOptPtr);
}



boolean EIM_NavDataUnpackAll(NavData_t* navdata, uint32* cks)
{
	boolean success = TRUE;
	NavData_Cks_t navdata_cks;
	navdata_cks.cks = 0;

	NavData_Option_t* navdata_option_ptr;

	navdata_option_ptr = (NavData_Option_t*) &navdata->options[0];

	EIM_AppData.nd_seq   			= navdata->sequence;
	EIM_AppData.Hk.VisionDefined  	= navdata->vision_defined;

	while( navdata_option_ptr != 0 )
	{
		// Check if we have a valid option
		if( navdata_option_ptr->size == 0 )
		{
			/* TODO:  Replace this with an error event. */
			//PRINT("One option (%d) is not a valid option because its size is zero\n", navdata_option_ptr->tag);
			navdata_option_ptr = 0;
			success = FALSE;
		}
		else
		{
			switch( navdata_option_ptr->tag )
			{
				case ARDRONE2_NAVDATA_DEMO_TAG:
				{
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
							(CFE_SB_Msg_t *) &EIM_AppData.navdata_demo ,
							sizeof(EIM_AppData.navdata_demo) );

					EIM_AppData.Hk.navdata_demo_count++;
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.navdata_demo);

					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_demo);
					break;
				}

				case ARDRONE2_NAVDATA_TIME_TAG:
				{
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
							(CFE_SB_Msg_t *) &EIM_AppData.navdata_time,
							sizeof(EIM_AppData.navdata_time) );

					EIM_AppData.Hk.navdata_time_count++;
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.navdata_time);
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_time);
					break;
				}

				case ARDRONE2_NAVDATA_RAW_MEASURES_TAG:
				{
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_raw_measures ,
                    sizeof(EIM_AppData.navdata_raw_measures) );

					EIM_AppData.Hk.navdata_raw_measures_count++;
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.navdata_raw_measures);
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_raw_measures);

			        EIM_AppData.ImuMsg.SampleCnt = 1;
			        EIM_AppData.ImuMsg.ImuSample[0].MsgAccData[0] = EIM_AppData.navdata_raw_measures.raw_accs[0];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgAccData[1] = EIM_AppData.navdata_raw_measures.raw_accs[1];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgAccData[2] = EIM_AppData.navdata_raw_measures.raw_accs[2];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgRateData[0] = EIM_AppData.navdata_raw_measures.raw_gyros[0];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgRateData[1] = EIM_AppData.navdata_raw_measures.raw_gyros[1];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgRateData[2] = EIM_AppData.navdata_raw_measures.raw_gyros[2];
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.ImuMsg);
			        EIM_AppData.ImuMsg.ImuSample[0].TimeStamp = CFE_TIME_GetTime();
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.ImuMsg);
					break;
				}

				case ARDRONE2_NAVDATA_PHYS_MEASURES_TAG:
				{
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_phys_measures ,
                    sizeof(EIM_AppData.navdata_phys_measures) );

					EIM_AppData.Hk.navdata_phys_measures_count++;
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.navdata_phys_measures);
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_phys_measures);

			        EIM_AppData.ImuMsg.SampleCnt = 1;
			        EIM_AppData.ImuMsg.ImuSample[0].MsgAccData[0] = EIM_AppData.navdata_phys_measures.phys_accs[0];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgAccData[1] = EIM_AppData.navdata_phys_measures.phys_accs[1];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgAccData[2] = EIM_AppData.navdata_phys_measures.phys_accs[2];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgRateData[0] = EIM_AppData.navdata_phys_measures.phys_gyros[0];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgRateData[1] = EIM_AppData.navdata_phys_measures.phys_gyros[1];
			        EIM_AppData.ImuMsg.ImuSample[0].MsgRateData[2] = EIM_AppData.navdata_phys_measures.phys_gyros[2];
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.ImuMsg);
			        EIM_AppData.ImuMsg.ImuSample[0].TimeStamp = CFE_TIME_GetTime();
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.ImuMsg);

					break;
				}

				case ARDRONE2_NAVDATA_GYROS_OFFSETS_TAG:
				{
					EIM_AppData.Hk.navdata_gyro_offsets_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_gyro_offsets ,
                    sizeof(EIM_AppData.navdata_gyro_offsets) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_gyro_offsets);
					break;
				}

				case ARDRONE2_NAVDATA_EULER_ANGLES_TAG:
				{
					EIM_AppData.Hk.navdata_euler_angles_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_euler_angles ,
                    sizeof(EIM_AppData.navdata_euler_angles) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_euler_angles);
					break;
				}

				case ARDRONE2_NAVDATA_REFERENCES_TAG:
				{
					EIM_AppData.Hk.navdata_references_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_references ,
                    sizeof(EIM_AppData.navdata_references) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_references);
					break;
				}

				case ARDRONE2_NAVDATA_TRIMS_TAG:
				{
					EIM_AppData.Hk.navdata_trims_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_trims,
                    sizeof(EIM_AppData.navdata_trims));
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_trims);
                    break;
				}

				case ARDRONE2_NAVDATA_RC_REFERENCES_TAG:
				{
					EIM_AppData.Hk.navdata_rc_references_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_rc_references ,
                    sizeof(EIM_AppData.navdata_rc_references) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_rc_references);
					break;
				}

				case ARDRONE2_NAVDATA_PWM_TAG:
				{
					EIM_AppData.Hk.navdata_pwm_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_pwm ,
                    sizeof(EIM_AppData.navdata_pwm) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_pwm);
					break;
				}

				case ARDRONE2_NAVDATA_ALTITUDE_TAG:
				{
					EIM_AppData.Hk.navdata_altitude_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_altitude ,
                    sizeof(EIM_AppData.navdata_altitude) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_altitude);
					break;
				}

				case ARDRONE2_NAVDATA_VISION_RAW_TAG:
				{
					EIM_AppData.Hk.navdata_vision_raw_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_vision_raw ,
                    sizeof(EIM_AppData.navdata_vision_raw) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_vision_raw);
					break;
				}

				case ARDRONE2_NAVDATA_VISION_OF_TAG:
				{
					EIM_AppData.Hk.navdata_vision_of_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_vision_of ,
                    sizeof(EIM_AppData.navdata_vision_of) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_vision_of);
					break;
				}

				case ARDRONE2_NAVDATA_VISION_TAG:
				{
					EIM_AppData.Hk.navdata_vision_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_vision ,
                    sizeof(EIM_AppData.navdata_vision) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_vision);
					break;
				}

				case ARDRONE2_NAVDATA_VISION_PERF_TAG:
				{
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
							(CFE_SB_Msg_t *) &EIM_AppData.navdata_vision_perf,
							sizeof(EIM_AppData.navdata_vision_perf) );

					EIM_AppData.Hk.navdata_vision_perf_count++;
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.navdata_vision_perf);
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_vision_perf);
					break;
				}

				case ARDRONE2_NAVDATA_TRACKERS_SEND_TAG:
				{
					EIM_AppData.Hk.navdata_trackers_send_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_trackers_send ,
                    sizeof(EIM_AppData.navdata_trackers_send) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_trackers_send);
					break;
				}

				case ARDRONE2_NAVDATA_VISION_DETECT_TAG:
				{
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
							(CFE_SB_Msg_t *) &EIM_AppData.navdata_vision_detect,
							sizeof(EIM_AppData.navdata_vision_detect) );

					EIM_AppData.Hk.navdata_vision_detect_count++;
			        CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.navdata_vision_detect);
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_vision_detect);
					break;
				}

				case ARDRONE2_NAVDATA_WATCHDOG_TAG:
				{
					EIM_AppData.Hk.navdata_watchdog_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_watchdog ,
                    sizeof(EIM_AppData.navdata_watchdog) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_watchdog);
					break;
				}

				case ARDRONE2_NAVDATA_ADC_DATA_FRAME_TAG:
				{
					EIM_AppData.Hk.navdata_adc_data_frame_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_adc_data_frame ,
                    sizeof(EIM_AppData.navdata_adc_data_frame) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_adc_data_frame);
					break;
				}

				case ARDRONE2_NAVDATA_VIDEO_STREAM_TAG:
				{
					EIM_AppData.Hk.navdata_video_stream_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_video_stream ,
                    sizeof(EIM_AppData.navdata_video_stream) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_video_stream);
					break;
				}

				case ARDRONE2_NAVDATA_GAMES_TAG:
				{
					EIM_AppData.Hk.navdata_games_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_games ,
                    sizeof(EIM_AppData.navdata_games) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_games);
					break;
				}

				case ARDRONE2_NAVDATA_PRESSURE_RAW_TAG:
				{
					EIM_AppData.Hk.navdata_pressure_raw_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_pressure_raw ,
                    sizeof(EIM_AppData.navdata_pressure_raw) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_pressure_raw);
					break;
				}

				case ARDRONE2_NAVDATA_MAGNETO_TAG:
				{
					EIM_AppData.Hk.navdata_magneto_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_magneto ,
                    sizeof(EIM_AppData.navdata_magneto) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_magneto);
					break;
				}

				case ARDRONE2_NAVDATA_WIND_TAG:
				{
					EIM_AppData.Hk.navdata_wind_speed_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_wind_speed ,
                    sizeof(EIM_AppData.navdata_wind_speed) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_wind_speed);
					break;
				}

				case ARDRONE2_NAVDATA_KALMAN_PRESSURE_TAG:
				{
					EIM_AppData.Hk.navdata_kalman_pressure_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_kalman_pressure ,
                    sizeof(EIM_AppData.navdata_kalman_pressure) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_kalman_pressure);
					break;
				}

				case ARDRONE2_NAVDATA_HDVIDEO_STREAM_TAG:
				{
					EIM_AppData.Hk.navdata_hdvideo_stream_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_hdvideo_stream ,
                    sizeof(EIM_AppData.navdata_hdvideo_stream) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_hdvideo_stream);
					break;
				}

				case ARDRONE2_NAVDATA_WIFI_TAG:
				{
					EIM_AppData.Hk.navdata_wifi_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_wifi ,
                    sizeof(EIM_AppData.navdata_wifi) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_wifi);
					break;
				}

				case ARDRONE2_NAVDATA_ZIMMU_3000_TAG:
				{
					EIM_AppData.Hk.navdata_zimmu_3000_count++;
					navdata_option_ptr = EIM_NavdataUnpackOption( navdata_option_ptr,
                    (CFE_SB_Msg_t *) &EIM_AppData.navdata_zimmu_3000 ,
                    sizeof(EIM_AppData.navdata_zimmu_3000) );
					CFE_SB_SendMsg((CFE_SB_Msg_t*)&EIM_AppData.navdata_zimmu_3000);
					break;
				}

				case ARDRONE2_NAVDATA_CKS_TAG:
				{
					//navdata_option_ptr = ARDrone2_NavdataUnpackOption( navdata_option_ptr,
                    //(NavDataHeader_t *) &navdata_unpacked->demo ,
                    //sizeof(navdata_unpacked->demo) );
					*cks = navdata_cks.cks;
					navdata_option_ptr = 0; // End of structure
					break;
				}

				default:
				{
					// TODO:  Replace the following with an error event.
					//PRINT("Tag %d is an unknown navdata option tag\n", (int) navdata_option_ptr->tag);
					navdata_option_ptr = (NavData_Option_t*)(((uint32)navdata_option_ptr) + navdata_option_ptr->size);
					break;
				}
			}
		}
	}

	return success;
}



uint32 EIM_NavDataComputeCks( int8* nv, int32 size )
{
	int32 i;
	uint32 cks;
	uint32 temp;

	cks = 0;

	for( i = 0; i < size; i++ )
	{
		temp = nv[i];
		cks += temp;
	}

	return cks;
};



int32 EIM_ReadTelem(void)
{
    uint32 addr_len = 0;
	int32 len = 0;
	uint32 navdata_cks = 0;
	uint32 cks = 0;
	int32 size = 0;
	int32 status = 0;

	addr_len = sizeof(addrNav);
    int8 buffer[EIM_MAX_NAV_BUFFER_SIZE];

    /* Receive data */
    len = recvfrom(EIM_AppData.NavSocketID, buffer, EIM_MAX_NAV_BUFFER_SIZE,
    		0,	(struct sockaddr *) &addrNav, (socklen_t*)&addr_len);
    if (len < 0)
	{
		CFE_EVS_SendEvent(EIM_TELEM_SOCKET_READ_ERR_EID, CFE_EVS_ERROR,
			"EIM:  Telem socket read failed.  errno: %i", errno);
		status = -1;
		goto end_of_function;
	}
	else
	{
		if(len > 0)
		{
			NavData_t *pNavData = (NavData_t *)buffer;
			if( pNavData->header == NAVDATA_HEADER )
			{
				memcpy(&EIM_AppData.Hk.ARDroneState, &pNavData->ardrone_state, sizeof(EIM_AppData.Hk.ARDroneState));
				if( EIM_GetMaskFromState(pNavData->ardrone_state, ARDRONE2_NAVDATA_BOOTSTRAP) == TRUE)
				{
					EIM_AppData.Hk.NavDataState = EIM_NAVDATA_BOOTSTRAP;
					CFE_EVS_SendEvent(EIM_TELEM_INIT_EID, CFE_EVS_INFORMATION, "EIM:  NavData in Bootstrap mode.");
					EIM_configATCmd("general:navdata_demo", "TRUE");
				}
				else if( EIM_GetMaskFromState(pNavData->ardrone_state, ARDRONE2_COMMAND_MASK) == TRUE)
				{
					//EIM_AppData.Hk.NavDataState = EIM_NAVDATA_COMMAND_MASK;
					CFE_EVS_SendEvent(EIM_TELEM_INIT_EID, CFE_EVS_DEBUG,
						"EIM:  ARDRONE2_COMMAND_MASK == TRUE.");
					EIM_cmdSetControl(ACK_CONTROL_MODE);
				}
				else
				{
					EIM_AppData.Hk.NavDataState = EIM_NAVDATA_ENABLED;
				}

				//EIM_configATCmd("GENERAL:num_version_config", "TRUE");

				if( pNavData->sequence > navSequence )
				{
					/* Lock the mutex */
					//OS_MutSemTake(g_ARDrone2_AppData.NavDataMutexId);
					EIM_AppData.NavDataStale = FALSE;

					if(len >= (int32)sizeof(NavData_t))
					{
						EIM_NavDataUnpackAll((NavData_t*)buffer, &navdata_cks);
						cks = EIM_NavDataComputeCks(buffer,
								size - sizeof(NavData_Cks_t) );

						//FIXME: This is temporary.  Need a better solution.  Too many memcpy
						/* Send out Select message */
		  //                memcpy(&EIM_AppData.NavDataSelectMsg.demo,
		  //                       &EIM_AppData.NavDataDemoMsg.payload,
		  //                       sizeof(EIM_AppData.NavDataDemoMsg.payload));
		  //                memcpy(&EIM_AppData.NavDataSelectMsg.time,
		  //                       &EIM_AppData.NavDataUnpacked.time,
		  //                       sizeof(EIM_AppData.NavDataUnpacked.time));
		  //                memcpy(&EIM_AppData.NavDataSelectMsg.mag,
		  //                       &EIM_AppData.NavDataUnpacked.magneto,
		  //                       sizeof(EIM_AppData.NavDataUnpacked.magneto));

		  //                CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&EIM_AppData.NavDataSelectMsg);
		  //                CFE_SB_SetMsgId((CFE_SB_Msg_t*)&EIM_AppData.NavDataSelectMsg,
		  //                		EIM_NAVDATA_SELECT_MID);
		  //                CFE_SB_SendMsg((CFE_SB_Msg_t *) &EIM_AppData.NavDataSelectMsg);

						/* Unlock mutex */
						//OS_MutSemGive(g_ARDrone2_AppData.NavDataMutexId);

						//TODO: Send out individual packets based on option mask

						if( cks != navdata_cks )
						{
							CFE_EVS_SendEvent(EIM_TELEM_CHECKSUM_ERR_EID, CFE_EVS_ERROR,
									"EIM:  [Navdata] Checksum failed : %d (distant) / %d (local)\n",
									navdata_cks, cks);
						}
					}
				}
				else
				{
					CFE_EVS_SendEvent(EIM_TELEM_SEQUENCE_ERR_EID, CFE_EVS_ERROR,
							"EIM:  [Navdata] Sequence pb : %d (distant) / %d (local)\n",
							pNavData->sequence, navSequence);
				}
				navSequence = pNavData->sequence;
			}
		}
		else
		{
			CFE_EVS_SendEvent(EIM_TELEM_PACKET_ERR_EID, CFE_EVS_ERROR,
				"EIM:  [Navdata] Failed to read NavData telemetry socket.  Error=%u.\n", len);
		}
	}

end_of_function:
    return status;
}



void EIM_NavDataTlm_delete_callback(void)
{
	close(EIM_AppData.ATCmdSocketID);
	close(EIM_AppData.NavSocketID);
	EIM_AppData.ATCmdSocketID = 0;
	EIM_AppData.NavSocketID = 0;
	if(EIM_AppData.Hk.NavDataState == EIM_NAVDATA_ENABLED)
	{
		EIM_AppData.Hk.NavDataState = EIM_NAVDATA_DISABLED;
	}
}



#ifdef __cplusplus
}
#endif
