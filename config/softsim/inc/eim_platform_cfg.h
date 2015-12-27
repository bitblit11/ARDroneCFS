#ifndef _eim_platform_cfg_h_
#define _eim_platform_cfg_h_



/*************************************************************************
** Macro definitions
**************************************************************************/


#define EIM_NAVDATA_SEQUENCE_DEFAULT  			1
#define EIM_CMD_PORT                 			5554
#define EIM_NAV_DATA_PORT            			5554
#define EIM_MAX_NAV_BUFFER_SIZE					1024
#define EIM_MAX_AT_BUFFER_SIZE					1024
//#define EIM_WIFI_IP 							"10.0.254.86"
//#define EIM_WIFI_IP 							"127.0.0.1"
#define EIM_WIFI_IP 							"192.168.1.1"
#define EIM_AT_PORT   							5556
#define EIM_WATCHDOG_PERIOD						1000000
#define EIM_NAVDATA_MAX_CUSTOM_TIME_SAVE 		20
#define EIM_NB_NAVDATA_DETECTION_RESULTS 		4


/**
**  \eimcfg Software Bus Command Pipe Depth
**
**  \par Description:
**       Dictates the number of messages to SCH that can be queued while awaiting
**       processing by the SCH Application.
**
**  \par Limits
**       Must be greater than zero
*/
#define EIM_PIPE_DEPTH      12              /**< \brief EIM Command Pipe Depth */

#define EIM_ARDRONE2_DEFAULT_SKIPFRAMES		199


/** \eimcfg Mission specific version number for EIM application
**  
**  \par Description:
**       An application version number consists of four parts:
**       major version number, minor version number, revision
**       number and mission specific revision number. The mission
**       specific revision number is defined here and the other
**       parts are defined in "sch_version.h".
**
**  \par Limits:
**       Must be defined as a numeric value that is greater than
**       or equal to zero.
*/

#define EIM_MISSION_REV            0



//#define EIM_NAVDATA_SEQUENCE_DEFAULT  	1
//#define EIM_CMD_PORT                 	5554
//#define EIM_NAV_DATA_PORT            	5554
//#define EIM_MAX_NAV_BUFFER_SIZE			1024
//#define EIM_MAX_AT_BUFFER_SIZE			1024
//#define EIM_WIFI_IP 					"192.168.1.1"
//#define EIM_AT_PORT   					5556
//#define EIM_WATCHDOG_PERIOD				1000000


#endif /* _eim_platform_cfg_h_ */

/************************/
/*  End of File Comment */
/************************/
