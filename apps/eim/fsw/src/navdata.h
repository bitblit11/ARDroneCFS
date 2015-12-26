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

#ifndef EIM_NAVDATATLM_H_
#define EIM_NAVDATATLM_H_

#include "cfe.h"
#include "eim_platform_cfg.h"
#include "msg.h"
#include "types.h"


#define NAVDATA_HEADER  0x55667788


void EIM_NavDataTlmMain(void);





typedef enum
{
	ARDRONE2_FLY_MASK            = 1U << 0,  /*!< FLY MASK : (0) ardrone is landed, (1) ardrone is flying */
	ARDRONE2_VIDEO_MASK          = 1U << 1,  /*!< VIDEO MASK : (0) video disable, (1) video enable */
	ARDRONE2_VISION_MASK         = 1U << 2,  /*!< VISION MASK : (0) vision disable, (1) vision enable */
	ARDRONE2_CONTROL_MASK        = 1U << 3,  /*!< CONTROL ALGO : (0) euler angles control, (1) angular speed control */
	ARDRONE2_ALTITUDE_MASK       = 1U << 4,  /*!< ALTITUDE CONTROL ALGO : (0) altitude control inactive (1) altitude control active */
	ARDRONE2_USER_FEEDBACK_START = 1U << 5,  /*!< USER feedback : Start button state */
	ARDRONE2_COMMAND_MASK        = 1U << 6,  /*!< Control command ACK : (0) None, (1) one received */
	ARDRONE2_CAMERA_MASK         = 1U << 7,  /*!< CAMERA MASK : (0) camera not ready, (1) Camera ready */
	ARDRONE2_TRAVELLING_MASK     = 1U << 8,  /*!< Travelling mask : (0) disable, (1) enable */
	ARDRONE2_USB_MASK            = 1U << 9,  /*!< USB key : (0) usb key not ready, (1) usb key ready */
	ARDRONE2_NAVDATA_DEMO_MASK   = 1U << 10, /*!< Navdata demo : (0) All navdata, (1) only navdata demo */
	ARDRONE2_NAVDATA_BOOTSTRAP   = 1U << 11, /*!< Navdata bootstrap : (0) options sent in all or demo mode, (1) no navdata options sent */
	ARDRONE2_MOTORS_MASK  	     = 1U << 12, /*!< Motors status : (0) Ok, (1) Motors problem */
	ARDRONE2_COM_LOST_MASK       = 1U << 13, /*!< Communication Lost : (1) com problem, (0) Com is ok */
	ARDRONE2_SOFTWARE_FAULT      = 1U << 14, /*!< Software fault detected - user should land as quick as possible (1) */
	ARDRONE2_VBAT_LOW            = 1U << 15, /*!< VBat low : (1) too low, (0) Ok */
	ARDRONE2_USER_EL             = 1U << 16, /*!< User Emergency Landing : (1) User EL is ON, (0) User EL is OFF*/
	ARDRONE2_TIMER_ELAPSED       = 1U << 17, /*!< Timer elapsed : (1) elapsed, (0) not elapsed */
	ARDRONE2_MAGNETO_NEEDS_CALIB = 1U << 18, /*!< Magnetometer calibration state : (0) Ok, no calibration needed, (1) not ok, calibration needed */
	ARDRONE2_ANGLES_OUT_OF_RANGE = 1U << 19, /*!< Angles : (0) Ok, (1) out of range */
	ARDRONE2_WIND_MASK 		  	= 1U << 20, /*!< WIND MASK: (0) ok, (1) Too much wind */
	ARDRONE2_ULTRASOUND_MASK     = 1U << 21, /*!< Ultrasonic sensor : (0) Ok, (1) deaf */
	ARDRONE2_CUTOUT_MASK         = 1U << 22, /*!< Cutout system detection : (0) Not detected, (1) detected */
	ARDRONE2_PIC_VERSION_MASK    = 1U << 23, /*!< PIC Version number OK : (0) a bad version number, (1) version number is OK */
	ARDRONE2_ATCODEC_THREAD_ON   = 1U << 24, /*!< ATCodec thread ON : (0) thread OFF (1) thread ON */
	ARDRONE2_NAVDATA_THREAD_ON   = 1U << 25, /*!< Navdata thread ON : (0) thread OFF (1) thread ON */
	ARDRONE2_VIDEO_THREAD_ON     = 1U << 26, /*!< Video thread ON : (0) thread OFF (1) thread ON */
	ARDRONE2_ACQ_THREAD_ON       = 1U << 27, /*!< Acquisition thread ON : (0) thread OFF (1) thread ON */
	ARDRONE2_CTRL_WATCHDOG_MASK  = 1U << 28, /*!< CTRL watchdog : (1) delay in control execution (> 5ms), (0) control is well scheduled */
	ARDRONE2_ADC_WATCHDOG_MASK   = 1U << 29, /*!< ADC Watchdog : (1) delay in uart2 dsr (> 5ms), (0) uart2 is good */
	ARDRONE2_COM_WATCHDOG_MASK   = 1U << 30, /*!< Communication Watchdog : (1) com problem, (0) Com is ok */
  #if defined(__ARMCC_VERSION)
	ARDRONE2_EMERGENCY_MASK      = (int)0x80000000  /*!< Emergency landing : (0) no emergency, (1) emergency */
  #else
	ARDRONE2_EMERGENCY_MASK      = 1U << 31  /*!< Emergency landing : (0) no emergency, (1) emergency */
  #endif
} State_Mask_t;



typedef struct
{
	uint32 update_count;
	uint32 previous_count;
} NavDataHeader_t;


typedef struct
{
	uint16  tag;
	uint16  size;
	uint8   *data;
} NavData_Option_t;


typedef enum _navdata_tag_t
{
	ARDRONE2_NAVDATA_DEMO_TAG = 0,
	ARDRONE2_NAVDATA_TIME_TAG              = 1 ,
	ARDRONE2_NAVDATA_RAW_MEASURES_TAG      = 2 ,
	ARDRONE2_NAVDATA_PHYS_MEASURES_TAG     = 3 ,
	ARDRONE2_NAVDATA_GYROS_OFFSETS_TAG     = 4 ,
	ARDRONE2_NAVDATA_EULER_ANGLES_TAG      = 5 ,
	ARDRONE2_NAVDATA_REFERENCES_TAG        = 6 ,
	ARDRONE2_NAVDATA_TRIMS_TAG             = 7 ,
	ARDRONE2_NAVDATA_RC_REFERENCES_TAG     = 8 ,
	ARDRONE2_NAVDATA_PWM_TAG               = 9 ,
	ARDRONE2_NAVDATA_ALTITUDE_TAG          = 10 ,
	ARDRONE2_NAVDATA_VISION_RAW_TAG        = 11 ,
	ARDRONE2_NAVDATA_VISION_OF_TAG         = 12 ,
	ARDRONE2_NAVDATA_VISION_TAG            = 13 ,
	ARDRONE2_NAVDATA_VISION_PERF_TAG       = 14 ,
	ARDRONE2_NAVDATA_TRACKERS_SEND_TAG     = 15 ,
	ARDRONE2_NAVDATA_VISION_DETECT_TAG     = 16 ,
	ARDRONE2_NAVDATA_WATCHDOG_TAG          = 17 ,
	ARDRONE2_NAVDATA_ADC_DATA_FRAME_TAG    = 18 ,
	ARDRONE2_NAVDATA_VIDEO_STREAM_TAG      = 19 ,
	ARDRONE2_NAVDATA_GAMES_TAG             = 20 ,
	ARDRONE2_NAVDATA_PRESSURE_RAW_TAG      = 21 ,
	ARDRONE2_NAVDATA_MAGNETO_TAG           = 22 ,
	ARDRONE2_NAVDATA_WIND_TAG              = 23 ,
	ARDRONE2_NAVDATA_KALMAN_PRESSURE_TAG   = 24 ,
	ARDRONE2_NAVDATA_HDVIDEO_STREAM_TAG    = 25 ,
	ARDRONE2_NAVDATA_WIFI_TAG              = 26 ,
	ARDRONE2_NAVDATA_ZIMMU_3000_TAG        = 27 ,
	ARDRONE2_NAVDATA_NUM_TAGS              = 28 ,
	ARDRONE2_NAVDATA_CKS_TAG = 0xFFFF
} NavData_Tag_t;

#define ARDRONE2_OPTION_HEADER_SIZE = sizeof(uint16) + sizeof(uint16);


/*----------------------------------------------------------------------------*/
/**
 * @brief Last navdata option that *must* be included at the end of all navdata packets
 * + 6 bytes
 */
typedef struct
{
	NavDataHeader_t header;

	// Checksum for all navdatas (including options)
	uint32  	cks;
} OS_PACK NavData_Cks_t;


/*----------------------------------------------------------------------------*/
/**
 * @brief Timestamp
 * + 6 bytes
 */
typedef struct
{
	NavDataHeader_t header;

	uint32  	time;  						/*!< 32 bit value where the 11 most significant bits represents the seconds, and the 21 least significant bits are the microseconds. */
} OS_PACK ARDrone_NavData_Time_t;


/*----------------------------------------------------------------------------*/
/**
 * @brief Raw sensors measurements
 */
typedef struct
{
	NavDataHeader_t header;

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
} OS_PACK ARDrone_NavData_Raw_Measures_t;


// split next struc into magneto_navdata_t and pressure_navdata_t
typedef struct
{
	NavDataHeader_t header;

	int32   	up;
	int16   	ut;
	int32   	Temperature_meas;
 	int32   	Pression_meas;
} OS_PACK ARDrone_NavData_Pressure_Raw_t;


typedef struct
{
	NavDataHeader_t header;

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

} OS_PACK ARDrone_NavData_Magneto_t;


typedef struct
{
	NavDataHeader_t header;

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
} OS_PACK ARDrone_NavData_Wind_Speed_t;


typedef struct
{
	NavDataHeader_t header;

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
} OS_PACK ARDrone_NavData_Kalman_Pressure_t;


// TODO: depreciated struct ? remove it ?
typedef struct
{
	NavDataHeader_t header;

	int32 		vzimmuLSB;
	float 		vzfind;

} OS_PACK ARDrone_NavData_Zimmu_3000_t;


typedef struct
{
	NavDataHeader_t header;

	float   	accs_temp;
	uint16    	gyro_temp;
	float   	phys_accs[NB_ACCS];
	float   	phys_gyros[NB_GYROS];
	uint32    	alim3V3;              // 3.3volt alim [LSB]
	uint32    	vrefEpson;            // ref volt Epson gyro [LSB]
	uint32    	vrefIDG;              // ref volt IDG gyro [LSB]
} OS_PACK ARDrone_NavData_Phys_Measures_t;


typedef struct
{
	NavDataHeader_t header;

	float 		offset_g[NB_GYROS];
} OS_PACK ARDrone_NavData_Gyros_Offsets_t;


typedef struct
{
	NavDataHeader_t header;

	float   	theta_a;
	float   	phi_a;
} OS_PACK ARDrone_NavData_Euler_Angles_t;


typedef struct
{
	NavDataHeader_t header;

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

} OS_PACK ARDrone_NavData_References_t;


typedef struct
{
	NavDataHeader_t header;

	float 		angular_rates_trim_r;
	float 		euler_angles_trim_theta;
	float 		euler_angles_trim_phi;
} OS_PACK ARDrone_NavData_Trims_t;


typedef struct
{
	NavDataHeader_t header;

	int32    	rc_ref_pitch;
	int32    	rc_ref_roll;
	int32    	rc_ref_yaw;
	int32    	rc_ref_gaz;
	int32    	rc_ref_ag;
} OS_PACK ARDrone_NavData_RC_References_t;


typedef struct
{
	NavDataHeader_t header;

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
} OS_PACK ARDrone_NavData_PWM_t;


typedef struct
{
	NavDataHeader_t header;

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

} OS_PACK ARDrone_NavData_Altitude_t;


typedef struct
{
	NavDataHeader_t header;

	float 		vision_tx_raw;
	float 		vision_ty_raw;
	float 		vision_tz_raw;
} OS_PACK ARDrone_NavData_Vision_Raw_t;


typedef struct
{
	NavDataHeader_t header;

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
} OS_PACK ARDrone_NavData_Vision_t;


typedef struct
{
	NavDataHeader_t header;

	// +44 bytes
	float  		time_szo;
	float  		time_corners;
	float  		time_compute;
	float  		time_tracking;
	float  		time_trans;
	float  		time_update;
	float  		time_custom[EIM_NAVDATA_MAX_CUSTOM_TIME_SAVE];
} OS_PACK ARDrone_NavData_Vision_Perf_t;


typedef struct
{
	NavDataHeader_t header;

	int32 		locked[DEFAULT_NB_TRACKERS_WIDTH * DEFAULT_NB_TRACKERS_HEIGHT];
	screen_point_t 	point[DEFAULT_NB_TRACKERS_WIDTH * DEFAULT_NB_TRACKERS_HEIGHT];
} OS_PACK ARDrone_NavData_Trackers_Send_t;


typedef struct
{
	NavDataHeader_t header;

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
} OS_PACK ARDrone_NavData_Vision_Detect_t;


typedef struct
{
	NavDataHeader_t header;

	float   	of_dx[5];
	float   	of_dy[5];
} OS_PACK ARDrone_NavData_Vision_OF_t;


typedef struct
{
	NavDataHeader_t header;

	// +4 bytes
	int32    	watchdog;
} OS_PACK ARDrone_NavData_Watchdog_t;


typedef struct
{
	NavDataHeader_t header;

	uint32  	version;
	uint8   	data_frame[32];
} OS_PACK ARDrone_NavData_ADC_Data_Frame_t;


typedef struct
{
	NavDataHeader_t header;

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

} OS_PACK ARDrone_NavData_Video_Stream_t;


typedef enum
{
	NAVDATA_HDVIDEO_STORAGE_FIFO_IS_FULL = (1<<0),
	NAVDATA_HDVIDEO_USBKEY_IS_PRESENT   = (1<<8),
	NAVDATA_HDVIDEO_USBKEY_IS_RECORDING = (1<<9),
	NAVDATA_HDVIDEO_USBKEY_IS_FULL      = (1<<10)
} ARDrone_NavData_HDVideo_States_t;


typedef struct
{
	NavDataHeader_t header;

	uint32 		hdvideo_state;
	uint32 		storage_fifo_nb_packets;
	uint32 		storage_fifo_size;
	uint32 		usbkey_size;         /*! USB key in kbytes - 0 if no key present */
	uint32 		usbkey_freespace;    /*! USB key free space in kbytes - 0 if no key present */
	uint32 		frame_number;        /*! 'frame_number' PaVE field of the frame starting to be encoded for the HD stream */
	uint32 		usbkey_remaining_time; /*! time in seconds */

} OS_PACK ARDrone_NavData_HDVideo_Stream_t;


typedef struct
{
	NavDataHeader_t header;

	uint32 		double_tap_counter;
	uint32  	finish_line_counter;
} OS_PACK ARDrone_NavData_Games_t;


typedef struct
{
	NavDataHeader_t header;

	uint32 		link_quality;
} OS_PACK ARDrone_NavData_Wifi_t;


typedef struct
{
	uint32		header;				/*!< Always set to NAVDATA_HEADER */
	uint32		ardrone_state;    	/*!< Bit mask built from def_ardrone_state_mask_t */
	uint32		sequence;         	/*!< Sequence number, incremented for each sent packet */
	int32		vision_defined;
	NavData_Option_t	options[1];
} NavData_t;




#endif /* EIM_NAVDATATLM_H_ */
