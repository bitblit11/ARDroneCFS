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

#ifndef _eim_msgdefs_
#define _eim_msgdefs_

/*************************************************************************
**
** Include section
**
**************************************************************************/

#include "eim_platform_cfg.h"


/*************************************************************************
**
** SCH application definitions
**
**************************************************************************/

#define EIM_NOOP_CC             								0
#define EIM_RESET_CC            								1
#define EIM_ENABLE_NAVDATA_CC									2
#define EIM_DISABLE_NAVDATA_CC  								3
#define EIM_ACTIVATE_NAVDATA_TAG_CC  							4
#define EIM_DEACTIVATE_NAVDATA_TAG_CC  							5
#define EIM_ACTIVATE_NAVDATA_DEMO_CC							6
#define EIM_DEACTIVATE_NAVDATA_DEMO_CC							7


#define EIM_ARDRONE2_SET_NAME_CC								8
#define EIM_ARDRONE2_SET_WATCHDOG_TIMEOUT_CC					9
#define EIM_ARDRONE2_ENABLE_VIDEO_CC							10
#define EIM_ARDRONE2_DISABLE_VIDEO_CC							11
#define EIM_ARDRONE2_ENABLE_VISION_CC							12
#define EIM_ARDRONE2_DISABLE_VISION_CC							13
#define EIM_ARDRONE2_ENABLE_CONTROL_CC							14
#define EIM_ARDRONE2_DISABLE_CONTROL_CC							15
#define EIM_ARDRONE2_ENABLE_COMBINED_YAW_CONTROL_CC				16
#define EIM_ARDRONE2_DISABLE_COMBINED_YAW_CONTROL_CC			17
#define EIM_ARDRONE2_SET_MAX_ANGLE_CC							18
#define EIM_ARDRONE2_SET_MAX_ALTITUDE_CC						19
#define EIM_ARDRONE2_SET_MIN_ALTITUDE_CC						20
#define EIM_ARDRONE2_SET_MAX_IPHONE_TILT_CC						21
#define EIM_ARDRONE2_SET_MAX_VERTICAL_SPEED_CC					22
#define EIM_ARDRONE2_SET_MAX_YAW_SPEED_CC						23
#define EIM_ARDRONE2_ENABLE_OUTDOOR_MODE_CC						24
#define EIM_ARDRONE2_DISABLE_OUTDOOR_MODE_CC					25
#define EIM_ARDRONE2_ENABLE_OUTDOOR_SHELL_CC					26
#define EIM_ARDRONE2_DISABLE_OUTDOOR_SHELL_CC					27
#define EIM_ARDRONE2_ENABLE_AUTONOMOUS_MODE_CC					28
#define EIM_ARDRONE2_DISABLE_AUTONOMOUS_MODE_CC					29
#define EIM_ARDRONE2_SET_MANUAL_TRIM_CC							30
#define EIM_ARDRONE2_SET_MAX_INDOOR_ANGLE_CC					31
#define EIM_ARDRONE2_SET_MAX_INDOOR_VERTICAL_SPEED_CC			32
#define EIM_ARDRONE2_ENABLE_INDOOR_CONTROL_CC					33
#define EIM_ARDRONE2_DISABLE_INDOOR_CONTROL_CC					34
#define EIM_ARDRONE2_ENABLE_INDOOR_COMBINED_YAW_CONTROL_CC		35
#define EIM_ARDRONE2_DISABLE_INDOOR_COMBINED_YAW_CONTROL_CC		36
#define EIM_ARDRONE2_SET_MAX_OUTDOOR_ANGLE_CC					37
#define EIM_ARDRONE2_SET_MAX_OUTDOOR_VERTICAL_SPEED_CC			38
#define EIM_ARDRONE2_ENABLE_OUTDOOR_CONTROL_CC					39
#define EIM_ARDRONE2_DISABLE_OUTDOOR_CONTROL_CC					40
#define EIM_ARDRONE2_ENABLE_OUTDOOR_COMBINED_YAW_CONTROL_CC		41
#define EIM_ARDRONE2_DISABLE_OUTDOOR_COMBINED_YAW_CONTROL_CC	42
#define EIM_ARDRONE2_SET_FLYING_MODE_CC							43
#define EIM_ARDRONE2_SET_ROUNDEL_HOVERING_RANGE_CC				44
#define EIM_ARDRONE2_EXECUTE_FLIGHT_ANIMATION_CC				45
#define EIM_ARDRONE2_SET_SINGLE_PLAYER_SSID_CC					46
#define EIM_ARDRONE2_SET_MULTI_PLAYER_SSID_CC					47
#define EIM_ARDRONE2_SET_WIFI_MODE_CC							48
#define EIM_ARDRONE2_SET_WIFI_RATE_CC							49
#define EIM_ARDRONE2_SET_OWNER_MAC_CC							50
#define EIM_ARDRONE2_SET_ULTRASOUND_FREQ_CC						51
#define EIM_ARDRONE2_SET_ULTRASOUND_WATCHDOG_CC					52
#define EIM_ARDRONE2_SET_VIDEO_CODEC_FPS_CC						53
#define EIM_ARDRONE2_SET_VIDEO_CODEC_CC							54
#define EIM_ARDRONE2_SET_VIDEO_SLICES_CC						55
#define EIM_ARDRONE2_SET_VIDEO_LIVE_SOCKET_CC					56
#define EIM_ARDRONE2_SET_VIDEO_BITRATE_CC						57
#define EIM_ARDRONE2_SET_MAX_VIDEO_BITRATE_CC					58
#define EIM_ARDRONE2_SET_VIDEO_BITRATE_CONTROL_MODE_CC			59
#define EIM_ARDRONE2_SET_VIDEO_BITRATE_STORAGE_CC				60
#define EIM_ARDRONE2_SET_VIDEO_CHANNEL_CC						61
#define EIM_ARDRONE2_ENABLE_VIDEO_ON_USB_CC						62
#define EIM_ARDRONE2_DISABLE_VIDEO_ON_USB_CC					63
#define EIM_ARDRONE2_SET_VIDEO_FILE_INDEX_CC					64
#define EIM_ARDRONE2_SET_LED_ANIMATION_CC						65
#define EIM_ARDRONE2_SET_ENEMY_COLORS_DETECT_CC					66
#define EIM_ARDRONE2_SET_GROUNDSTRIPE_COLORS_DETECT_CC			67
#define EIM_ARDRONE2_ENABLE_ENEMY_OUTDOOR_SHELL_DETECT_CC		68
#define EIM_ARDRONE2_DISABLE_ENEMY_OUTDOOR_SHELL_DETECT_CC		69
#define EIM_ARDRONE2_SET_DETECT_TYPE_CC							70
#define EIM_ARDRONE2_SET_DETECTIONS_SELECT_H_CC					71
#define EIM_ARDRONE2_SET_DETECTIONS_SELECT_V_HSYNC_CC			72
#define EIM_ARDRONE2_SET_DETECTIONS_SELECT_V_CC					73
#define EIM_ARDRONE2_USERBOX_STOP_CC							74
#define EIM_ARDRONE2_USERBOX_START_CC							75
#define EIM_ARDRONE2_USERBOX_SCREENSHOT_CC						76
#define EIM_ARDRONE2_USERBOX_CANCEL_CC							77
#define EIM_ARDRONE2_SET_LATITUDE_CC							78
#define EIM_ARDRONE2_SET_LONGITUDE_CC							79
#define EIM_ARDRONE2_SET_ALTITUDE_CC							80
#define EIM_ARDRONE2_SET_APPLICATION_ID_CC						81
#define EIM_ARDRONE2_SET_APPLICATION_DESCRIPTION_CC				82
#define EIM_ARDRONE2_SET_PROFILE_ID_CC							83
#define EIM_ARDRONE2_SET_PROFILE_DESCRIPTION_CC					84
#define EIM_ARDRONE2_SET_SESSION_ID_CC							85
#define EIM_ARDRONE2_SET_SESSION_DESCRIPTION_CC					86

#define EIM_E_STOP_CC											87
#define EIM_E_STOP_RESET_CC		    							88
#define EIM_LAUNCH_CC               							89
#define EIM_LAND_CC                 							90
#define EIM_HOVER_CC                							91
#define EIM_ROLL_CC                 							92
#define EIM_PITCH_CC                							93
#define EIM_YAW_CC                  							94
#define EIM_VERTICAL_CC             							95
#define EIM_MOVE_CC												96
#define EIM_SET_FLAT_TRIM_CC									97
#define EIM_CALIBRATE_MAGNETOMETER_CC							98
#define EIM_SET_CONTROL_MODE_CC									99


#endif /* _eim_msgdefs_ */

/************************/
/*  End of File Comment */
/************************/

