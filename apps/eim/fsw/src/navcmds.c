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

#include <float.h>

#ifdef __cplusplus
extern "C" {
#endif



/*=======================================================================================
** File Name:  eim_cmds.c
**
** Title:  Function Definitions ARDRONE2 App API commands
**
** $Authors:   Guy de Carufel
** $Revision:  $
** $Date:      2013-10-15
**
** Purpose:  Define all the API function calls for Drone control
**
** Functions Defined:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2013-10-15 | Guy de Carufel | Code Started
**
**=====================================================================================*/

/*
** Include Files
*/
#include <string.h>
#include <errno.h>

#include "cfe.h"
#include "app.h"
#include "cmds.h"
#include "events.h"
#include "navcmds.h"

/*
** Local Defines
*/
//void EIM_RcvATCmds(void);
//void EIM_RotWingGenericCmds(CFE_SB_Msg_t*);
//void EIM_PlatformSpecificCmds(CFE_SB_Msg_t*);

void EIM_customATCmd(int, char *);
void EIM_modNavDataOpt(NavData_Tag_t, int flag);

void EIM_rollWithCombinedYaw(float roll);
void EIM_yawAbs(float yawAngle, float yawAcu);
void EIM_move_mag(int, float, float, float, float, float, float);
void EIM_LEDAnimate(int, int, float);
void EIM_moveAnimate(int, int);
void EIM_SendATCommand(char *command_string);
void EIM_resetCmdSeq(void);
int EIM_incrAtCmdSeq(void);

/*
** Local Structure Declarations
*/
#define EIM_NAVCMD_SENDBUFF_SIZE 1500
char EIM_NavCmd_SendBuff[EIM_NAVCMD_SENDBUFF_SIZE];

/*
** External Global Variables
*/
extern EIM_AppData_t EIM_AppData;

/*
** Global Variables
*/
const char *g_EIM_configGenCmds[] =
{
    "GENERAL:num_version_config",
    "GENERAL:num_version_mb",
    "GENERAL:num_version_soft",
    "GENERAL:soft_build_date",
    "GENERAL:motor1_soft",
    "GENERAL:motor2_soft",
    "GENERAL:motor3_soft",
    "GENERAL:motor4_soft",
    "GENERAL:motor1_hard",
    "GENERAL:motor2_hard",
    "GENERAL:motor3_hard",
    "GENERAL:motor4_hard",
    "GENERAL:motor1_supplier",
    "GENERAL:motor2_supplier",
    "GENERAL:motor3_supplier",
    "GENERAL:motor4_supplier",
    "GENERAL:ardrone_name",
    "GENERAL:flying_time",
    "GENERAL:navdata_demo",
    "GENERAL:com_watchdog",
    "GENERAL:video_enable",
    "GENERAL:vision_enable",
    "GENERAL:vbat_min",
    "GENERAL:navdata_options"
};


const char *g_EIM_configCtrlCmds[] =
{
    "CONTROL:accs_offset",
    "CONTROL:accs_gains",
    "CONTROL:gyros_offset",
    "CONTROL:gyros_gains",
    "CONTROL:gyros110_offset",
    "CONTROL:gyros110_gains",
    "CONTROL:gyros_offset_thr_x",
    "CONTROL:gyros_offset_thr_y",
    "CONTROL:gyros_offset_thr_z",
    "CONTROL:pwm_ref_gyros",
    "CONTROL:shield_enable",
    "CONTROL:altitude_max",
    "CONTROL:altitude_min",
    "CONTROL:outdoor",
    "CONTROL:flight_without_shell",
    "CONTROL:flight_anim",
    "CONTROL:control_level",
    "CONTROL:euler_angle_max",
    "CONTROL:indoor_euler_angle_max",
    "CONTROL:outdoor_euler_angle_max",
    "CONTROL:control_vz_max",
    "CONTROL:indoor_control_vz_max",
    "CONTROL:outdoor_control_vz_max",
    "CONTROL:control_yaw",
    "CONTROL:indoor_control_yaw",
    "CONTROL:outdoor_control_yaw",
    "CONTROL:flying_mode"
};

/*
** Local Variables
*/
struct sockaddr_in 		CmdSocketAddress;
struct sockaddr_in 		CmdARDroneAddress;
int					    CmdSequence;

float roll = 0;
float pitch = 0;
float vSpeed = 0;
float ySpeed = 0;


/* Main function of task */
void EIM_ATCmdMain(void)
{
    /* Register this child task */
    CFE_ES_RegisterChildTask();

    /* Initialize sockets */
    EIM_InitATCmdSockets();

	/* Loop and check for a new AT cmd every 30ms */
    while(1)
	{
//	    EIM_RcvATCmds();
		OS_TaskDelay(100);
//	    EIM_move(1, roll, pitch, vSpeed, ySpeed);
		EIM_cmdComWdg();
    }
}



/* Initialize commanding socket */
int EIM_InitATCmdSockets(void)
{
	int                     status = 0;
	socklen_t optlen;
	int sendbuff;

    /* Reset Cmd sequence */
    EIM_resetCmdSeq();

	/* Create sockets */
	if ( (EIM_AppData.ATCmdSocketID =
            socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        CFE_EVS_SendEvent(EIM_NAVCMD_INIT_ERR_EID, CFE_EVS_ERROR,
                          "EIM: Failed to create command socket.  errno: %d", errno);
        status = -1;
        goto end_of_function;
    }

	/* Set buffer size */
	optlen = sizeof(sendbuff);
	status = getsockopt(EIM_AppData.ATCmdSocketID, SOL_SOCKET, SO_SNDBUF, &sendbuff, &optlen);
	if(status == -1)
	     OS_printf("Error getsockopt one\n");
	else
	     OS_printf("send buffer size = %d\n", sendbuff);
	sendbuff = 20;
	status = setsockopt(EIM_AppData.ATCmdSocketID, SOL_SOCKET, SO_SNDBUF, &sendbuff, sizeof(sendbuff));
	status = getsockopt(EIM_AppData.ATCmdSocketID, SOL_SOCKET, SO_SNDBUF, &sendbuff, &optlen);
	if(status == -1)
	     OS_printf("Error getsockopt one\n");
	else
	     OS_printf("send buffer size = %d\n", sendbuff);


	/* Set minimum number of bytes to process */
	optlen = sizeof(sendbuff);
	status = getsockopt(EIM_AppData.ATCmdSocketID, SOL_SOCKET, SO_SNDLOWAT, &sendbuff, &optlen);
	if(status == -1)
	     OS_printf("Error getsockopt one\n");
	else
	     OS_printf("SO_SNDLOWAT = %d\n", sendbuff);
	sendbuff = 0;
	status = setsockopt(EIM_AppData.ATCmdSocketID, SOL_SOCKET, SO_SNDLOWAT, &sendbuff, sizeof(sendbuff));
	status = getsockopt(EIM_AppData.ATCmdSocketID, SOL_SOCKET, SO_SNDLOWAT, &sendbuff, &optlen);
	if(status == -1)
	     OS_printf("Error getsockopt one\n");
	else
	     OS_printf("SO_SNDLOWAT = %d\n", sendbuff);

	/* Set addresses */
	bzero((char *) &CmdSocketAddress, sizeof(CmdSocketAddress));
	CmdSocketAddress.sin_family      = AF_INET;
	CmdSocketAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
	CmdSocketAddress.sin_port        = htons(0);

	bzero((char *) &CmdARDroneAddress, sizeof(CmdARDroneAddress));
	CmdARDroneAddress.sin_family      = AF_INET;
	CmdARDroneAddress.sin_addr.s_addr = inet_addr(EIM_WIFI_IP);
	CmdARDroneAddress.sin_port        = htons(EIM_AT_PORT);

	if ( bind(EIM_AppData.ATCmdSocketID,
              (struct sockaddr *) &CmdSocketAddress,
			  sizeof(CmdSocketAddress)) < 0)
	{
		CFE_EVS_SendEvent(EIM_NAVCMD_INIT_ERR_EID, CFE_EVS_ERROR,
                          "EIM: Failed to bind command socket.  errno: %d", errno);
		status = -1;
		goto end_of_function;
	}

end_of_function:
	return status;
}



/* Send a config AT command */
void EIM_configATCmd(const char *cmd_in, const char *param)
{
    int seq = 0;
    char cmd[100];

    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*CONFIG=%d,\"%s\",\"%s\"\r", seq, cmd_in, param);
    EIM_SendATCommand(cmd);
}


/* Send a custom AT command */
void EIM_customATCmd(int length, char *cmd_in)
{
	char cmd[256];
    memset(cmd, 0x0, sizeof(cmd));
    memcpy(cmd, cmd_in, length);

	EIM_SendATCommand(cmd);
}



void EIM_CalibMagneto(void)
{
    int seq = 0;
    char cmd[100];

    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*CALIB=%d,%d\r", seq, 0);
	EIM_SendATCommand(cmd);
}



/* Set the Control mode */
void EIM_cmdSetControl(ARDrone2_ControlMode_t controlMode)
{
    int seq = 0;
    char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*CTRL=%d,%d,0\r", seq, controlMode);
	EIM_SendATCommand(cmd);
}


/* Set configuration IDs */
void EIM_configIds(void)
{
    EIM_configATCmd("custom:session_id", "1");
    OS_TaskDelay(30);
    EIM_configATCmd("custom:profile_id", "1");
    OS_TaskDelay(30);
    EIM_configATCmd("custom:application_id", "1");
//    EIM_configATCmd("custom:session_id", ARDRONE2_SESSION_ID);
//    OS_TaskDelay(30);
//    EIM_configATCmd("custom:profile_id", ARDRONE2_PROFILE_ID);
//    OS_TaskDelay(30);
//    EIM_configATCmd("custom:application_id", ARDRONE2_APPLICATION_ID);
}


/* Change navData options */
void EIM_modNavDataOpt(NavData_Tag_t optionTag, int flag)
{
    char cmd_param[11];

    OS_MutSemTake(EIM_AppData.NavDataMutexId);
    if (flag == TRUE)
    {
        /* Perform bitwize OR to turn on bit */
        EIM_AppData.lastNavDataOptions |= 1 << (int) optionTag;
    }
    else
    {
        /* Perform bitwise XAND to turn off bit */
        EIM_AppData.lastNavDataOptions &= ~(1 << (int) optionTag);
    }
    OS_MutSemGive(EIM_AppData.NavDataMutexId);

    sprintf(cmd_param, "%u", (unsigned int)EIM_AppData.lastNavDataOptions);

    EIM_configATCmd("general:navdata_options", cmd_param);
}



/* Tell the drone it is lying horizontally. Must be called before flying */
void EIM_setFlatTrim(void)
{
    char cmd[100];
    int seq;

    /* Unknown setting, but needed apparently */
    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*PMODE=%d,%d\r", seq, 2);
	EIM_SendATCommand(cmd);

    OS_TaskDelay(30);

    /* Set limits ? */
    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*MISC=%d,%d,%d,%d,%d\r", seq, 2, 20, 2000, 3000);
	EIM_SendATCommand(cmd);

    OS_TaskDelay(30);

    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*FTRIM=%d\r", seq);
	EIM_SendATCommand(cmd);
}



/* Take off and hover at pre-defined level (default: 1m) */
void EIM_takeOff(void)
{
    int seq = 0;
    char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));

    /* Bits 18, 20, 22, 24 and 28 set to 1 */
    int arg2 = 0x11540000;

    /* For take-off, set bit 9 to 1 */
    arg2 |= 0x200;

    seq = EIM_incrAtCmdSeq();
    sprintf(cmd, "AT*PCMD=%d,0,0,0,0,0\r", seq);
    EIM_SendATCommand(cmd);
    //EIM_cmdComWdg();
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*REF=%d,%d\r", seq, arg2);
	EIM_SendATCommand(cmd);
}


/* Land the drone */
void EIM_land(void)
{
	char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));
    int seq;

    /* Bits 18, 20, 22, 24 and 28 set to 1.  Bit 9 is 0 */
    int arg2 = 0x11540000;

    seq = EIM_incrAtCmdSeq();
    sprintf(cmd, "AT*PCMD=%d,0,0,0,0,0\r", seq);
    EIM_SendATCommand(cmd);
    //EIM_cmdComWdg();
    seq = EIM_incrAtCmdSeq();
	sprintf(cmd, "AT*REF=%d,%d\r", seq, arg2);
	EIM_SendATCommand(cmd);
}


/* Emergency stop.  Kills engines and falls if flying. */
void EIM_eStop(void)
{
	int seq = EIM_incrAtCmdSeq();

    char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));

    /* Bits 18, 20, 22, 24 and 28 set to 1 */
    int arg2 = 0x11540000;

    /* For emergency stop / reset, set bit 8 to 1 */
    arg2 |= 0x100;

    sprintf(cmd, "AT*REF=%d,%d\r", seq, arg2);
	EIM_SendATCommand(cmd);
}


/* Reset the e-stop. Can then take off again. */
void EIM_reset(void)
{
    /* Same AT command as e-stop */
    EIM_eStop();
}

/* Make drone hover over same point on ground (null translation) */
void EIM_hover(void)
{
    int opt = 0;      // Set to 0 to enter hover mode
    roll = 0;     // Roll
    pitch = 0;    // Pitch
    vSpeed = 0;   // Vertical speed
    ySpeed = 0;      // Yaw / spin

    EIM_move(opt, roll, pitch, vSpeed, ySpeed);
}


/* Make drone pitch forward (-%) / backward (+%) */
void EIM_pitch(float pitch)
{
    int opt = 1;    // Set to consider other params

    /* Out of range > 100% of max inclination value */
    if(pitch > 1 || pitch < -1)
    {
        return;
    }

    EIM_move(opt, roll, pitch, vSpeed, ySpeed);
}


/* Make drone roll left (-%) / right (+%) */
void EIM_roll(float roll)
{
    int opt = 1;    // Set to consider other params

    /* Out of range > 100% of max inclination value */
    if(roll > 1 || roll < -1)
    {
        return;
    }

    EIM_move(opt, roll, pitch, vSpeed, ySpeed);
}


/* Make drone roll left (-%) / right (+%) */
/* ARDrone specific roll command used in racing */
void EIM_rollWithCombinedYaw(float roll)
{
    int opt = 3;    // Set bits 1 and 2 = 1

    /* Out of range > 100% of max inclination value */
    if(roll > 1 || roll < -1)
    {
        return;
    }

    EIM_move(opt, roll, pitch, vSpeed, ySpeed);
}


/* Make drone spin left-cw (-%) / right-ccw (+%) */
void EIM_yaw(float ySpeed)
{
    int opt = 1;    // Set to consider other params

    printf("Yaw is %f\n", ySpeed);

    /* Out of range > 100% of max speed value */
    if(ySpeed > 1 || ySpeed < -1)
    {
        return;
    }

    EIM_move(opt, roll, pitch, vSpeed, ySpeed);
}


/* Make drone climb (+%) or drop (-%) */
void EIM_climb(float vSpeed)
{
    int opt = 1;    // Set to consider other params

    /* Out of range > 100% of max speed value */
    if(vSpeed > 1 || vSpeed < -1)
    {
        return;
    }

    EIM_move(opt, roll, pitch, vSpeed, ySpeed);
}


/* General ARDrone function to move */
void EIM_move(int opt, float inRoll, float inPitch, float inVSpeed, float inYSpeed)
{
	if(
		(EIM_AppData.navdata_demo.ctrl_state == EIM_MINOR_CTRL_STATE_FLYING) ||
		(EIM_AppData.navdata_demo.ctrl_state == EIM_MINOR_CTRL_STATE_HOVERING)) {
		char cmd[100];
		int seq = 0;
		memset(cmd, 0x0, sizeof(cmd));

		roll = inRoll;
		pitch = inPitch;
		vSpeed = inVSpeed;
		ySpeed = inYSpeed;

		seq = EIM_incrAtCmdSeq();

		sprintf(cmd, "AT*PCMD=%d,%d,%d,%d,%d,%d\r", seq, opt,
				*(int*) &roll, *(int*) &pitch, *(int*) &vSpeed, *(int*) &ySpeed);

		if((roll > FLT_EPSILON) || (roll < -FLT_EPSILON)) {
			OS_printf("Roll: %f   Pitch: %f   Yaw: %f   VSpeed: %f     %s\n", roll, pitch, ySpeed, vSpeed, cmd);
		}

		EIM_SendATCommand(cmd);
	}
}


/* Make drone yaw to set angle (deg) from North (+ Est, - West) */
void EIM_yawAbs(float yawAngle, float yawAcu)
{
    int opt = 5;    // Set to consider other params and abs. ySpeed
    float roll = 0;    // Roll
    float pitch = 0;   // Pitch
    float vSpeed = 0;  // Vertical speed
    float ySpeed = 0;  // Yaw speed
    float yaw = yawAngle / 180.0;

    /* Out of range > 100% of ySpeed angle (0 = North, -1/1 = South)
       yawAcu in degrees. Must be positive */
    if(yaw > 1 || yaw < -1 || yawAcu < 0)
    {
        return;
    }

    EIM_move_mag(opt, roll, pitch, vSpeed, ySpeed, yaw, yawAcu);
}


/* General ARDrone function to move with absolute magnitometer */
void EIM_move_mag(int opt, float roll, float pitch, float vSpeed,
                       float ySpeed, float yaw, float yawAcu)
{
	char cmd[100];
    int seq = 0;
    memset(cmd, 0x0, sizeof(cmd));

    seq = EIM_incrAtCmdSeq();

	sprintf(cmd, "AT*PCMD_MAG=%d,%d,%d,%d,%d,%d,%d,%d\r", seq, opt,
            *(int*) &roll, *(int*) &pitch, *(int*) &vSpeed, *(int*) &ySpeed,
            *(int*) &yaw, *(int*) &yawAcu);
    EIM_SendATCommand(cmd);
}



/* EIM LED animation */
void EIM_LEDAnimate(int animation, int duration, float freq)
{
    int seq = EIM_incrAtCmdSeq();

	char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));

	sprintf(cmd, "AT*LED=%d,%d,%d,%d\r", seq, animation, (int) freq, duration);
	EIM_SendATCommand(cmd);
}

/* EIM execute predefined movement - animation */
void EIM_moveAnimate(int animation, int duration)
{
    int seq = EIM_incrAtCmdSeq();

	char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));

	sprintf(cmd, "AT*ANIM=%d,%d,%d\r", seq, animation, duration);
	EIM_SendATCommand(cmd);
}


///* EIM execute "HOVER_ON_TOP_OF_ROUNDEL" maneuver */
//void EIM_hoverTopRoundel(void)
//{
//    EIM_detectConfigCmd(detect_type, "?");
//    EIM_controlConfigCmd(flying_mode, "?");
//}



// PRIVATE FUNCTIONS:

/* Send AT command directly to Drone. Private function */
void EIM_SendATCommand(char *command_string)
{
	sendto(EIM_AppData.ATCmdSocketID,
           command_string, strlen(command_string), 0,
		   (struct sockaddr *) &CmdARDroneAddress, sizeof(CmdARDroneAddress) );

}

/* Send Watchdog command */
void EIM_cmdComWdg(void)
{
    int seq = 0;
    char cmd[100];
    memset(cmd, 0x0, sizeof(cmd));
    seq = EIM_incrAtCmdSeq();

    sprintf(cmd, "AT*COMWDG=%u\r", seq);
	EIM_SendATCommand(cmd);
}



/* Reset the Cmd sequence */
void EIM_resetCmdSeq(void)
{
    //OS_MutSemTake(EIM_AppData.CmdSeqMutexId);
    CmdSequence = EIM_NAVDATA_SEQUENCE_DEFAULT-1;
    //OS_MutSemGive(EIM_AppData.CmdSeqMutexId);
}



/* Increment the Cmd sequence */
int EIM_incrAtCmdSeq(void)
{
   int seq;

    //OS_MutSemTake(EIM_AppData.CmdSeqMutexId);
    CmdSequence++;
    seq = CmdSequence;
    //OS_MutSemGive(EIM_AppData.CmdSeqMutexId);

    return seq;
}

#ifdef __cplusplus
}
#endif



/*=======================================================================================
** End of file ardron2_cmds.c
**=====================================================================================*/


