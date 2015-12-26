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

#ifndef EIM_CMDS_H_
#define EIM_CMDS_H_

#include "cfe.h"

typedef enum
{
	EIM_CMD_SUCCESS = 0,
	EIM_CMD_FAILED	= 1
} EIM_CmdResponse_t;

typedef enum {
	EIM_WIFI_MODE_ACCESS_POINT = 0,
	EIM_WIFI_MODE_ADHOC = 1,
	EIM_WIFI_MODE_NETWORK = 2
} EIM_WifiMode_t;

typedef enum {
	EIM_VIDEO_CHANNEL_FIRST=0,
	EIM_VIDEO_CHANNEL_HORI=EIM_VIDEO_CHANNEL_FIRST,
	EIM_VIDEO_CHANNEL_VERT,
	EIM_VIDEO_CHANNEL_LARGE_HORI_SMALL_VERT,
	EIM_VIDEO_CHANNEL_LARGE_VERT_SMALL_HORI,
	EIM_VIDEO_CHANNEL_LAST=EIM_VIDEO_CHANNEL_LARGE_VERT_SMALL_HORI,
	EIM_VIDEO_CHANNEL_NEXT,
} EIM_VideoChannel_t;

typedef enum {
	EIM_LED_ANIMATION_BLINK_GREEN_RED,
	EIM_LED_ANIMATION_BLINK_GREEN,
	EIM_LED_ANIMATION_BLINK_RED,
	EIM_LED_ANIMATION_BLINK_ORANGE,
	EIM_LED_ANIMATION_SNAKE_GREEN_RED,
	EIM_LED_ANIMATION_FIRE,
	EIM_LED_ANIMATION_STANDARD,
	EIM_LED_ANIMATION_RED,
	EIM_LED_ANIMATION_GREEN,
	EIM_LED_ANIMATION_RED_SNAKE,
	EIM_LED_ANIMATION_BLANK,
	EIM_LED_ANIMATION_RIGHT_MISSILE,
	EIM_LED_ANIMATION_LEFT_MISSILE,
	EIM_LED_ANIMATION_DOUBLE_MISSILE,
	EIM_LED_ANIMATION_FRONT_LEFT_GREEN_OTHERS_RED,
	EIM_LED_ANIMATION_FRONT_RIGHT_GREEN_OTHERS_RED,
	EIM_LED_ANIMATION_REAR_RIGHT_GREEN_OTHERS_RED,
	EIM_LED_ANIMATION_REAR_LEFT_GREEN_OTHERS_RED,
	EIM_LED_ANIMATION_LEFT_GREEN_RIGHT_RED,
	EIM_LED_ANIMATION_LEFT_RED_RIGHT_GREEN,
	EIM_LED_ANIMATION_BLINK_STANDARD,
} EIM_LEDAnimation_t;

typedef enum
{
	EIM_FREEFLIGHT 					= 0,
	EIM_HOVER_ON_ROUNDEL 			= 1,
	EIM_HOVER_ON_ORIENTED_RONDEL 	= 2
} EIM_ARDrone2_FlightModes_t;

typedef enum
{
	EIM_ULTRASOUND_22HZ		= 0,
	EIM_ULTRASOUND_25HZ		= 1
} EIM_ARDrone2_UltrasoundFreq_t;



typedef enum
{
	EIM_NULL_CODEC   			 			= 0,
	EIM_UVLC_CODEC    						= 1,
	EIM_MJPEG_CODEC	  						= 2,
	EIM_P263_CODEC	  						= 3,
	EIM_P264_CODEC    						= 4,
	EIM_MP4_360P_CODEC 						= 5,
	EIM_H264_360P_CODEC 					= 6,
	EIM_MP4_360P_H264_720P_CODEC 			= 7,
	EIM_H264_720P_CODEC 					= 8,
	EIM_MP4_360P_SLRS_CODEC 				= 9,
	EIM_H264_360P_SLRS_CODEC 				= 10,
	EIM_H264_720P_SLRS_CODEC 				= 11,
	EIM_H264_AUTO_RESIZE_CODEC 				= 12,
	EIM_MP4_360P_H264_360P_CODEC 			= 13
} EIM_VideoCodecType_t;

typedef enum
{
	EIM_ARDRONE2_NULL_CODEC		 			= 0x00,
	EIM_ARDRONE2_UVLC_CODEC    				= 0x20,	/* codec_type value is used for START_CODE */
	EIM_ARDRONE2_MJPEG_CODEC	 			= 0x21, /* not used */
	EIM_ARDRONE2_P263_CODEC	  				= 0x22,	/* not used */
	EIM_ARDRONE2_P264_CODEC    				= 0x40,
	EIM_ARDRONE2_MP4_360P_CODEC 			= 0x80,
	EIM_ARDRONE2_H264_360P_CODEC 			= 0x81,
	EIM_ARDRONE2_MP4_360P_H264_720P_CODEC 	= 0x82,
	EIM_ARDRONE2_H264_720P_CODEC 			= 0x83,
	EIM_ARDRONE2_MP4_360P_SLRS_CODEC 		= 0x84,
	EIM_ARDRONE2_H264_360P_SLRS_CODEC 		= 0x85,
	EIM_ARDRONE2_H264_720P_SLRS_CODEC 		= 0x86,
	EIM_ARDRONE2_H264_AUTO_RESIZE_CODEC 	= 0x87, /* resolution is automatically adjusted according to bitrate */
	EIM_ARDRONE2_MP4_360P_H264_360P_CODEC 	= 0x88
} EIM_ARDrone2_VideoCodecType_t;

typedef enum {
	EIM_ANIMATION_PHI_M30_DEG=0,
	EIM_ANIMATION_PHI_30_DEG,
	EIM_ANIMATION_THETA_M30_DEG,
	EIM_ANIMATION_THETA_30_DEG,
	EIM_ANIMATION_THETA_20DEG_YAW_200DEG,
	EIM_ANIMATION_THETA_20DEG_YAW_M200DEG,
	EIM_ANIMATION_TURNAROUND,
	EIM_ANIMATION_TURNAROUND_GODOWN,
	EIM_ANIMATION_YAW_SHAKE,
	EIM_ANIMATION_YAW_DANCE,
	EIM_ANIMATION_PHI_DANCE,
	EIM_ANIMATION_THETA_DANCE,
	EIM_ANIMATION_VZ_DANCE,
	EIM_ANIMATION_WAVE,
	EIM_ANIMATION_PHI_THETA_MIXED,
	EIM_ANIMATION_DOUBLE_PHI_THETA_MIXED,
	EIM_ANIMATION_FLIP_AHEAD,
	EIM_ANIMATION_FLIP_BEHIND,
	EIM_ANIMATION_FLIP_LEFT,
	EIM_ANIMATION_FLIP_RIGHT
} EIM_FlightAnimation_t;

typedef enum {
	EIM_VARIABLE_BITRATE_MODE_DISABLED=0,
	EIM_VARIABLE_BITRATE_MODE_DYNAMIC,
	EIM_VARIABLE_BITRATE_MANUAL
} EIM_VariableBitrate_t;


void EIM_ProcessGroundCommand(void);

EIM_CmdResponse_t EIM_ResetCtrsCmd(void);
EIM_CmdResponse_t EIM_EnableNavDataCmd(void);
EIM_CmdResponse_t EIM_DisableNavDataCmd(void);
EIM_CmdResponse_t EIM_ActivateNavDataTagCmd(uint32 TagID);
EIM_CmdResponse_t EIM_DeactivateNavDataTagCmd(uint32 TagID);
EIM_CmdResponse_t EIM_ActivateNavDataDemoCmd(void);
EIM_CmdResponse_t EIM_DeactivateNavDataDemoCmd(void);


EIM_CmdResponse_t EIM_ARDrone2_SetName(char *Name);
EIM_CmdResponse_t EIM_ARDrone2_SetWatchdogTimeout(uint32 Timeout);
EIM_CmdResponse_t EIM_ARDrone2_EnableVideo(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableVideo(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableVision(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableVision(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableControl(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableControl(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableCombinedYawControl(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableCombinedYawControl(void);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxAngle(float angle);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxAltitude(uint32 altitude);
EIM_CmdResponse_t EIM_ARDrone2_SetMinAltitude(uint32 altitude);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxIPhoneTilt(float angle);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxVerticalSpeed(uint32 speed);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxYawSpeed(float speed);
EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorMode(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorMode(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorShell(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorShell(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableAutonomousMode(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableAutonomousMode(void);
EIM_CmdResponse_t EIM_ARDrone2_SetManualTrim(void);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxIndoorAngle(float angle);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxIndoorVerticalSpeed(uint32 speed);
EIM_CmdResponse_t EIM_ARDrone2_EnableIndoorControl(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableIndoorControl(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableIndoorCombinedYawControl(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableIndoorCombinedYawControl(void);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxOutdoorAngle(float angle);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxOutdoorVerticalSpeed(uint32 speed);
EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorControl(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorControl(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorCombinedYawControl(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorCombinedYawControl(void);
EIM_CmdResponse_t EIM_ARDrone2_SetFlyingMode(EIM_ARDrone2_FlightModes_t mode);
EIM_CmdResponse_t EIM_ARDrone2_SetRoundelHoveringRange(uint32 range);
EIM_CmdResponse_t EIM_ARDrone2_ExecuteFlightAnimation(EIM_FlightAnimation_t animation, uint32 duration);
EIM_CmdResponse_t EIM_ARDrone2_SetSinglePlayerSSID(char *SSID);
EIM_CmdResponse_t EIM_ARDrone2_SetMultiPlayerSSID(char *SSID);
EIM_CmdResponse_t EIM_ARDrone2_SetWifiMode(EIM_WifiMode_t Mode);
EIM_CmdResponse_t EIM_ARDrone2_SetWifiRate(void);
EIM_CmdResponse_t EIM_ARDrone2_SetOwnerMac(char *MAC);
EIM_CmdResponse_t EIM_ARDrone2_SetUltrasoundFreq(EIM_ARDrone2_UltrasoundFreq_t freq);
EIM_CmdResponse_t EIM_ARDrone2_SetUltrasoundWatchdog(void);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoCodecFPS(uint32 fps);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoCodec(EIM_VideoCodecType_t codec);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoSlices(void);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoLiveSocket(void);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoBitrate(uint32 bitrate);
EIM_CmdResponse_t EIM_ARDrone2_SetMaxVideoBitrate(uint32 bitrate);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoBitrateControlMode(EIM_VariableBitrate_t Mode);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoBitrateStorage(void);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoChannel(EIM_VideoChannel_t Channel);
EIM_CmdResponse_t EIM_ARDrone2_EnableVideoOnUSB(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableVideoOnUSB(void);
EIM_CmdResponse_t EIM_ARDrone2_SetVideoFileIndex(void);
EIM_CmdResponse_t EIM_ARDrone2_SetLEDAnimation(EIM_LEDAnimation_t Animation, float Frequency, uint32 Duration);
EIM_CmdResponse_t EIM_ARDrone2_SetEnemyColorsDetect(void);
EIM_CmdResponse_t EIM_ARDrone2_SetGroundStripeColorsDetect(void);
EIM_CmdResponse_t EIM_ARDrone2_EnableEnemyOutdoorShellDetect(void);
EIM_CmdResponse_t EIM_ARDrone2_DisableEnemyOutdoorShellDetect(void);
EIM_CmdResponse_t EIM_ARDrone2_SetDetectType(void);
EIM_CmdResponse_t EIM_ARDrone2_SetDetectionsSelectH(void);
EIM_CmdResponse_t EIM_ARDrone2_SetDetectionsSelectVHSync(void);
EIM_CmdResponse_t EIM_ARDrone2_SetDetectionsSelectV(void);
EIM_CmdResponse_t EIM_ARDrone2_UserboxStop(void);
EIM_CmdResponse_t EIM_ARDrone2_UserboxStart(void);
EIM_CmdResponse_t EIM_ARDrone2_UserboxScreenshot(void);
EIM_CmdResponse_t EIM_ARDrone2_UserboxCancel(void);
EIM_CmdResponse_t EIM_ARDrone2_SetLatitude(void);
EIM_CmdResponse_t EIM_ARDrone2_SetLongitude(void);
EIM_CmdResponse_t EIM_ARDrone2_SetAltitude(void);
EIM_CmdResponse_t EIM_ARDrone2_SetApplicationID(void);
EIM_CmdResponse_t EIM_ARDrone2_SetApplicationDescription(void);
EIM_CmdResponse_t EIM_ARDrone2_SetProfileID(void);
EIM_CmdResponse_t EIM_ARDrone2_SetProfileDescription(void);
EIM_CmdResponse_t EIM_ARDrone2_SetSessionID(void);
EIM_CmdResponse_t EIM_ARDrone2_SetSessionDescription(void);
EIM_CmdResponse_t EIM_ARDrone2_EmergencyStop(void);
EIM_CmdResponse_t EIM_ARDrone2_EmergencyStopReset(void);
EIM_CmdResponse_t EIM_ARDrone2_Launch(void);
EIM_CmdResponse_t EIM_ARDrone2_Land(void);
EIM_CmdResponse_t EIM_ARDrone2_Hover(void);
EIM_CmdResponse_t EIM_ARDrone2_SetRoll(void);
EIM_CmdResponse_t EIM_ARDrone2_SetPitch(void);
EIM_CmdResponse_t EIM_ARDrone2_SetYawSpeed(void);
EIM_CmdResponse_t EIM_ARDrone2_SetVerticalSpeed(void);
EIM_CmdResponse_t EIM_ARDrone2_SetMovement(void);
EIM_CmdResponse_t EIM_ARDrone2_SetFlatTrim(void);
EIM_CmdResponse_t EIM_ARDrone2_CalibrateMagnetometer(void);







int32 EIM_VerifyCmdLength (CFE_SB_MsgPtr_t MessagePtr, uint32 ExpectedLength);



#endif /* EIM_CMDS_H_ */
