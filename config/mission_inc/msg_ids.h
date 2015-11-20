#ifndef _EFT1_MSG_IDS_H_
#define _EFT1_MSG_IDS_H_

#include "cfe_msgids.h"

/* Commands */

/* TO 										*/
/* Range: 0x900 - 0x90f 					*/
#define TO_CMD_MID 						0x1900
#define TO_SEND_HK_MID 					0x1901
#define TO_DATA_TYPES_MID				0x0902
#define TO_HK_TLM_MID 					0x0903
#define TO_SEND_TLM_MID					0x0904

/* CI 										*/
/* Range: 0x900 - 0x90f 					*/
#define CI_CMD_MID 						0x1905
#define CI_SEND_HK_MID 					0x1906
#define CI_HK_TLM_MID 					0x0907
#define CI_READ_CMD_MID					0x1908
#define FIXHAWK_MAVLINK_IN_MSG_MID		0x0909

/* CF										*/
/* Range: 0x910 - 0x92f						*/
#define CF_CMD_MID                      0x1910
#define CF_INCOMING_PDU_MID             0x1FFD
#define CF_SEND_HK_MID                  0x1912
#define CF_SPARE1_CMD_MID               0x1913
#define CF_SPARE2_CMD_MID               0x1914
#define CF_SPARE3_CMD_MID               0x1915
#define CF_SPARE4_CMD_MID               0x1916
#define CF_SPARE5_CMD_MID               0x1917
#define CF_WAKE_UP_REQ_CMD_MID          0x1918
#define CF_CONFIG_TLM_MID               0x0919
#define CF_HK_TLM_MID                   0x091a
#define CF_SPARE0_TLM_MID               0x091b
#define CF_SPARE1_TLM_MID               0x091c
#define CF_SPARE2_TLM_MID               0x091d
#define CF_SPARE3_TLM_MID               0x091e
#define CF_SPARE4_TLM_MID               0x091f
#define CF_TRANS_TLM_MID                0x0920
/*
** NOTE: the definition below is NOT used by the code. The code uses the MsgId
** defined in the CF table. For the purpose of keeping all CF related message
** IDs defined in this file, the CF table should reference this macro
** definition.
*/
#define CF_SPACE_TO_GND_PDU_MID         0x1FFE


/* CS										*/
/* Range: 0x930 - 0x93f						*/
#define CS_CMD_MID						0x1930
#define CS_BACKGROUND_CYCLE_MID			0x1931
#define CS_SEND_HK_MID					0x1932
#define CS_HK_TLM_MID					0x0933


/* DS										*/
/* Range: 0x940 - 0x94f						*/
#define DS_CMD_MID						0x1940
#define DS_SEND_HK_MID					0x1941
#define DS_HK_TLM_MID					0x0942
#define DS_DIAG_TLM_MID					0x0943


/* EIM										*/
/* Range: 0x950 - 0x97f						*/
#define EIM_CMD_MID						0x1950
#define EIM_SEND_HK_MID					0x1951
#define EIM_HK_TLM_MID					0x0952
#define EIM_IMU_MID						0x0953
#define EIM_NAVDATA_DEMO_MID			0x0954
#define EIM_NAVDATA_TIME_MID			0x0955
#define EIM_NAVDATA_RAW_MEASURES_MID	0x0956
#define EIM_NAVDATA_PRESSURE_RAW_MID	0x0957
#define EIM_NAVDATA_MAGNETO_MID			0x0958
#define EIM_NAVDATA_WIND_SPEED_MID		0x0959
#define EIM_NAVDATA_KALMAN_PRESSURE_MID	0x095a
#define EIM_NAVDATA_ZIMMU_3000_MID		0x095b
#define EIM_NAVDATA_PHYS_MEASURES_MID	0x095c
#define EIM_NAVDATA_GYRO_OFFSETS_MID	0x095d
#define EIM_NAVDATA_EULER_ANGLES_MID	0x095e
#define EIM_NAVDATA_REFERENCES_MID		0x095f
#define EIM_NAVDATA_TRIMS_MID			0x0960
#define EIM_NAVDATA_RC_REFERENCES_MID	0x0961
#define EIM_NAVDATA_PWM_MID				0x0962
#define EIM_NAVDATA_ALTITUDE_MID		0x0963
#define EIM_NAVDATA_VISION_RAW_MID		0x0964
#define EIM_NAVDATA_VISION_MID			0x0965
#define EIM_NAVDATA_VISION_PERF_MID		0x0966
#define EIM_NAVDATA_TRACKERS_SEND_MID	0x0967
#define EIM_NAVDATA_DETECT_MID			0x0968
#define EIM_NAVDATA_VISION_OF_MID		0x0969
#define EIM_NAVDATA_WATCHDOG_MID		0x096a
#define EIM_NAVDATA_ADC_DATA_FRAME_MID	0x096b
#define EIM_NAVDATA_VIDEO_STREAM_MID	0x096c
#define EIM_NAVDATA_HDVIDEO_MID			0x096d
#define EIM_NAVDATA_GAMES_MID			0x096e
#define EIM_NAVDATA_WIFI_MID			0x096f


/* FM										*/
/* Range: 0x980 - 0x98f						*/
#define FM_CMD_MID  					0x1980
#define FM_SEND_HK_MID					0x1981
#define FM_HK_TLM_MID       			0x0982
#define FM_OPEN_FILES_TLM_MID			0x0983
#define FM_FREE_SPACE_TLM_MID			0x0984
#define FM_FILE_INFO_TLM_MID			0x0985
#define FM_DIR_LIST_TLM_MID				0x0986


/* HK										*/
/* Range: 0x990 - 0x99f						*/
#define HK_CMD_MID  					0x1990
#define HK_SEND_HK_MID					0x1991
#define HK_SEND_COMBINED_PKT_MID    	0x1992
#define HK_HK_TLM_MID       			0x0993
#define HK_COMBINED_PKT1_MID			0x0994
#define HK_COMBINED_PKT2_MID			0x0995
#define HK_COMBINED_PKT3_MID			0x0996
#define HK_COMBINED_PKT4_MID			0x0997
#define HK_COMBINED_PKT5_MID			0x0998
#define HK_COMBINED_PKT6_MID			0x0999
#define HK_COMBINED_PKT7_MID			0x099a
#define HK_COMBINED_PKT8_MID			0x099b
#define HK_COMBINED_PKT9_MID			0x099c
#define HK_COMBINED_PKT10_MID			0x099d


/* HS										*/
/* Range: 0x9a0 - 0x9af						*/
#define HS_CMD_MID     					0x19a0
#define HS_SEND_HK_MID      			0x19a1
#define HS_WAKEUP_MID       			0x19a2
#define HS_HK_TLM_MID       			0x09a3
#define HS_CUSTOM_HK_TLM_MID			0x09a4


/* LC										*/
/* Range: 0x9b0 - 0x9bf						*/
#define LC_HK_TLM_MID					0x09b0
#define LC_SEND_HK_MID					0x19b1
#define LC_CMD_MID						0x19b2
#define LC_SAMPLE_AP_MID				0x09b3


/* MM										*/
/* Range: 0x9c0 - 0x9c2						*/
#define MM_CMD_MID        				0x19c0
#define MM_SEND_HK_MID    				0x19c1
#define MM_HK_TLM_MID     				0x09c2


/* MD										*/
/* Range: 0x9c3 - 0x9cf						*/
#define MD_CMD_MID						0x19c3
#define MD_WAKEUP_MID					0x19c4
#define MD_SEND_HK_MID					0x19c5
#define MD_HK_TLM_MID					0x09c6
#define MD_DWELL_PKT_MID_BASE			0x09c7


/* NAV										*/
/* Range: 0x9d0 - 0x9df						*/
#define NAV_CMD_MID						0x19d0
#define NAV_SEND_HK_MID					0x19d1
#define NAV_FUNC2_MID					0x19d2
#define NAV_FUNC3_MID					0x19d3
#define NAV_FUNC4_MID					0x19d4
#define NAV_FUNC5_MID					0x19d5
#define NAV_FUNC6_MID					0x19d6
#define NAV_FUNC7_MID					0x19d7
#define NAV_FUNC8_MID					0x19d8
#define NAV_FUNC9_MID					0x19d9
#define NAV_FUNC10_MID					0x19da
#define NAV_HK_TLM_MID					0x09db
#define NAV_HIGH_RATE_NAV_MID			0x09dc


/* SC										*/
/* Range: 0x9e0 - 0x9e3						*/
#define SC_CMD_MID                      0x19e0
#define SC_SEND_HK_MID                  0x19e1
#define SC_1HZ_WAKEUP_MID               0x19e2
#define SC_HK_TLM_MID                   0x09e3


/* SCH										*/
/* Range: 0x9e4 - 0x9ef						*/
#define SCH_CMD_MID         			0x19e4
#define SCH_SEND_HK_MID     			0x19e5
#define SCH_UNUSED_MID      			0
#define SCH_DIAG_TLM_MID				0x09e7
#define SCH_HK_TLM_MID					0x09e8


/* GOPRO									*/
/* Range: 0x9f0 - 0x9ff						*/
#define GOPRO_CMD_MID						0x19f0
#define GOPRO_SEND_HK_MID					0x19f1
#define GOPRO_HK_TLM_MID					0x09f2


/* FIXHAWK																*/
/* Range: 0x9f0 - 0x9ff													*/
#define FIXHAWK_CMD_MID												0x1a00
#define FIXHAWK_SEND_HK_MID											0x1a01
#define FIXHAWK_HK_TLM_MID											0x0a02
#define MAVLINK_CFS_MSG_ID_HEARTBEAT								0x0a03 /* 515 */
#define MAVLINK_CFS_MSG_ID_ATTITUDE_QUATERNION_COV					0x0a04 /* 516 */
#define MAVLINK_CFS_MSG_ID_ATTITUDE_QUATERNION						0x0a05 /* 517 */
#define MAVLINK_CFS_MSG_ID_ATTITUDE_TARGET							0x0a06 /* 518 */
#define MAVLINK_CFS_MSG_ID_ATTITUDE									0x0a07 /* 519 */
#define MAVLINK_CFS_MSG_ID_AUTH_KEY									0x0a08 /* 520 */
#define MAVLINK_CFS_MSG_ID_AUTOPILOT_VERSION						0x0a09 /* 521 */
#define MAVLINK_CFS_MSG_ID_BATTERY_STATUS							0x0a0a /* 522 */
#define MAVLINK_CFS_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK				0x0a0b /* 523 */
#define MAVLINK_CFS_MSG_ID_CHANGE_OPERATOR_CONTROL					0x0a0c /* 524 */
#define MAVLINK_CFS_MSG_ID_COMMAND_ACK								0x0a0d /* 525 */
#define MAVLINK_CFS_MSG_ID_COMMAND_INT								0x0a0e /* 526 */
#define MAVLINK_CFS_MSG_ID_COMMAND_LONG								0x0a0f /* 527 */
#define MAVLINK_CFS_MSG_ID_DATA_STREAM								0x0a10 /* 528 */
#define MAVLINK_CFS_MSG_ID_DATA_TRANSMISSION_HANDSHAKE				0x0a11 /* 529 */
#define MAVLINK_CFS_MSG_ID_DEBUG_VECT								0x0a12 /* 530 */
#define MAVLINK_CFS_MSG_ID_DEBUG									0x0a13 /* 531 */
#define MAVLINK_CFS_MSG_ID_DISTANCE_SENSOR							0x0a14 /* 532 */
#define MAVLINK_CFS_MSG_ID_ENCAPSULATED_DATA						0x0a15 /* 533 */
#define MAVLINK_CFS_MSG_ID_FILE_TRANSFER_PROTOCOL					0x0a16 /* 534 */
#define MAVLINK_CFS_MSG_ID_GLOBAL_POSITION_INT_COV					0x0a17 /* 535 */
#define MAVLINK_CFS_MSG_ID_GLOBAL_POSITION_INT						0x0a18 /* 536 */
#define MAVLINK_CFS_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE			0x0a19 /* 537 */
#define MAVLINK_CFS_MSG_ID_GPS_GLOBAL_ORIGIN						0x0a1a /* 538 */
#define MAVLINK_CFS_MSG_ID_GPS_INJECT_DATA							0x0a1b /* 539 */
#define MAVLINK_CFS_MSG_ID_GPS_RAW_INT								0x0a1c /* 540 */
#define MAVLINK_CFS_MSG_ID_GPS_RTK									0x0a1d /* 541 */
#define MAVLINK_CFS_MSG_ID_GPS_STATUS								0x0a1e /* 542 */
#define MAVLINK_CFS_MSG_ID_GPS2_RAW									0x0a1f /* 543 */
#define MAVLINK_CFS_MSG_ID_HIGHRES_IMU								0x0a20 /* 544 */
#define MAVLINK_CFS_MSG_ID_HIL_CONTROLS								0x0a21 /* 545 */
#define MAVLINK_CFS_MSG_ID_HIL_GPS									0x0a22 /* 546 */
#define MAVLINK_CFS_MSG_ID_HIL_OPTICAL_FLOW							0x0a23 /* 547 */
#define MAVLINK_CFS_MSG_ID_HIL_RC_INPUTS_RAW						0x0a24 /* 548 */
#define MAVLINK_CFS_MSG_ID_HIL_SENSOR								0x0a25 /* 549 */
#define MAVLINK_CFS_MSG_ID_HIL_STATE_QUATERNION						0x0a26 /* 550 */
#define MAVLINK_CFS_MSG_ID_HIL_STATE								0x0a27 /* 551 */
#define MAVLINK_CFS_MSG_ID_LOCAL_POSITION_NED_COV					0x0a28 /* 552 */
#define MAVLINK_CFS_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET	0x0a29 /* 553 */
#define MAVLINK_CFS_MSG_ID_LOCAL_POSITION_NED						0x0a2a /* 554 */
#define MAVLINK_CFS_MSG_ID_LOG_DATA									0x0a2b /* 555 */
#define MAVLINK_CFS_MSG_ID_LOG_ENTRY								0x0a2c /* 556 */
#define MAVLINK_CFS_MSG_ID_LOG_ERASE								0x0a2d /* 557 */
#define MAVLINK_CFS_MSG_ID_LOG_REQUEST_DATA							0x0a2e /* 558 */
#define MAVLINK_CFS_MSG_ID_LOG_REQUEST_END							0x0a2f /* 559 */
#define MAVLINK_CFS_MSG_ID_LOG_REQUEST_LIST							0x0a30 /* 560 */
#define MAVLINK_CFS_MSG_ID_MANUAL_CONTROL							0x0a31 /* 561 */
#define MAVLINK_CFS_MSG_ID_MANUAL_SETPOINT							0x0a32 /* 562 */
#define MAVLINK_CFS_MSG_ID_MEMORY_VECT								0x0a33 /* 563 */
#define MAVLINK_CFS_MSG_ID_MISSION_ACK								0x0a34 /* 564 */
#define MAVLINK_CFS_MSG_ID_MISSION_CLEAR_ALL						0x0a35 /* 565 */
#define MAVLINK_CFS_MSG_ID_MISSION_COUNT							0x0a36 /* 566 */
#define MAVLINK_CFS_MSG_ID_MISSION_CURRENT							0x0a37 /* 567 */
#define MAVLINK_CFS_MSG_ID_MISSION_ITEM_INT							0x0a38 /* 568 */
#define MAVLINK_CFS_MSG_ID_MISSION_ITEM_REACHED						0x0a39 /* 569 */
#define MAVLINK_CFS_MSG_ID_MISSION_ITEM								0x0a3a /* 570 */
#define MAVLINK_CFS_MSG_ID_MISSION_REQUEST_LIST						0x0a3b /* 571 */
#define MAVLINK_CFS_MSG_ID_MISSION_REQUEST_PARTIAL_LIST				0x0a3c /* 572 */
#define MAVLINK_CFS_MSG_ID_MISSION_REQUEST							0x0a3d /* 573 */
#define MAVLINK_CFS_MSG_ID_MISSION_SET_CURRENT						0x0a3e /* 574 */
#define MAVLINK_CFS_MSG_ID_MISSION_WRITE_PARTIAL_LIST				0x0a3f /* 575 */
#define MAVLINK_CFS_MSG_ID_MISSION_VALUE_FLOAT						0x0a40 /* 576 */
#define MAVLINK_CFS_MSG_ID_NAMED_VALUE_FLOAT						0x0a41 /* 577 */
#define MAVLINK_CFS_MSG_ID_NAMED_VALUE_INT							0x0a42 /* 578 */
#define MAVLINK_CFS_MSG_ID_NAV_CONTROLLER_OUTPUT					0x0a43 /* 579 */
#define MAVLINK_CFS_MSG_ID_OMNIDIRECTIONAL_FLOW						0x0a44 /* 580 */
#define MAVLINK_CFS_MSG_ID_OPTICAL_FLOW								0x0a45 /* 581 */
#define MAVLINK_CFS_MSG_ID_PARAM_REQUEST_LIST						0x0a46 /* 582 */
#define MAVLINK_CFS_MSG_ID_PARAM_REQUEST_READ						0x0a47 /* 583 */
#define MAVLINK_CFS_MSG_ID_PARAM_SET								0x0a48 /* 584 */
#define MAVLINK_CFS_MSG_ID_PARAM_VALUE								0x0a49 /* 585 */
#define MAVLINK_CFS_MSG_ID_PING										0x0a4a /* 586 */
#define MAVLINK_CFS_MSG_ID_POSITION_TARGET_GLOBAL_INT				0x0a4b /* 587 */
#define MAVLINK_CFS_MSG_ID_POSITION_TARGET_LOCAL_NED				0x0a4c /* 588 */
#define MAVLINK_CFS_MSG_ID_POWER_STATUS								0x0a4d /* 589 */
#define MAVLINK_CFS_MSG_ID_RADIO_STATUS								0x0a4e /* 590 */
#define MAVLINK_CFS_MSG_ID_RAW_IMU									0x0a4f /* 591 */
#define MAVLINK_CFS_MSG_ID_RAW_PRESSURE								0x0a50 /* 592 */
#define MAVLINK_CFS_MSG_ID_RC_CHANNELS_OVERRIDE						0x0a51 /* 593 */
#define MAVLINK_CFS_MSG_ID_RC_CHANNELS_RAW							0x0a52 /* 594 */
#define MAVLINK_CFS_MSG_ID_RC_CHANNELS_SCALED						0x0a53 /* 595 */
#define MAVLINK_CFS_MSG_ID_RC_CHANNELS								0x0a54 /* 596 */
#define MAVLINK_CFS_MSG_ID_REQUEST_DATA_STREAM						0x0a55 /* 597 */
#define MAVLINK_CFS_MSG_ID_SAFETY_ALLOWED_AREA						0x0a56 /* 598 */
#define MAVLINK_CFS_MSG_ID_SAFETY_SET_ALLOWED_AREA					0x0a57 /* 599 */
#define MAVLINK_CFS_MSG_ID_SCALED_IMU								0x0a58 /* 600 */
#define MAVLINK_CFS_MSG_ID_SCALED_IMU2								0x0a59 /* 601 */
#define MAVLINK_CFS_MSG_ID_SCALED_PRESSURE							0x0a5a /* 602 */
#define MAVLINK_CFS_MSG_ID_SERIAL_CONTROL							0x0a5b /* 603 */
#define MAVLINK_CFS_MSG_ID_SERVO_OUTPUT_RAW							0x0a5c /* 604 */
#define MAVLINK_CFS_MSG_ID_SET_ATTITUDE_TARGET						0x0a5d /* 605 */
#define MAVLINK_CFS_MSG_ID_SET_GPS_GLOBAL_ORIGIN					0x0a5e /* 606 */
#define MAVLINK_CFS_MSG_ID_SET_MODE									0x0a5f /* 607 */
#define MAVLINK_CFS_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT			0x0a60 /* 608 */
#define MAVLINK_CFS_MSG_ID_SET_POSITION_TARGET_LOCAL_NED			0x0a61 /* 609 */
#define MAVLINK_CFS_MSG_ID_SIM_STATE								0x0a62 /* 610 */
#define MAVLINK_CFS_MSG_ID_STATUSTEXT								0x0a63 /* 611 */
#define MAVLINK_CFS_MSG_ID_SYS_STATUS								0x0a64 /* 612 */
#define MAVLINK_CFS_MSG_ID_SYSTEM_TIME								0x0a65 /* 613 */
#define MAVLINK_CFS_MSG_ID_TERRAIN_CHECK							0x0a66 /* 614 */
#define MAVLINK_CFS_MSG_ID_TERRAIN_DATA								0x0a67 /* 615 */
#define MAVLINK_CFS_MSG_ID_TERRAIN_REPORT							0x0a68 /* 616 */
#define MAVLINK_CFS_MSG_ID_TERRAIN_REQUEST							0x0a69 /* 617 */
#define MAVLINK_CFS_MSG_ID_V2_EXTENSION								0x0a6a /* 618 */
#define MAVLINK_CFS_MSG_ID_VFR_HUD									0x0a6b /* 619 */
#define MAVLINK_CFS_MSG_ID_VICON_POSITION_ESTIMATE					0x0a6c /* 620 */
#define MAVLINK_CFS_MSG_ID_VISION_POSITION_ESTIMATE					0x0a6d /* 621 */
#define MAVLINK_CFS_MSG_ID_VISION_SPEED_ESTIMATE					0x0a6e /* 622 */

#define MAVLINK_CFS_MSG_ID_ATTITUDE_CONTROL							0x0a6f /* 623 */
#define MAVLINK_CFS_MSG_ID_BRIEF_FEATURE							0x0a70 /* 624 */
#define MAVLINK_CFS_MSG_ID_DETECTION_STATS							0x0a71 /* 625 */
#define MAVLINK_CFS_MSG_ID_IMAGE_AVAILABLE							0x0a72 /* 626 */
#define MAVLINK_CFS_MSG_ID_IMAGE_TRIGGER_CONTROL					0x0a73 /* 627 */
#define MAVLINK_CFS_MSG_ID_IMAGE_TRIGGERED							0x0a74 /* 628 */
#define MAVLINK_CFS_MSG_ID_MARKER									0x0a75 /* 629 */
#define MAVLINK_CFS_MSG_ID_ONBOARD_HEALTH							0x0a76 /* 630 */
#define MAVLINK_CFS_MSG_ID_PATTERN_DETECTED							0x0a77 /* 631 */
#define MAVLINK_CFS_MSG_ID_POINT_OF_INTEREST_CONNECTION				0x0a78 /* 632 */
#define MAVLINK_CFS_MSG_ID_POINT_OF_INTEREST						0x0a79 /* 633 */
#define MAVLINK_CFS_MSG_ID_POSITION_CONTROL_SETPOINT				0x0a7a /* 634 */
#define MAVLINK_CFS_MSG_ID_RAW_AUX									0x0a7b /* 635 */
#define MAVLINK_CFS_MSG_ID_SET_CAM_SHUTTER							0x0a7c /* 636 */
#define MAVLINK_CFS_MSG_ID_SET_POSITION_CONTROL_OFFSET				0x0a7d /* 637 */
#define MAVLINK_CFS_MSG_ID_WATCHDOG_COMMAND							0x0a7e /* 638 */
#define MAVLINK_CFS_MSG_ID_WATCHDOG_HEARTBEAT						0x0a7f /* 639 */
#define MAVLINK_CFS_MSG_ID_WATCHDOG_PROCESS_INFO					0x0a80 /* 640 */
#define MAVLINK_CFS_MSG_ID_WATCHDOG_PROCESS_STATUS					0x0a81 /* 641 */

#define FIXHAWK_SEND_HEARTBEAT_MID									0x1a82
#define FIXHAWK_MAVLINK_OUT_MSG_MID									0x0a83


/* NAVSPARK											*/
/* Range: 0xb00 - 0xb0f								*/
#define NAVSPARK_CMD_MID							0x1b00
#define NAVSPARK_SEND_HK_MID						0x1b01
#define NAVSPARK_HK_TLM_MID							0x0b02
#define NAVSPARK_READ_DEVICE_MID					0x1b03
#define NAVSPARK_SOFTWARE_VERSION_TLM_MID			0x0b05
#define NAVSPARK_ACK_TLM_MID						0x0b06
#define NAVSPARK_NACK_TLM_MID						0x0b07
#define NAVSPARK_POS_UPDATE_RATE_TLM_MID			0x0b08
#define NAVSPARK_GLONASS_EPHEM_TLM_MID				0x0b09
#define NAVSPARK_GPS_EPHEM_TLM_MID					0x0b0a
#define NAVSPARK_MEAS_EPOCH_TLM_MID					0x0b0b
#define NAVSPARK_SV_AND_CHANNEL_STATUS_TLM_MID		0x0b0c
#define NAVSPARK_RCV_NAV_STATUS_TLM_MID				0x0b0d
#define NAVSPARK_GPS_SUBFRM_DATA_TLM_MID			0x0b0e
#define NAVSPARK_SOFTWARE_CRC_TLM_MID				0x0b0f
#define NAVSPARK_RAW_MEAS_TLM_MID					0x0b10
#define NAVSPARK_BIN_MEAS_DATA_OUT_STATUS_TLM_MID	0x0b11
#define NAVSPARK_GNSS_DATUM_TLM_MID					0x0b12
#define NAVSPARK_GNSS_DOPMASK_TLM_MID				0x0b13
#define NAVSPARK_ELEV_AND_CNR_MASK_TLM_MID			0x0b14
#define NAVSPARK_SBAS_STATUS_TLM_MID				0x0b15
#define NAVSPARK_QZSS_STATUS_TLM_MID				0x0b16
#define NAVSPARK_SAEE_STATUS_TLM_MID				0x0b17
#define NAVSPARK_BOOT_STATUS_TLM_MID				0x0b18
#define NAVSPARK_EXT_NMEA_MSG_INT_TLM_MID			0x0b19
#define NAVSPARK_INT_DET_STATUS_TLM_MID				0x0b1a
#define NAVSPARK_GPS_PARAM_SRCH_ENG_NUM_TLM_MID		0x0b1b
#define NAVSPARK_GNSS_NAV_MODE_TLM_MID				0x0b1c
#define NAVSPARK_1PPS_PULSE_WIDTH_TLM_MID			0x0b1d
#define NAVSPARK_1PPS_FREQ_OUT_TLM_MID				0x0b1e
#define NAVSPARK_POWER_MODE_TLM_MID					0x0b1f
#define NAVSPARK_NAV_DATA_TLM_MID					0x0b20

#define GN_WAKEUP_MID								0x1b30
#define GN_SEND_HK_MID								0x1b31
#define GN_CMD_MID									0x1b32
#define GN_HK_TLM_MID								0x0b33

/* VID													*/
/* Range: 0xb20 - 0xb2f									*/
#define VID_CMD_MID									0x1b40
#define VID_SEND_HK_MID								0x1b41
#define VID_HK_TLM_MID								0x0b42
#define VID_GRAB_FRAME_MID							0x1b43
#define VID_FWD_CAM_FRAME_MID			    		0x0b44


#endif
