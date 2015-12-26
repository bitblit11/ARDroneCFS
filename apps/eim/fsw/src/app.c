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

/*************************************************************************
**
** Include section
**
**************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"
#include <linux/i2c.h>
#include <string.h>
#include <errno.h>

#include "eim_msgids.h"
#include "eim_perfids.h"
#include "eim_platform_cfg.h"

#include "msg.h"
#include "events.h"
#include "app.h"
#include "version.h"
#include "msgdefs.h"
#include "cmds.h"
#include "navdata.h"

#include "cfe_time_msg.h"
#include "verify.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*************************************************************************
**
** Macro definitions
**
**************************************************************************/
#define EIM_MAX_BUFFER_SIZE		64


/*************************************************************************
**
** Type definitions
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Imported data
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Exported data
**
**************************************************************************/

/*
** Application global data
*/
EIM_AppData_t           EIM_AppData;


/*
 * Interal data
 */

/*************************************************************************
**
** File data
**
**************************************************************************/

/*
** (none)
*/


/*************************************************************************
** Local function prototypes
**************************************************************************/

int32 EIM_AppInit(void);

int32 EIM_EvsInit(void);

int32 EIM_SbInit(void);

int32 EIM_TblInit(void);

void EIM_ReportHousekeeping(void);
void EIM_ProcessCommandPacket(void);
void EIM_ProcessGroundCommand(void);


/*************************************************************************
**
** Function definitions
**
**************************************************************************/

/*******************************************************************
**
** EIM_AppMain
**
** NOTE: For complete prolog information, see 'eim_app.h'
********************************************************************/
void EIM_AppMain(void)
{
    int32  status;
    uint32 RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(EIM_APPMAIN_PERF_ID);

    EIM_AppInit();

    /*
    ** CI Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(EIM_APPMAIN_PERF_ID);

        /* Pend on receipt of command packet -- timeout set to 500 millisecs */
        status = CFE_SB_RcvMsg(&EIM_AppData.MsgPtr, EIM_AppData.CmdPipe, 500);

        CFE_ES_PerfLogEntry(EIM_APPMAIN_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            EIM_ProcessCommandPacket();
        }
    }

    CFE_ES_ExitApp(RunStatus);


} /* End of EIM_AppMain() */



void EIM_delete_callback(void)
{
    if(EIM_AppData.imuHandle > 0)
    {
        close(EIM_AppData.imuHandle);
    }
    if(EIM_AppData.sensorLogFileHandle > 0)
    {
        close(EIM_AppData.sensorLogFileHandle);
    }
}



int32 EIM_AppInit(void)
{
    CFE_ES_RegisterApp() ;

    CFE_EVS_Register(EIM_AppData.EventFilters,
                     sizeof(EIM_AppData.EventFilters)/sizeof(CFE_EVS_BinFilter_t),
                     CFE_EVS_BINARY_FILTER);

    CFE_SB_CreatePipe(&EIM_AppData.CmdPipe, EIM_PIPE_DEPTH, (char*)"EIM_CMD_PIPE");
    CFE_SB_Subscribe(EIM_CMD_MID, EIM_AppData.CmdPipe);
    CFE_SB_Subscribe(EIM_SEND_HK_MID, EIM_AppData.CmdPipe);
    
    /* Reset counters */
    EIM_AppData.Hk.CmdCounter = 0;
    EIM_AppData.Hk.ErrCounter = 0;

    EIM_AppData.Hk.SkipFrames = EIM_ARDRONE2_DEFAULT_SKIPFRAMES;
    EIM_AppData.SkippedFrames = 0;

    EIM_AppData.control_level = 1;
    EIM_AppData.indoor_control_level = 1;
    EIM_AppData.outdoor_control_level = 1;
    EIM_AppData.Hk.ARDrone2TimedOut = FALSE;

    /*
    ** Install the delete handler
    */
    OS_TaskInstallDeleteHandler((void *)(&EIM_delete_callback));

    CFE_SB_InitMsg(&EIM_AppData.ImuMsg,
            EIM_IMU_MID,
            EIM_IMU_MSG_SIZE, TRUE);

    CFE_SB_InitMsg(&EIM_AppData.Hk,
            EIM_HK_TLM_MID,
            EIM_HK_TLM_LNGTH, TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_demo,
            EIM_NAVDATA_DEMO_MID,
            sizeof(EIM_AppData.navdata_demo), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_time,
            EIM_NAVDATA_TIME_MID,
            sizeof(EIM_AppData.navdata_time), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_raw_measures,
            EIM_NAVDATA_RAW_MEASURES_MID,
            sizeof(EIM_AppData.navdata_raw_measures), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_pressure_raw,
            EIM_NAVDATA_PRESSURE_RAW_MID,
            sizeof(EIM_AppData.navdata_pressure_raw), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_magneto,
            EIM_NAVDATA_MAGNETO_MID,
            sizeof(EIM_AppData.navdata_magneto), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_wind_speed,
            EIM_NAVDATA_WIND_SPEED_MID,
            sizeof(EIM_AppData.navdata_wind_speed), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_kalman_pressure,
            EIM_NAVDATA_KALMAN_PRESSURE_MID,
            sizeof(EIM_AppData.navdata_kalman_pressure), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_zimmu_3000,
            EIM_NAVDATA_ZIMMU_3000_MID,
            sizeof(EIM_AppData.navdata_zimmu_3000), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_phys_measures,
            EIM_NAVDATA_PHYS_MEASURES_MID,
            sizeof(EIM_AppData.navdata_phys_measures), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_gyro_offsets,
            EIM_NAVDATA_GYRO_OFFSETS_MID,
            sizeof(EIM_AppData.navdata_gyro_offsets), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_euler_angles,
            EIM_NAVDATA_EULER_ANGLES_MID,
            sizeof(EIM_AppData.navdata_euler_angles), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_references,
            EIM_NAVDATA_REFERENCES_MID,
            sizeof(EIM_AppData.navdata_references), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_trims,
            EIM_NAVDATA_TRIMS_MID,
            sizeof(EIM_AppData.navdata_trims), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_rc_references,
            EIM_NAVDATA_RC_REFERENCES_MID,
            sizeof(EIM_AppData.navdata_rc_references), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_pwm,
            EIM_NAVDATA_PWM_MID,
            sizeof(EIM_AppData.navdata_pwm), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_altitude,
            EIM_NAVDATA_ALTITUDE_MID,
            sizeof(EIM_AppData.navdata_altitude), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_vision_raw,
            EIM_NAVDATA_VISION_RAW_MID,
            sizeof(EIM_AppData.navdata_vision_raw), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_vision,
            EIM_NAVDATA_VISION_MID,
            sizeof(EIM_AppData.navdata_vision), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_vision_perf,
            EIM_NAVDATA_VISION_PERF_MID,
            sizeof(EIM_AppData.navdata_vision_perf), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_trackers_send,
            EIM_NAVDATA_TRACKERS_SEND_MID,
            sizeof(EIM_AppData.navdata_trackers_send), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_vision_detect,
            EIM_NAVDATA_DETECT_MID,
            sizeof(EIM_AppData.navdata_vision_detect), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_vision_of,
            EIM_NAVDATA_VISION_OF_MID,
            sizeof(EIM_AppData.navdata_vision_of), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_watchdog,
            EIM_NAVDATA_WATCHDOG_MID,
            sizeof(EIM_AppData.navdata_watchdog), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_adc_data_frame,
            EIM_NAVDATA_ADC_DATA_FRAME_MID,
            sizeof(EIM_AppData.navdata_adc_data_frame), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_video_stream,
            EIM_NAVDATA_VIDEO_STREAM_MID,
            sizeof(EIM_AppData.navdata_video_stream), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_hdvideo_stream,
            EIM_NAVDATA_HDVIDEO_MID,
            sizeof(EIM_AppData.navdata_hdvideo_stream), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_games,
            EIM_NAVDATA_GAMES_MID,
            sizeof(EIM_AppData.navdata_games), TRUE);

    CFE_SB_InitMsg(&EIM_AppData.navdata_wifi,
            EIM_NAVDATA_WIFI_MID,
            sizeof(EIM_AppData.navdata_wifi), TRUE);

    CFE_EVS_SendEvent (EIM_STARTUP_INF_EID, CFE_EVS_INFORMATION,
               "EIM Initialized.  Version %d.%d.%d.%d",
               EIM_MAJOR_VERSION,
               EIM_MINOR_VERSION,
               EIM_REVISION,
               EIM_MISSION_REV);

    EIM_AppData.userLedBrightness = 1;

    EIM_AppData.sensorLogFileHandle = -1;
#ifdef EIM_LOG_TO_FILE_SYSTEM
    //EIM_AppData.sensorLogFileHandle = OS_creat("/log/eim_sensor.log", OS_WRITE_ONLY);
#endif

    return CFE_SUCCESS;
} /* End of EIM_AppInit() */



void EIM_ProcessCommandPacket(void)
{
    CFE_SB_MsgId_t  MsgId;
    MsgId = CFE_SB_GetMsgId( EIM_AppData.MsgPtr );

    switch (MsgId)
    {
        case EIM_CMD_MID:
            EIM_ProcessGroundCommand();
            break;

        case EIM_SEND_HK_MID:
            EIM_ReportHousekeeping();
            break;

        default:
            EIM_AppData.Hk.ErrCounter++;
            CFE_EVS_SendEvent(EIM_COMMAND_ERR_EID, CFE_EVS_ERROR,
            "EIM: invalid command packet,MID = 0x%x", MsgId);
            break;
    }
} /* End EIM_ProcessCommandPacket */



void EIM_ReportHousekeeping(void)
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &EIM_AppData.Hk);

    CFE_SB_SendMsg((CFE_SB_Msg_t *) &EIM_AppData.Hk);

} /* End of EIM_ReportHousekeeping() */







#ifdef __cplusplus
}
#endif

/************************/
/*  End of File Comment */
/************************/

