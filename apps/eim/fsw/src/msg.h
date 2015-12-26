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
** Ensure that "this" header is included only once
**
**************************************************************************/

#ifndef _eim_msg_
#define _eim_msg_

/*************************************************************************
**
** Include section
**
**************************************************************************/

#include "cmds.h"
#include "common_types.h"
#include "eim_platform_cfg.h"
#include "navcmds.h"



/*************************************************************************
**
** EIM command packet structure definitions
**
**************************************************************************/





typedef enum {
	EIM_CAMERA_DETECTION_HORIZONTAL = 0,
	EIM_CAMERA_DETECTION_VERTICAL,
	EIM_CAMERA_DETECTION_VISION,
	EIM_CAMERA_DETECTION_NONE,
	EIM_CAMERA_DETECTION_COCARDE,
	EIM_CAMERA_DETECTION_ORIENTED_COCARDE,
	EIM_CAMERA_DETECTION_STRIPE,
	EIM_CAMERA_DETECTION_H_COCARDE,
	EIM_CAMERA_DETECTION_H_ORIENTED_COCARDE,
	EIM_CAMERA_DETECTION_STRIPE_V,
	EIM_CAMERA_DETECTION_MULTIPLE_DETECTION_MODE,
	EIM_CAMERA_DETECTION_CAP,
	EIM_CAMERA_DETECTION_ORIENTED_COCARDE_BW,
	EIM_CAMERA_DETECTION_VISION_V2,
	EIM_CAMERA_DETECTION_TOWER_SIDE,
	EIM_CAMERA_DETECTION_NUM,
} EIM_CameraDetectionType_t;

typedef enum {
	EIM_ENEMY_COLOR_ORANGE_GREEN=1,
	EIM_ENEMY_COLOR_ORANGE_YELLOW,
	EIM_ENEMY_COLOR_ORANGE_BLUE,
	EIM_ENEMY_COLOR_ARRACE_FINISH_LINE=0x10,
	EIM_ENEMY_COLOR_ARRACE_DONUT=0x11
} EIM_EnemyColor_t;

typedef enum {
	EIM_CONFIG_KEY_VIDEO_ENABLE,//BOOLEAN
	EIM_CONFIG_KEY_CONTROL_LEVEL,//INT
	EIM_CONFIG_KEY_EULER_ANGLE_MAX,//FLOAT
	EIM_CONFIG_KEY_ALTITUDE_MAX,//INT
	EIM_CONFIG_KEY_ALTITUDE_MIN,//INT
	EIM_CONFIG_KEY_CONTROL_IPHONE_TILT,//FLOAT
	EIM_CONFIG_KEY_CONTROL_VZ_MAX,//FLOAT
	EIM_CONFIG_KEY_CONTROL_YAW,//FLOAT
	EIM_CONFIG_KEY_OUTDOOR,//BOOLEAN
	EIM_CONFIG_KEY_FLIGHT_WITHOUT_SHELL,//BOOLEAN
	EIM_CONFIG_KEY_AUTONOMOUS_FLIGHT,//BOOLEAN
	EIM_CONFIG_KEY_MANUAL_TRIM,//BOOLEAN
	EIM_CONFIG_KEY_INDOOR_EULER_ANGLE_MAX,//FLOAT
	EIM_CONFIG_KEY_INDOOR_CONTROL_VZ_MAX,//FLOAT
	EIM_CONFIG_KEY_INDOOR_CONTROL_YAW,//FLOAT
	EIM_CONFIG_KEY_OUTDOOR_EULER_ANGLE_MAX,//FLOAT
	EIM_CONFIG_KEY_OUTDOOR_CONTROL_VZ_MAX,//FLOAT
	EIM_CONFIG_KEY_OUTDOOR_CONTROL_YAW,//FLOAT
	EIM_CONFIG_KEY_FLYING_MODE,//INT
	EIM_CONFIG_KEY_HOVERING_RANGE,//INT
	EIM_CONFIG_KEY_FLIGHT_ANIM,//STRING
	EIM_CONFIG_KEY_TRAVELLING_MODE,//STRING
	EIM_CONFIG_KEY_TRAVELLING_ENABLE,//BOOLEAN
	EIM_CONFIG_KEY_SSID_SINGLE_PLAYER,//STRING
	EIM_CONFIG_KEY_SSID_MULTI_PLAYER,//STRING
	EIM_CONFIG_KEY_WIFI_MODE,//INT
	EIM_CONFIG_KEY_WIFI_RATE,//INT
	EIM_CONFIG_KEY_OWNER_MAC,//STRING
	EIM_CONFIG_KEY_CODEC_FPS,//INT
	EIM_CONFIG_KEY_VIDEO_CODEC,//INT
	EIM_CONFIG_KEY_VIDEO_SLICES,//INT
	EIM_CONFIG_KEY_VIDEO_LIVE_SOCKET,//INT
	EIM_CONFIG_KEY_BITRATE,//INT
	EIM_CONFIG_KEY_MAX_BITRATE,//INT
	EIM_CONFIG_KEY_BITRATE_CTRL_MODE,//INT
	EIM_CONFIG_KEY_BITRATE_STORAGE,//INT
	EIM_CONFIG_KEY_VIDEO_CHANNEL,//INT
	EIM_CONFIG_KEY_VIDEO_ON_USB,//BOOLEAN
	EIM_CONFIG_KEY_VIDEO_FILE_INDEX,//INT
	EIM_CONFIG_KEY_LEDS_ANIM,//STRING
	EIM_CONFIG_KEY_ENEMY_COLORS,//INT
	EIM_CONFIG_KEY_GROUNDSTRIPE_COLORS,//INT
	EIM_CONFIG_KEY_ENEMY_WITHOUT_SHELL,//INT
	EIM_CONFIG_KEY_DETECT_TYPE,//INT
	EIM_CONFIG_KEY_DETECTIONS_SELECT_H,//INT
	EIM_CONFIG_KEY_DETECTIONS_SELECT_V_HSYNC,//INT
	EIM_CONFIG_KEY_DETECTIONS_SELECT_V,//INT
	EIM_CONFIG_KEY_USERBOX_CMD,//STRING
	EIM_CONFIG_KEY_LATITUDE,//DOUBLE
	EIM_CONFIG_KEY_LONGITUDE,//DOUBLE
	EIM_CONFIG_KEY_ALTITUDE,//DOUBLE
} EIM_ConfigKeys_t;

typedef enum {
	EIM_ARDRONE_VIDEO_CODEC_UVLC = 0x20,
	EIM_ARDRONE_VIDEO_CODEC_P264 = 0x40,
	EIM_MP4_ARDRONE_VIDEO_CODEC_360P = 0x80,
	EIM_H264_ARDRONE_VIDEO_CODEC_360P = 0x81,
	EIM_MP4_360P_H264_ARDRONE_VIDEO_CODEC_720P = 0x82,
	EIM_H264_ARDRONE_VIDEO_CODEC_720P = 0x83,
	EIM_MP4_360P_ARDRONE_VIDEO_CODEC_SLRS = 0x84,
	EIM_H264_360P_ARDRONE_VIDEO_CODEC_SLRS = 0x85,
	EIM_H264_720P_ARDRONE_VIDEO_CODEC_SLRS = 0x86,
	EIM_H264_AUTO_ARDRONE_VIDEO_CODEC_RESIZE = 0x87,
} EIM_VideoCodec_t;

typedef enum {
	EIM_FLYING_MODE_FREE_FLIGHT=0,
	EIM_FLYING_MODE_HOVER_ON_TOP_OF_ROUNDEL=1<<0,
	EIM_FLYING_MODE_HOVER_ON_TOP_OF_ORIENTED_ROUNDEL=1<<1,
} EIM_FlyingMode_t;

typedef enum {
	EIM_ACADEMY_STATE_NONE,
	EIM_ACADEMY_STATE_CONNECTION,
	EIM_ACADEMY_STATE_PREPARE_PROCESS,
	EIM_ACADEMY_STATE_PROCESS,
	EIM_ACADEMY_STATE_FINISH_PROCESS,
	EIM_ACADEMY_STATE_DISCONNECTION,
	EIM_ACADEMY_STATE_MAX,
} EIM_AcademyState_t;

typedef enum {
	EIM_ACADEMY_RESULT_NONE,
	EIM_ACADEMY_RESULT_OK,
	EIM_ACADEMY_RESULT_FAILED,
} EIM_AcademyResult_t;




typedef struct
{
    int16 				accel[3];
    uint16 				temp;
    int16 				gyro[3];
    CFE_TIME_SysTime_t	sampleTime;
} EIM_IMU_raw_t;

typedef struct
{
    int16 mag[3];
    CFE_TIME_SysTime_t	sampleTime;
} EIM_Mag_raw_t;

typedef struct
{
    double accel_x;
    double accel_y;
    double accel_z;
    double gyro_x;
    double gyro_y;
    double gyro_z;
    double mag_x;
    double mag_y;
    double mag_z;
    double temp;
} EIM_IMU_cal_val_t;

typedef struct
{
    double mag_x;
    double mag_y;
    double mag_z;
} EIM_Mag_cal_val_t;

/*
** EIM_SEND_HK_MID, EIM_NOOP_CC, EIM_RESET_CC,
** EIM_SEND_DIAG_TLM_CC
*/
/** 
**  \brief No Arguments Command
**
**  For command details see #EIM_NOOP_CC, #EIM_RESET_CC,
**  #EIM_SEND_DIAG_TLM_CC
*/
typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

} EIM_NoArgsCmd_t;



typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */
    EIM_VariableBitrate_t	Mode;
} EIM_SetVideoBitrateControlModeCmd_t;



typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */
    EIM_VideoChannel_t	Channel;
} EIM_SetVideoChannelCmd_t;



#define EIM_NAME_LENGTH 20
typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */
    char			  Name[EIM_NAME_LENGTH];
} EIM_SetNameCmd_t;



#define EIM_SSID_LENGTH 20
typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */
    char			  Name[EIM_SSID_LENGTH];
} EIM_SetSSIDCmd_t;


#define EIM_MAC_LENGTH 18
typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */
    char			  MAC[EIM_MAC_LENGTH];

} EIM_SetOwnerMac_t;



typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    EIM_VideoCodecType_t	CodecType;
} EIM_CodecTypeCmd_t;



typedef struct
{
    uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    uint32 	FramesPerSecond;
} EIM_FpsCmd_t;



typedef struct
{
    uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    uint32 	Timeout;
} EIM_SetWatchdogCmd_t;





typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    EIM_ARDrone2_UltrasoundFreq_t Freq;

} EIM_UltrasoundFreqCmd_t;




typedef struct
{
    uint8             CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    EIM_ARDrone2_FlightModes_t	Mode;
} EIM_FlightModeCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    float	Angle;

} EIM_AngleCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    EIM_WifiMode_t	Mode;

} EIM_SetWifiModeCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    float	Speed;

} EIM_SpeedCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    uint32	BitRate;

} EIM_BitRateCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    uint32	Altitude;

} EIM_AltitudeCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    EIM_LEDAnimation_t 	Animation;
    float 				Frequency;
    uint32 				Duration;

} EIM_LEDAnimationCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    float	Rate;

} EIM_AngularRateCmd_t;



typedef struct
{
    uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    float	Percent;
} EIM_PercentageCmd_t;



typedef struct
{
    uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    EIM_FlightAnimation_t 	Animation;
    uint32					Duration;
} EIM_FlightAnimationCmd_t;



typedef struct
{
    uint8	CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */

    float	Roll;
    float	Pitch;
    float	Vertical;
    float	Yaw;

} EIM_CombinedMovementCmd_t;



typedef struct
{
    uint8             	CmdHeader[CFE_SB_CMD_HDR_SIZE];  /**< \brief cFE Software Bus Command Message Header */
    uint32				ControlMode;
} EIM_SetControlModeCmd_t;

/*
** EIM_ENABLE_CC, EIM_DISABLE_CC
*/
/** 
**  \brief Entry Enable/Disable Commands
**
**  For command details see #EIM_ENABLE_CC, #EIM_DISABLE_CC
*/
typedef struct
{
    uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];          /**< \brief cFE Software Bus Command Message Header */

} EIM_EntryCmd_t;



typedef struct
{
    uint8   CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint32  TagID;
} EIM_ActDeactTagCmd_t;



#define EIM_IMU_MSG_SIZE sizeof(EIM_IMU_Msg_t)

/*************************************************************************
**
** EIM housekeeping telemetry packet definition
**
**************************************************************************/

typedef enum
{
	EIM_NAVDATA_DISABLED		= 0,
	EIM_NAVDATA_ENABLED			= 1,
	EIM_NAVDATA_INITIALIZING	= 2,
	EIM_NAVDATA_BOOTSTRAP		= 3,
	EIM_NAVDATA_COMMAND_MASK	= 4,
	EIM_NAVDATA_FAILED			= 5
} NavDataState_t;



typedef struct
{
    boolean Fly 				: 1;
    boolean Video 				: 1;
    boolean Vision 				: 1;
    boolean ControlAlgo 		: 1;
    boolean AltControlAlgo 		: 1;
    boolean UserFeedbackStart 	: 1;
    boolean CommandReceived 	: 1;
    boolean Camera 				: 1;
    boolean Traveling 			: 1;
    boolean USB 				: 1;
    boolean Demo 				: 1;
    boolean Bootstrap 			: 1;
    boolean Motors 				: 1;
    boolean ComLost 			: 1;
    boolean Software 			: 1;
    boolean VBat 				: 1;
    boolean UserEmergency 		: 1;
    boolean Timer 				: 1;
    boolean MagnetoCalib 		: 1;
    boolean Angles 				: 1;
    boolean Wind 				: 1;
    boolean UltrasonicSensor 	: 1;
    boolean Cutout 				: 1;
    boolean PICVersion 			: 1;
    boolean ATCodecThread 		: 1;
    boolean NavDataThread 		: 1;
    boolean VideoThread 		: 1;
    boolean AcqThread 			: 1;
    boolean CtrlWatchdog 		: 1;
    boolean ADCWatchdog 		: 1;
    boolean CommWatchdog 		: 1;
	boolean Emergency 			: 1;
} EIM_ARDrone2State_t;

typedef struct
{
    uint8    TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

    /*
    ** Command execution counters (ground commands)
    */
    uint16    CmdCounter;                              /**< \schtlmmnemonic \SCH_CMDPC
                                                           \brief Command Counter
                                                           \details \ref SCHHK_CmdCounter "Click for more" */
    uint16    ErrCounter;                              /**< \schtlmmnemonic \SCH_CMDEC
                                                           \brief Command Error Counter 
                                                           \details \ref SCHHK_ErrCounter "Click for more"  */
    NavDataState_t	  	NavDataState;
    EIM_ARDrone2State_t	ARDroneState;

    int32				VisionDefined;
    uint32				SkipFrames;

    uint32				navdata_demo_count;
    uint32				navdata_time_count;
    uint32				navdata_raw_measures_count;
    uint32				navdata_pressure_raw_count;
    uint32				navdata_magneto_count;
    uint32				navdata_wind_speed_count;
    uint32				navdata_kalman_pressure_count;
    uint32				navdata_zimmu_3000_count;
    uint32				navdata_phys_measures_count;
    uint32				navdata_gyro_offsets_count;
    uint32				navdata_euler_angles_count;
    uint32				navdata_references_count;
    uint32				navdata_trims_count;
    uint32				navdata_rc_references_count;
    uint32				navdata_pwm_count;
    uint32				navdata_altitude_count;
    uint32				navdata_vision_raw_count;
    uint32				navdata_vision_count;
    uint32				navdata_vision_perf_count;
    uint32				navdata_trackers_send_count;
    uint32				navdata_vision_detect_count;
    uint32				navdata_vision_of_count;
    uint32				navdata_watchdog_count;
    uint32				navdata_adc_data_frame_count;
    uint32				navdata_video_stream_count;
    uint32				navdata_hdvideo_stream_count;
    uint32				navdata_games_count;
    uint32				navdata_wifi_count;

    boolean				ARDrone2TimedOut;
} OS_PACK EIM_HkPacket_t;

typedef enum
{
	EIM_MINOR_CTRL_STATE_DISABLED = 0,
	EIM_MINOR_CTRL_STATE_INIT = 1,
	EIM_MINOR_CTRL_STATE_LANDED = 2,
	EIM_MINOR_CTRL_STATE_FLYING = 3,
	EIM_MINOR_CTRL_STATE_HOVERING = 4,
	EIM_MINOR_CTRL_STATE_TAKEOFF = 5,
	EIM_MINOR_CTRL_STATE_UNKNOWN = 6,
	EIM_MINOR_CTRL_STATE_GOTOFIX = 7,
	EIM_MINOR_CTRL_STATE_LANDING = 8,
	EIM_MINOR_CTRL_STATE_LOOPING = 9
} EIMMinorCtrlState_t;

typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

    int16       minor_ctrl_state;           /*!< Minor Control State */
    int16       ctrl_state;                 /*!< Major Control State */
    uint32    	vbat_flying_percentage; 	/*!< battery voltage filtered (mV) */

	float   	theta;                  	/*!< UAV's pitch in milli-degrees */
	float   	phi;                    	/*!< UAV's roll  in milli-degrees */
	float   	psi;                    	/*!< UAV's yaw   in milli-degrees */

	int32     	altitude;               	/*!< UAV's altitude in centimeters */

	float   	vx;                     	/*!< UAV's estimated linear velocity */
	float   	vy;                     	/*!< UAV's estimated linear velocity */
	float   	vz;                     	/*!< UAV's estimated linear velocity */

	uint32    	num_frames;			  		/*!< streamed frame index */ // Not used -> To integrate in video stage.

	// Camera parameters compute by detection
	matrix33_t	detection_camera_rot;

	velocities_t	detection_camera_trans;

	uint32	  	detection_tag_index;

	uint32	  	detection_camera_type;  	/*!<  Type of tag searched in detection  */

	// Camera parameters compute by drone
	matrix33_t	drone_camera_rot;

	velocities_t	drone_camera_trans;
} OS_PACK EIM_NavData_Demo_t;



/*----------------------------------------------------------------------------*/
/**
 * @brief Timestamp
 * + 6 bytes
 */
typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32  	time;  						/*!< 32 bit value where the 11 most significant bits represents the seconds, and the 21 least significant bits are the microseconds. */
} OS_PACK EIM_NavData_Time_t;



/*----------------------------------------------------------------------------*/
/**
 * @brief Raw sensors measurements
 */
typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	// +12 bytes
	uint16  	raw_accs[NB_ACCS];    		// filtered accelerometers
	int16   	raw_gyros[NB_GYROS];  		// filtered gyrometers
	int16   	raw_gyros_110[2];   		// gyrometers  x/y 110 deg/s
	uint32  	vbat_raw;             		// battery voltage raw (mV)
	uint16  	us_debut_echo;
	uint16  	us_fin_echo;
	uint16  	us_association_echo;
	uint16  	us_distance_echo;
	uint16  	us_courbe_temps;
	uint16  	us_courbe_valeur;
	uint16  	us_courbe_ref;
	uint16  	flag_echo_ini;
	// TODO:   uint16_t  frame_number; // from ARDrone_Magneto
	uint16  	nb_echo;
	uint32  	sum_echo;
	int32   	alt_temp_raw;

	int16   	gradient;
} OS_PACK EIM_NavData_Raw_Measures_t;



// split next struc into magneto_navdata_t and pressure_navdata_t
typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int32   	up;
	int16   	ut;
	int32   	Temperature_meas;
 	int32   	Pression_meas;
} OS_PACK EIM_NavData_Pressure_Raw_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int16   	mx;
	int16   	my;
	int16   	mz;
	vector31_t 	magneto_raw;       // magneto in the body frame, in mG
	vector31_t 	magneto_rectified;
	vector31_t 	magneto_offset;
	float 		heading_unwrapped;
	float 		heading_gyro_unwrapped;
	float		heading_fusion_unwrapped;
	char 		magneto_calibration_ok;
	uint32      magneto_state;
	float 		magneto_radius;
	float    	error_mean;
	float     	error_var;

} OS_PACK EIM_NavData_Magneto_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float 		wind_speed;
	float 		wind_angle;
	float 		wind_compensation_theta;
	float 		wind_compensation_phi;
	float 		state_x1;
	float 		state_x2;
	float 		state_x3;
	float 		state_x4;
	float 		state_x5;
	float 		state_x6;
	float 		magneto_debug1;
	float 		magneto_debug2;
	float 		magneto_debug3;
} OS_PACK EIM_NavData_Wind_Speed_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float 		offset_pressure;
	float 		est_z;
	float 		est_zdot;
	float 		est_bias_PWM;
	float 		est_biais_pression;
	float 		offset_US;
	float 		prediction_US;
	float 		cov_alt;
	float 		cov_PWM;
	float 		cov_vitesse;
	uint32    	bool_effet_sol;
	float 		somme_inno;
	uint32    	flag_rejet_US;
	float 		u_multisinus;
	float 		gaz_altitude;
	uint32    	Flag_multisinus;
	uint32    	Flag_multisinus_debut;
} OS_PACK EIM_NavData_Kalman_Pressure_t;



// TODO: depreciated struct ? remove it ?
typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int32 		vzimmuLSB;
	float 		vzfind;

} OS_PACK EIM_NavData_Zimmu_3000_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float   	accs_temp;
	uint16    	gyro_temp;
	float   	phys_accs[NB_ACCS];
	float   	phys_gyros[NB_GYROS];
	uint32    	alim3V3;              // 3.3volt alim [LSB]
	uint32    	vrefEpson;            // ref volt Epson gyro [LSB]
	uint32    	vrefIDG;              // ref volt IDG gyro [LSB]
} OS_PACK EIM_NavData_Phys_Measures_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float 		offset_g[NB_GYROS];
} OS_PACK EIM_NavData_Gyros_Offsets_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float   	theta_a;
	float   	phi_a;
} OS_PACK EIM_NavData_Euler_Angles_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int32   	ref_theta;
	int32   	ref_phi;
	int32   	ref_theta_I;
	int32   	ref_phi_I;
	int32   	ref_pitch;
	int32   	ref_roll;
	int32   	ref_yaw;
	int32   	ref_psi;

	float 		vx_ref;
	float 		vy_ref;
	float 		theta_mod;
	float 		phi_mod;

	float 		k_v_x;
	float 		k_v_y;
	uint32  	k_mode;

	float 		ui_time;
	float 		ui_theta;
	float 		ui_phi;
	float 		ui_psi;
	float 		ui_psi_accuracy;
	int32 		ui_seq;

} OS_PACK EIM_NavData_References_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float 		angular_rates_trim_r;
	float 		euler_angles_trim_theta;
	float 		euler_angles_trim_phi;
} OS_PACK EIM_NavData_Trims_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int32    	rc_ref_pitch;
	int32    	rc_ref_roll;
	int32    	rc_ref_yaw;
	int32    	rc_ref_gaz;
	int32    	rc_ref_ag;
} OS_PACK EIM_NavData_RC_References_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint8     	motor1;
	uint8     	motor2;
	uint8     	motor3;
	uint8     	motor4;
	uint8	  	sat_motor1;
	uint8	  	sat_motor2;
	uint8	  	sat_motor3;
	uint8	  	sat_motor4;
	float   	gaz_feed_forward;
	float   	gaz_altitude;
	float   	altitude_integral;
	float   	vz_ref;
	int32     	u_pitch;
	int32     	u_roll;
	int32     	u_yaw;
	float   	yaw_u_I;
	int32     	u_pitch_planif;
	int32     	u_roll_planif;
	int32     	u_yaw_planif;
	float   	u_gaz_planif;
	uint16    	current_motor1;
	uint16    	current_motor2;
	uint16    	current_motor3;
	uint16    	current_motor4;
	//WARNING: new navdata (FC 26/07/2011)
	float 		altitude_prop;
	float 		altitude_der;
} OS_PACK EIM_NavData_PWM_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int32   	altitude_vision;
	float 		altitude_vz;
	int32   	altitude_ref;
	int32   	altitude_raw;

	float		obs_accZ;
	float 		obs_alt;
	vector31_t 	obs_x;
	uint32 		obs_state;
	vector21_t	est_vb;
	uint32 		est_state ;

} OS_PACK EIM_NavData_Altitude_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float 		vision_tx_raw;
	float 		vision_ty_raw;
	float 		vision_tz_raw;
} OS_PACK EIM_NavData_Vision_Raw_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32   	vision_state;
	int32    	vision_misc;
	float  		vision_phi_trim;
	float  		vision_phi_ref_prop;
	float  		vision_theta_trim;
	float  		vision_theta_ref_prop;

	int32    	new_raw_picture;
	float  		theta_capture;
	float  		phi_capture;
	float  		psi_capture;
	int32    	altitude_capture;
	uint32   	time_capture;     // time in TSECDEC format (see config.h)
	velocities_t 	body_v;

	float  		delta_phi;
	float 	 	delta_theta;
	float  		delta_psi;

	uint32  	gold_defined;
	uint32  	gold_reset;
	float 		gold_x;
	float 		gold_y;
} OS_PACK EIM_NavData_Vision_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	// +44 bytes
	float  		time_szo;
	float  		time_corners;
	float  		time_compute;
	float  		time_tracking;
	float  		time_trans;
	float  		time_update;
	float  		time_custom[EIM_NAVDATA_MAX_CUSTOM_TIME_SAVE];
} OS_PACK EIM_NavData_Vision_Perf_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	int32 		locked[DEFAULT_NB_TRACKERS_WIDTH * DEFAULT_NB_TRACKERS_HEIGHT];
	screen_point_t 	point[DEFAULT_NB_TRACKERS_WIDTH * DEFAULT_NB_TRACKERS_HEIGHT];
} OS_PACK EIM_NavData_Trackers_Send_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32   	nb_detected;
	uint32   	type[EIM_NB_NAVDATA_DETECTION_RESULTS];
	uint32   	xc[EIM_NB_NAVDATA_DETECTION_RESULTS];
	uint32   	yc[EIM_NB_NAVDATA_DETECTION_RESULTS];
	uint32   	width[EIM_NB_NAVDATA_DETECTION_RESULTS];
	uint32   	height[EIM_NB_NAVDATA_DETECTION_RESULTS];
	uint32   	dist[EIM_NB_NAVDATA_DETECTION_RESULTS];
	float  		orientation_angle[EIM_NB_NAVDATA_DETECTION_RESULTS];
	matrix33_t 	rotation[EIM_NB_NAVDATA_DETECTION_RESULTS];
	vector31_t 	translation[EIM_NB_NAVDATA_DETECTION_RESULTS];
	uint32   	camera_source[EIM_NB_NAVDATA_DETECTION_RESULTS];
} OS_PACK EIM_NavData_Vision_Detect_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	float   	of_dx[5];
	float   	of_dy[5];
} OS_PACK EIM_NavData_Vision_OF_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	// +4 bytes
	int32    	watchdog;
} OS_PACK EIM_NavData_Watchdog_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32  	version;
	uint8   	data_frame[32];
} OS_PACK EIM_NavData_ADC_Data_Frame_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint8 		quant;			// quantizer reference used to encode frame [1:31]
	uint32		frame_size;		// frame size (bytes)
	uint32		frame_number;	// frame index
	uint32		atcmd_ref_seq;  // atmcd ref sequence number
	uint32		atcmd_mean_ref_gap;	// mean time between two consecutive atcmd_ref (ms)
	float 		atcmd_var_ref_gap;
	uint32		atcmd_ref_quality; // estimator of atcmd link quality

	// drone2
	uint32  	out_bitrate;     // measured out throughput from the video tcp socket
	uint32  	desired_bitrate; // last frame size generated by the video encoder

	// misc temporary data
	int32  		data1;
	int32  		data2;
	int32  		data3;
	int32  		data4;
	int32  		data5;

	// queue usage
	uint32 		tcp_queue_level;
	uint32 		fifo_queue_level;

} OS_PACK EIM_NavData_Video_Stream_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32 		hdvideo_state;
	uint32 		storage_fifo_nb_packets;
	uint32 		storage_fifo_size;
	uint32 		usbkey_size;         /*! USB key in kbytes - 0 if no key present */
	uint32 		usbkey_freespace;    /*! USB key free space in kbytes - 0 if no key present */
	uint32 		frame_number;        /*! 'frame_number' PaVE field of the frame starting to be encoded for the HD stream */
	uint32 		usbkey_remaining_time; /*! time in seconds */

} OS_PACK EIM_NavData_HDVideo_Stream_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32 		double_tap_counter;
	uint32  	finish_line_counter;
} OS_PACK EIM_NavData_Games_t;



typedef struct
{
    uint8    	TlmHeader[CFE_SB_TLM_HDR_SIZE];          /**< \brief cFE Software Bus Telemetry Message Header */

	uint32 		link_quality;
} OS_PACK EIM_NavData_Wifi_t;



#define EIM_HK_TLM_LNGTH           sizeof (EIM_HkPacket_t)

/*************************************************************************
**
** EIM diagnostic telemetry packet definition
**
**************************************************************************/

typedef struct
{
    uint8           TlmHeader[CFE_SB_TLM_HDR_SIZE];   /**< \brief cFE Software Bus Telemetry Message Header */
} EIM_DiagPacket_t;

#endif /* _eim_msg_ */

/************************/
/*  End of File Comment */
/************************/

