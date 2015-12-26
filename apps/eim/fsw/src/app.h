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

#ifndef _eim_app_
#define _eim_app_

/*************************************************************************
**
** Include section
**
**************************************************************************/

#include "cfe.h"
#include "eim_msgs.h"
#include "msg.h"
#include "navdata.h"
#include <netinet/in.h>

/*************************************************************************
**
** Macro definitions
**
**************************************************************************/

/*************************************************************************/
/*************************************************************************/

/*
** Command pipe definitions
*/
/** \name EIM App Pipe Characteristics */
/**  \{ */
#define EIM_PIPE_NAME       "EIM_CMD_PIPE"  /**< \brief EIM Command Pipe Name */
/** \} */

/*
** Event filter table definitions
*/
/** \name EIM App Event Filter Characteristics */
/**  \{ */
#define EIM_FILTER_COUNT    5
/** \} */


/*
** Internal Function Return Codes
*/
/** \name EIM App Internal Error Codes */
/**  \{ */
#define EIM_SUCCESS              (0) /**< \brief EIM return code for success */
#define EIM_ERROR               (-1) /**< \brief EIM return code for general error */
#define EIM_BAD_MSG_LENGTH_RC   (-2) /**< \brief EIM return code for unexpected cmd length */
#define EIM_UNKNOWN_ACTIVITY    (-3) /**< \brief EIM return code for unknown Entry Activity Type */
/** \} */

/*************************************************************************
**
** Type definitions
**
**************************************************************************/


/*
** Type definition (EIM app global data)
*/
typedef struct
{
    /*
    ** Operational data 
    */
    CFE_SB_MsgPtr_t       	MsgPtr;                         	/**< \brief Ptr to most recently received cmd message */
    CFE_SB_PipeId_t       	CmdPipe;                        	/**< \brief Pipe ID for EIM Command Pipe */

    CFE_EVS_BinFilter_t   	EventFilters[EIM_FILTER_COUNT]; 	/**< \brief Array of Event Filters */
    
    EIM_HkPacket_t        	Hk;                       		/**< \brief Housekeeping Telemetry Packet */
    EIM_DiagPacket_t      	DiagPacket;                     	/**< \brief Diagnostic Telemetry Packet */
    
    uint32                	LastProcessCount;               	/**< \brief Number of Frames Processed Last Cycle */
    
    uint32                	AppID;                          	/**< \brief EIM Application's Application ID */
    
    uint32					SkippedFrames;

    uint32                	userLedBrightness;

    int32                 	imuHandle;
    uint32                	imuAddress;
    int32                 	magHandle;
    uint32                	magAddress;

    EIM_IMU_Msg_t         	ImuMsg;
    EIM_Mag_Msg_t         	MagMsg;

    uint32					NavDataTlmTaskId;
    uint32					NavDataCmdTaskId;
    boolean 				NavDataStale;

    int                     NavSocketID;
    int                     ATCmdSocketID;

    struct sockaddr_in 		CmdSocketAddress;
    struct sockaddr_in 		CmdARDroneAddress;

    uint32                  NavDataMutexId;
    uint32                  CmdSeqMutexId;

    uint32                  lastNavDataOptions;

    int32                	sensorLogFileHandle;


    uint32 					nd_seq;
    int32 					vision_defined;

    uint32					control_level;
    uint32					indoor_control_level;
    uint32					outdoor_control_level;

    uint32					navdata_options;

    EIM_NavData_Demo_t				navdata_demo;
    EIM_NavData_Time_t				navdata_time;
    EIM_NavData_Raw_Measures_t		navdata_raw_measures;
    EIM_NavData_Pressure_Raw_t		navdata_pressure_raw;
    EIM_NavData_Magneto_t			navdata_magneto;
    EIM_NavData_Wind_Speed_t		navdata_wind_speed;
    EIM_NavData_Kalman_Pressure_t	navdata_kalman_pressure;
    EIM_NavData_Zimmu_3000_t		navdata_zimmu_3000;
    EIM_NavData_Phys_Measures_t		navdata_phys_measures;
    EIM_NavData_Gyros_Offsets_t		navdata_gyro_offsets;
    EIM_NavData_Euler_Angles_t		navdata_euler_angles;
    EIM_NavData_References_t		navdata_references;
    EIM_NavData_Trims_t				navdata_trims;
    EIM_NavData_RC_References_t		navdata_rc_references;
    EIM_NavData_PWM_t				navdata_pwm;
    EIM_NavData_Altitude_t			navdata_altitude;
    EIM_NavData_Vision_Raw_t		navdata_vision_raw;
    EIM_NavData_Vision_t			navdata_vision;
    EIM_NavData_Vision_Perf_t		navdata_vision_perf;
    EIM_NavData_Trackers_Send_t		navdata_trackers_send;
    EIM_NavData_Vision_Detect_t		navdata_vision_detect;
    EIM_NavData_Vision_OF_t			navdata_vision_of;
    EIM_NavData_Watchdog_t			navdata_watchdog;
    EIM_NavData_ADC_Data_Frame_t	navdata_adc_data_frame;
    EIM_NavData_Video_Stream_t		navdata_video_stream;
    EIM_NavData_HDVideo_Stream_t	navdata_hdvideo_stream;
    EIM_NavData_Games_t				navdata_games;
    EIM_NavData_Wifi_t				navdata_wifi;

} EIM_AppData_t;

/*************************************************************************
**
** Exported data
**
**************************************************************************/

extern EIM_AppData_t    EIM_AppData;
extern EIM_IMU_raw_t    EIM_RawData;

/*************************************************************************
**
** Exported functions
**
**************************************************************************/

/*
** Application entry point and main process loop
*/
void   EIM_AppMain(void);

#endif /* _eim_app_ */

/************************/
/*  End of File Comment */
/************************/
