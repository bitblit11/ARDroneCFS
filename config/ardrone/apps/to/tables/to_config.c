/*==============================================================================
** File Name: to_iloads.c
**
** Title:     TO iloads table definition
**
** $Author: $
** $Revision: $
** $Date:  $
**
** Purpose:   To provide the TO iloads table for default data config.
**
** Functions Contained:
**    None
**
**
** Limitations, Assumptions, External Events, and Notes:
**  1.   None
**
** Modification History:
**   MM/DD/YY  SCR/SDR     Author          DESCRIPTION
**   --------  ----------  -------------   -----------------------------
**   mm/dd/yy  $$$SCRxxxx  C. Writer       Build #: Code Started
**
**
**==============================================================================
*/

#ifndef _TO_CONFIG_
#define _TO_CONFIG_

#ifdef	__cplusplus
extern "C" {
#endif


/*
** Pragmas
*/

/*
** Include Files
*/
#include "app.h"
#include "tbl.h"
#include "cfe_tbl_filedef.h"
#include "to_platform_cfg.h"
#include "to_mission_cfg.h"
#include "msg_ids.h"

/*
** Local Defines
*/


/*
** Local Structure Declarations
*/

CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "to_ConfigTable", "TO.to_config", "TO config table",
    "to_config.tbl", sizeof(TO_Table_t)
};

/*
** Default TO iLoad table data
*/

#define TO_QUEUE_PILOT			0
#define TO_QUEUE_HIGH			1
#define TO_QUEUE_MEDIUM			2
#define TO_QUEUE_LOW			3
#define TO_QUEUE_EVENTS			4
#define TO_QUEUE_FILE_XFER		5

#define TO_CHANNEL_PILOT		0
#define TO_CHANNEL_TLM			1
#define TO_CHANNEL_FILE_XFER	2

TO_Table_t to_ConfigTable =
{
	TO_MAX_TLM_SUBSCRIPTIONS,
	0x1ffd,
	1000,
    {
    	/* 0 - 9 */
    	{CF_CONFIG_TLM_MID, 									1, TO_QUEUE_HIGH},
		{CF_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
		{CF_SPACE_TO_GND_PDU_MID, 								32, TO_QUEUE_FILE_XFER},
		{CF_TRANS_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{CFE_ES_APP_TLM_MID,    								1, TO_QUEUE_HIGH},
    	{CFE_ES_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{CFE_ES_MEMSTATS_TLM_MID,								1, TO_QUEUE_HIGH},
    	{CFE_ES_SHELL_TLM_MID,  								32,	TO_QUEUE_MEDIUM},
    	{CFE_EVS_EVENT_MSG_MID, 								32, TO_QUEUE_EVENTS},
    	{CFE_EVS_HK_TLM_MID,    								1, TO_QUEUE_HIGH},

    	/* 10 - 19 */
    	{CFE_SB_ALLSUBS_TLM_MID,								32, TO_QUEUE_MEDIUM},
    	{CFE_SB_HK_TLM_MID,     								1, TO_QUEUE_HIGH},
    	{CFE_SB_ONESUB_TLM_MID, 								32, TO_QUEUE_MEDIUM},
    	{CFE_SB_STATS_TLM_MID,  								1, TO_QUEUE_HIGH},
    	{CFE_TBL_HK_TLM_MID,    								1, TO_QUEUE_HIGH},
    	{CFE_TBL_REG_TLM_MID,   								1, TO_QUEUE_HIGH},
    	{CFE_TIME_DIAG_TLM_MID, 								1, TO_QUEUE_HIGH},
    	{CFE_TIME_HK_TLM_MID,   								1, TO_QUEUE_HIGH},
        {TO_HK_TLM_MID,     									1, TO_QUEUE_HIGH},
    	{HS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},

    	/* 20 - 29 */
    	{SCH_DIAG_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{SCH_HK_TLM_MID,         								1, TO_QUEUE_HIGH},
    	{EIM_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{FM_HK_TLM_MID,  										1, TO_QUEUE_HIGH},
    	{FM_OPEN_FILES_TLM_MID, 								1, TO_QUEUE_HIGH},
    	{FM_FREE_SPACE_TLM_MID, 								1, TO_QUEUE_HIGH},
    	{FM_FILE_INFO_TLM_MID, 									1, TO_QUEUE_HIGH},
    	{FM_DIR_LIST_TLM_MID, 									1, TO_QUEUE_HIGH},
    	{CS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{DS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},

    	/* 60 - 69 */
    	{DS_DIAG_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{HK_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT1_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT2_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT3_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT4_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT5_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT6_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT7_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT8_MID, 									1, TO_QUEUE_HIGH},

    	/* 70 - 79 */
    	{HK_COMBINED_PKT9_MID, 									1, TO_QUEUE_HIGH},
    	{HK_COMBINED_PKT10_MID,									1, TO_QUEUE_HIGH},
    	{LC_HK_TLM_MID,											1, TO_QUEUE_HIGH},
    	{LC_SAMPLE_AP_MID,										1, TO_QUEUE_HIGH},
    	{MD_HK_TLM_MID,											1, TO_QUEUE_HIGH},
    	{MD_DWELL_PKT_MID_BASE,									1, TO_QUEUE_HIGH},
    	{SCH_DIAG_TLM_MID,										1, TO_QUEUE_HIGH},
    	{SCH_HK_TLM_MID,										1, TO_QUEUE_HIGH},
    	{DS_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{DS_DIAG_TLM_MID,										1, TO_QUEUE_HIGH},

    	/* 80 - 89 */
    	{MM_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{SC_HK_TLM_MID, 										1, TO_QUEUE_HIGH},
    	{EIM_NAVDATA_TIME_MID, 									1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_RAW_MEASURES_MID,							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_PRESSURE_RAW_MID,							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_MAGNETO_MID,								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_WIND_SPEED_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_KALMAN_PRESSURE_MID,						1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_ZIMMU_3000_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_PHYS_MEASURES_MID,							1,  TO_QUEUE_MEDIUM},

    	/* 90 - 99 */
    	{EIM_NAVDATA_GYRO_OFFSETS_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_EULER_ANGLES_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_REFERENCES_MID, 							1,  TO_QUEUE_MEDIUM},
        {EIM_NAVDATA_TRIMS_MID, 								1,  TO_QUEUE_MEDIUM},
        {EIM_NAVDATA_RC_REFERENCES_MID, 						1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_PWM_MID, 									1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_ALTITUDE_MID, 								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_VISION_RAW_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_VISION_MID, 								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_VISION_PERF_MID, 							1,  TO_QUEUE_MEDIUM},

    	/* 100 - 109 */
    	{EIM_NAVDATA_TRACKERS_SEND_MID, 						1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_DETECT_MID, 								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_VISION_OF_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_WATCHDOG_MID, 								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_ADC_DATA_FRAME_MID, 						1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_VIDEO_STREAM_MID, 							1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_HDVIDEO_MID, 								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_GAMES_MID, 								1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_WIFI_MID, 									1,  TO_QUEUE_MEDIUM},
    	{EIM_NAVDATA_DEMO_MID,  								1,  TO_QUEUE_MEDIUM},

    	/* 110 - 119 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 120 - 129 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 130 - 139 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 140 - 149 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 150 - 159 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 160 - 169 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 170 - 179 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 180 - 189 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 190 - 199 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 200 - 209 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 210 - 219 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 220 - 229 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 230 - 239 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 240 - 249 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

    	/* 250 - 259 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

		/* 260 - 269 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},

		/* 270 - 279 */
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH},
    	{TO_UNUSED, 											1, TO_QUEUE_HIGH}
    },
	{
		{ TO_QUEUE_ENABLED,  50,  10000,     TO_CHANNEL_PILOT, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,  10,    500,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED,  30,    250,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20,       TO_CHANNEL_TLM, 	0, 0, 0, 0},
		{ TO_QUEUE_ENABLED, 100,     20,       TO_CHANNEL_FILE_XFER, 	0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,      0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,      0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,      0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,      0, 0, 0, 0, 0, 0},

		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},

		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0},
		{ TO_QUEUE_UNUSED,    0,    0, 0, 0, 0, 0, 0}
	},
	{
		{TO_CHANNEL_ENABLED, "192.168.1.2", 14550, 0 },
		{TO_CHANNEL_ENABLED, "192.168.1.2",  5011, 0 },
		{TO_CHANNEL_ENABLED, "192.168.1.2",  1234, 0 }
	}
};



/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#ifdef	__cplusplus
}
#endif

#endif /* _TO_CONFIG_ */
