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

#ifdef __cplusplus
extern "C" {
#endif

#include "cmds.h"
#include "msg.h"
#include "cfe.h"
#include "app.h"
#include "defs.h"
#include "events.h"
#include "navdata.h"
#include "eim_msgs.h"
#include "navcmds.h"
#include "msgdefs.h"

#include <string.h>

void EIM_ProcessGroundCommand(void)
{
    uint16 CommandCode;

    CommandCode = CFE_SB_GetCmdCode(EIM_AppData.MsgPtr);

    /* Process "known" EIM task ground commands */
    switch (CommandCode)
    {
        case EIM_NOOP_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Noop command failed.  Length incorrect.");
            }
            else
            {
            	/* Status of commands processed by EIM task */
            	EIM_AppData.Hk.CmdCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: NOOP command");
            }

            break;
        }

        case EIM_RESET_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Reset command failed.  Length incorrect.");
            }
            else
            {
                EIM_ResetCtrsCmd();
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Reset Counters command");
            }
            break;
    	}

        case EIM_ENABLE_NAVDATA_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable NavData command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_EnableNavDataCmd() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable NavData command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable NavData command");
                }
            }

            break;
    	}

        case EIM_DISABLE_NAVDATA_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable NavData command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_DisableNavDataCmd() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable NavData command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable NavData command");
                }
            }

            break;
    	}

        case EIM_ACTIVATE_NAVDATA_TAG_CC:
        {
        	EIM_ActDeactTagCmd_t        *CmdPtr = (EIM_ActDeactTagCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_ActDeactTagCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Activate NavData Tag command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ActivateNavDataTagCmd(CmdPtr->TagID) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Activate NavData Tag command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Activate NavData Tag %u command", CmdPtr->TagID);
                }
            }

            break;
    	}

        case EIM_DEACTIVATE_NAVDATA_TAG_CC:
        {
        	EIM_ActDeactTagCmd_t        *CmdPtr = (EIM_ActDeactTagCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_ActDeactTagCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Deactivate NavData Tag command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_DeactivateNavDataTagCmd(CmdPtr->TagID) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Deactivate NavData Tag command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Deactivate NavData Tag %u command", CmdPtr->TagID);
                }
            }

            break;
    	}

        case EIM_ACTIVATE_NAVDATA_DEMO_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Activate NavData Demo command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ActivateNavDataDemoCmd() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Activate NavData Demo command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Activate NavData Demo command");
                }
            }

        	break;
    	}

        case EIM_DEACTIVATE_NAVDATA_DEMO_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Deactivate NavData Demo command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_DeactivateNavDataDemoCmd() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Deactivate NavData Demo command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Deactivate NavData Demo command");
                }
            }

        	break;
    	}

        case EIM_ARDRONE2_SET_NAME_CC:
        {
        	EIM_SetNameCmd_t *CmdPtr = (EIM_SetNameCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetNameCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Name command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetName(CmdPtr->Name) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Name command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Name command");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_WATCHDOG_TIMEOUT_CC:
        {
        	EIM_SetWatchdogCmd_t *CmdPtr = (EIM_SetWatchdogCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetWatchdogCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Watchdog Timeout command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetWatchdogTimeout(CmdPtr->Timeout) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Watchdog Timeout command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Watchdog Timeout command");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_VIDEO_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Video command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableVideo() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Video command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Video command");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_VIDEO_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Video command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableVideo() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Video command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Video command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_VISION_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Vision command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableVision() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Vision command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Vision command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_VISION_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Vision command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableVision() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Vision command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Vision command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_COMBINED_YAW_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Combined Yaw Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableCombinedYawControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Combined Yaw Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Combined Yaw Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_COMBINED_YAW_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Combined Yaw Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableCombinedYawControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Combined Yaw Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Combined Yaw Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_ANGLE_CC:
        {
        	EIM_AngleCmd_t        *CmdPtr = (EIM_AngleCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AngleCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Angle command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxAngle(CmdPtr->Angle) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Angle command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Angle command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_ALTITUDE_CC:
        {
        	EIM_AltitudeCmd_t *CmdPtr = (EIM_AltitudeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AltitudeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Altitude command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxAltitude(CmdPtr->Altitude) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Altitude command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Altitude command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MIN_ALTITUDE_CC:
        {
        	EIM_AltitudeCmd_t *CmdPtr = (EIM_AltitudeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AltitudeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Min Altitude command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMinAltitude(CmdPtr->Altitude) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Min Altitude command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Min Altitude command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_IPHONE_TILT_CC:
        {
        	EIM_AngleCmd_t *CmdPtr = (EIM_AngleCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AngleCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max iPhone Tilt command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxIPhoneTilt(CmdPtr->Angle) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max iPhone Tilt command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max iPhone Tilt command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_VERTICAL_SPEED_CC:
        {
        	EIM_AltitudeCmd_t *CmdPtr = (EIM_AltitudeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Vertical Speed command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxVerticalSpeed(CmdPtr->Altitude) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Vertical Speed command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Vertical Speed command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_YAW_SPEED_CC:
        {
        	EIM_AngularRateCmd_t *CmdPtr = (EIM_AngularRateCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AngularRateCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Yaw Speed command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxYawSpeed(CmdPtr->Rate) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Yaw Speed command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Yaw Speed command successful.");
                }
            }

            break;
    	}



        case EIM_ARDRONE2_ENABLE_OUTDOOR_MODE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Outdoor Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableOutdoorMode() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_OUTDOOR_MODE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Outdoor Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableOutdoorMode() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Outdoor Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Outdoor Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_OUTDOOR_SHELL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Outdoor Shell command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableOutdoorShell() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Shell command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Shell command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_OUTDOOR_SHELL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disaable Outdoor Shell command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableOutdoorShell() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Disaable Outdoor Shell command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disaable Outdoor Shell command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_AUTONOMOUS_MODE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Autonomous Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableAutonomousMode() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Autonomous Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Autonomous Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_AUTONOMOUS_MODE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Autonomous Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableAutonomousMode() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Autonomous Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Autonomous Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MANUAL_TRIM_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Manual Trim command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetManualTrim() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Manual Trim command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Manual Trim command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_INDOOR_ANGLE_CC:
        {
        	EIM_AngleCmd_t *CmdPtr = (EIM_AngleCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AngleCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Indoor Angle command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxIndoorAngle(CmdPtr->Angle) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Indoor Angle command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Indoor Angle command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_INDOOR_VERTICAL_SPEED_CC:
        {
        	EIM_SpeedCmd_t *CmdPtr = (EIM_SpeedCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SpeedCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Indoor Vertical Speed command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxIndoorVerticalSpeed(CmdPtr->Speed) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Indoor Vertical Speed command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Indoor Vertical Speed command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_INDOOR_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Indoor Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableIndoorControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Indoor Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Indoor Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_INDOOR_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Indoor Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableIndoorControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Indoor Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Indoor Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_INDOOR_COMBINED_YAW_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Indoor Combined Yaw Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableIndoorCombinedYawControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Indoor Combined Yaw Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Indoor Combined Yaw Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_INDOOR_COMBINED_YAW_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Indoor Combined Yaw Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableIndoorCombinedYawControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Indoor Combined Yaw Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Indoor Combined Yaw Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_OUTDOOR_ANGLE_CC:
        {
        	EIM_AngleCmd_t *CmdPtr = (EIM_AngleCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AngleCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Outdoor Angle command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxOutdoorAngle(CmdPtr->Angle) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Outdoor Angle command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Outdoor Angle command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_OUTDOOR_VERTICAL_SPEED_CC:
        {
        	EIM_SpeedCmd_t *CmdPtr = (EIM_SpeedCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SpeedCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Outdoor Vertical Speed command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxOutdoorVerticalSpeed(CmdPtr->Speed) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Outdoor Vertical Speed command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Outdoor Vertical Speed command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_OUTDOOR_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Outdoor Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableOutdoorControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_OUTDOOR_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Outdoor Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableOutdoorControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Outdoor Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Outdoor Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_OUTDOOR_COMBINED_YAW_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Outdoor Combined Yaw Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableOutdoorCombinedYawControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Combined Yaw Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Outdoor Combined Yaw Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_OUTDOOR_COMBINED_YAW_CONTROL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Outdoor Combined Yaw Control command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableOutdoorCombinedYawControl() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Outdoor Combined Yaw Control command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Outdoor Combined Yaw Control command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_FLYING_MODE_CC:
        {
        	EIM_FlightModeCmd_t *CmdPtr = (EIM_FlightModeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_FlightModeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Flying Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetFlyingMode(CmdPtr->Mode) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Flying Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Flying Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_ROUNDEL_HOVERING_RANGE_CC:
        {
        	EIM_AltitudeCmd_t *CmdPtr = (EIM_AltitudeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_AltitudeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Roundel Hovering Range command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetRoundelHoveringRange(CmdPtr->Altitude) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Roundel Hovering Range command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Roundel Hovering Range command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_EXECUTE_FLIGHT_ANIMATION_CC:
        {
        	EIM_FlightAnimationCmd_t *CmdPtr = (EIM_FlightAnimationCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_FlightAnimationCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Execute Flight Animation command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_ExecuteFlightAnimation(CmdPtr->Animation, CmdPtr->Duration) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Execute Flight Animation command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Execute Flight Animation command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_SINGLE_PLAYER_SSID_CC:
        {
        	EIM_SetSSIDCmd_t *CmdPtr = (EIM_SetSSIDCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetSSIDCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Single Player SSID command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetSinglePlayerSSID(CmdPtr->Name) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Single Player SSID command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Single Player SSID command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MULTI_PLAYER_SSID_CC:
        {
        	EIM_SetSSIDCmd_t *CmdPtr = (EIM_SetSSIDCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetSSIDCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Multi Player SSID command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMultiPlayerSSID(CmdPtr->Name) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Multi Player SSID command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Multi Player SSID command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_WIFI_MODE_CC:
        {
        	EIM_SetWifiModeCmd_t *CmdPtr = (EIM_SetWifiModeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_WifiMode_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Wifi Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetWifiMode(CmdPtr->Mode) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Wifi Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Wifi Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_WIFI_RATE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Wifi Rate command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetWifiRate() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Wifi Rate command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Wifi Rate command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_OWNER_MAC_CC:
        {
        	EIM_SetOwnerMac_t *CmdPtr = (EIM_SetOwnerMac_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetOwnerMac_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Owner Mac command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetOwnerMac(CmdPtr->MAC) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Owner Mac command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Owner Mac command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_ULTRASOUND_FREQ_CC:
        {
        	EIM_UltrasoundFreqCmd_t *CmdPtr = (EIM_UltrasoundFreqCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_UltrasoundFreqCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Ultrasound Freq command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetUltrasoundFreq(CmdPtr->Freq) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Ultrasound Freq command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Ultrasound Freq command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_ULTRASOUND_WATCHDOG_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Ultrasound Watchdog command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetUltrasoundWatchdog() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Ultrasound Watchdog command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Ultrasound Watchdog command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_CODEC_FPS_CC:
        {
        	EIM_FpsCmd_t *CmdPtr = (EIM_FpsCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_FpsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Codec FPS command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoCodecFPS(CmdPtr->FramesPerSecond) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Codec FPS command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Codec FPS command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_CODEC_CC:
        {
        	EIM_CodecTypeCmd_t *CmdPtr = (EIM_CodecTypeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_CodecTypeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Codec command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoCodec(CmdPtr->CodecType) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Codec command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Codec command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_SLICES_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Slices command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoSlices() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Slices command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Slices command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_LIVE_SOCKET_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Live Socket command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoLiveSocket() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Video Live Socket command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Video Live Socket command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_BITRATE_CC:
        {
        	EIM_BitRateCmd_t *CmdPtr = (EIM_BitRateCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_BitRateCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Bitrate command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoBitrate(CmdPtr->BitRate) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Bitrate command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Bitrate command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_MAX_VIDEO_BITRATE_CC:
        {
        	EIM_BitRateCmd_t *CmdPtr = (EIM_BitRateCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_BitRateCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Max Video Bitrate command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetMaxVideoBitrate(CmdPtr->BitRate) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Video Bitrate command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Max Video Bitrate command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_BITRATE_CONTROL_MODE_CC:
        {
        	EIM_SetVideoBitrateControlModeCmd_t *CmdPtr = (EIM_SetVideoBitrateControlModeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_VariableBitrate_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Bitrate Control Mode command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoBitrateControlMode(CmdPtr->Mode) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Bitrate Control Mode command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Bitrate Control Mode command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_BITRATE_STORAGE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Bitrate Storage command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoBitrateStorage() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Bitrate Storage command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Bitrate Storage command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_CHANNEL_CC:
        {
        	EIM_SetVideoChannelCmd_t *CmdPtr = (EIM_SetVideoChannelCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetVideoChannelCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video Channel command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoChannel(CmdPtr->Channel) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Channel command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video Channel command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_VIDEO_ON_USB_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Video On USB command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableVideoOnUSB() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Video On USB command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Video On USB command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_VIDEO_ON_USB_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Video On USB command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableVideoOnUSB() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Video On USB command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Video On USB command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_VIDEO_FILE_INDEX_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Video File Index command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetVideoFileIndex() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video File Index command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Video File Index command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_LED_ANIMATION_CC:
        {
        	EIM_LEDAnimationCmd_t *CmdPtr = (EIM_LEDAnimationCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_LEDAnimationCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set LED Animation command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetLEDAnimation(CmdPtr->Animation, CmdPtr->Frequency, CmdPtr->Duration) == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set LED Animation command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set LED Animation command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_ENEMY_COLORS_DETECT_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Enemy Colors Detect command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetEnemyColorsDetect() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Enemy Colors Detect command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Enemy Colors Detect command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_GROUNDSTRIPE_COLORS_DETECT_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Groundstripe Colors Detect command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetGroundStripeColorsDetect() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Groundstripe Colors Detect command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Groundstripe Colors Detect command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_ENABLE_ENEMY_OUTDOOR_SHELL_DETECT_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Enable Enemy Outdoor Shell Detect command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_EnableEnemyOutdoorShellDetect() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Enemy Outdoor Shell Detect command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Enable Enemy Outdoor Shell Detect command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_DISABLE_ENEMY_OUTDOOR_SHELL_DETECT_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Disable Enemy Outdoor Shell Detect command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_DisableEnemyOutdoorShellDetect() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Enemy Outdoor Shell Detect command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Disable Enemy Outdoor Shell Detect command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_DETECT_TYPE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Detect Type command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetDetectType() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detect Type command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detect Type command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_DETECTIONS_SELECT_H_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Detections Select H command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetDetectionsSelectH() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detections Select H command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detections Select H command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_DETECTIONS_SELECT_V_HSYNC_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Detections Select V HSync command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetDetectionsSelectVHSync() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detections Select V HSync command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detections Select V HSync command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_DETECTIONS_SELECT_V_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Detections Select V command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetDetectionsSelectV() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detections Select V command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Detections Select V command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_USERBOX_STOP_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Userbox Stop command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_UserboxStop() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Stop command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Stop command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_USERBOX_START_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Userbox Start command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_UserboxStart() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Start command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Start command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_USERBOX_SCREENSHOT_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Userbox Screenshot command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_UserboxScreenshot() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Screenshot command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Screenshot command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_USERBOX_CANCEL_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Userbox Cancel command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_UserboxCancel() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Cancel command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Userbox Cancel command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_LATITUDE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Latitude command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetLatitude() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Latitude command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Latitude command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_LONGITUDE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Longitude command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetLongitude() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Longitude command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Longitude command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_ALTITUDE_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Altitude command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetAltitude() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Altitude command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Altitude command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_APPLICATION_ID_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Application ID command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetApplicationID() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Application ID command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Application ID command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_APPLICATION_DESCRIPTION_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Application Description command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetApplicationDescription() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Application Description command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Application Description command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_PROFILE_ID_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Profile ID command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetProfileID() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Profile ID command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Profile ID command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_PROFILE_DESCRIPTION_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Profile Description command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetProfileDescription() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Profile Description command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Profile Description command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_SESSION_ID_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Session ID command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetSessionID() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Session ID command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Session ID command successful.");
                }
            }

            break;
    	}

        case EIM_ARDRONE2_SET_SESSION_DESCRIPTION_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Session Description command failed.  Length incorrect.");
            }
            else
            {
                if(EIM_ARDrone2_SetSessionDescription() == EIM_CMD_FAILED)
                {
                    EIM_AppData.Hk.ErrCounter++;
                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Session Description command failed.");
                }
                else
                {
                    EIM_AppData.Hk.CmdCounter++;

                    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                            "EIM: Set Session Description command successful.");
                }
            }

            break;
    	}

        case EIM_E_STOP_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Emergency Stop command failed.  Length incorrect.");
            }
            else
            {
                EIM_eStop();
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Emergency Stop command successful.");
            }

            break;
    	}

        case EIM_E_STOP_RESET_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Emergency Reset command failed.  Length incorrect.");
            }
            else
            {
                EIM_eStop();
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Emergency Reset command successful.");
            }

            break;
    	}

        case EIM_LAUNCH_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Launch command failed.  Length incorrect.");
            }
            else
            {
                EIM_takeOff();
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Launch command successful.");
            }

            break;
    	}

        case EIM_LAND_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Land command failed.  Length incorrect.");
            }
            else
            {
                EIM_land();

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Land command successful.");
            }

            break;
    	}

        case EIM_HOVER_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Hover command failed.  Length incorrect.");
            }
            else
            {
                EIM_hover();
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Hover command successful.");
            }

            break;
    	}

        case EIM_ROLL_CC:
        {
        	EIM_PercentageCmd_t *CmdPtr = (EIM_PercentageCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_PercentageCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Roll command failed.  Length incorrect.");
            }
            else
            {
                EIM_roll(CmdPtr->Percent);
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Roll successful.");
            }

            break;
    	}

        case EIM_PITCH_CC:
        {
        	EIM_PercentageCmd_t *CmdPtr = (EIM_PercentageCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_PercentageCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Pitch command failed.  Length incorrect.");
            }
            else
            {
            	EIM_pitch(CmdPtr->Percent);
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Pitch command successful.");
            }

            break;
    	}

        case EIM_YAW_CC:
        {
        	EIM_PercentageCmd_t *CmdPtr = (EIM_PercentageCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_PercentageCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Yaw command failed.  Length incorrect.");
            }
            else
            {
            	EIM_yaw(CmdPtr->Percent);
            	EIM_AppData.Hk.CmdCounter++;
            	CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
            			"EIM: Yaw command successful.");
            }

            break;
    	}

        case EIM_VERTICAL_CC:
        {
        	EIM_PercentageCmd_t *CmdPtr = (EIM_PercentageCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_PercentageCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Vertical Speed command failed.  Length incorrect.");
            }
            else
            {
                EIM_climb(CmdPtr->Percent);
                EIM_AppData.Hk.CmdCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Vertical Speed command successful.");
            }

            break;
        }

        case EIM_MOVE_CC:
        {
        	EIM_CombinedMovementCmd_t *CmdPtr = (EIM_CombinedMovementCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_CombinedMovementCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Move command failed.  Length incorrect.");
            }
            else
            {
            	EIM_move(1, CmdPtr->Roll, CmdPtr->Pitch, CmdPtr->Vertical, CmdPtr->Yaw);
                EIM_AppData.Hk.CmdCounter++;
            }

            break;
        }

        case EIM_SET_FLAT_TRIM_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Flat Trim command failed.  Length incorrect.");
            }
            else
            {
                EIM_setFlatTrim();
                EIM_AppData.Hk.CmdCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Set Flat Trim command successful.");
            }

            break;
        }

        case EIM_CALIBRATE_MAGNETOMETER_CC:
        {
            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_NoArgsCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Calibrate Magnetometer command failed.  Length incorrect.");
            }
            else
            {
            	EIM_CalibMagneto();
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Calibrate Magnetometer command successful.");
            }

            break;
        }

        case EIM_SET_CONTROL_MODE_CC:
        {
        	EIM_SetControlModeCmd_t *CmdPtr = (EIM_SetControlModeCmd_t*)EIM_AppData.MsgPtr;

            if(EIM_VerifyCmdLength(EIM_AppData.MsgPtr,sizeof(EIM_SetControlModeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
            {
                EIM_AppData.Hk.ErrCounter++;
                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                        "EIM: Set Control Mode command failed.  Length incorrect.");
            }
            else
            {
            	EIM_cmdSetControl((ARDrone2_ControlMode_t)CmdPtr->ControlMode);
                EIM_AppData.Hk.CmdCounter++;

                CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
                		"EIM: Set Control Mode command successful.");
            }

            break;
        }

        default:
        {
    		CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
    				"EIM: Invalid command code received.  CC=%u.", CommandCode);
            EIM_AppData.Hk.ErrCounter++;
            break;
        }
    }

    return;
}


EIM_CmdResponse_t EIM_ResetCtrsCmd(void)
{
	EIM_AppData.Hk.CmdCounter = 0;
    EIM_AppData.Hk.ErrCounter = 0;

    return EIM_CMD_SUCCESS;
} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_EnableNavDataCmd(void)
{
	int32 Status = CFE_SUCCESS;
	EIM_CmdResponse_t ReturnCode = EIM_CMD_FAILED;

	EIM_AppData.Hk.NavDataState = EIM_NAVDATA_INITIALIZING;

	/* Create child task for telemetry listening */
	Status = CFE_ES_CreateChildTask(
			&EIM_AppData.NavDataTlmTaskId,
			"EIMNavDataTlm",
			(CFE_ES_ChildTaskMainFuncPtr_t) EIM_NavDataTlmMain, 0, 16000, 50, 0);
	if(Status != CFE_SUCCESS)
	{
		CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
				"EIM: Failed to create telemetry listener task.");
		EIM_AppData.Hk.NavDataState = EIM_NAVDATA_FAILED;
		ReturnCode = EIM_CMD_FAILED;
	    goto end_of_function;
	}

	/* Create child task for ARDrone commanding */
	Status = CFE_ES_CreateChildTask(
			&EIM_AppData.NavDataCmdTaskId,
			"EIMNavDataCmd",
			(CFE_ES_ChildTaskMainFuncPtr_t) EIM_ATCmdMain, 0, 16000, 50, 0);
	if(Status != CFE_SUCCESS)
	{
		CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
				"EIM: Failed to create navdata command task.");
		EIM_AppData.Hk.NavDataState = EIM_NAVDATA_FAILED;
		ReturnCode = EIM_CMD_FAILED;
	    goto end_of_function;
	}

	ReturnCode = EIM_CMD_SUCCESS;

end_of_function:
    return ReturnCode;
} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_DisableNavDataCmd(void)
{
	int32 Status = CFE_SUCCESS;

	Status = CFE_ES_DeleteChildTask(EIM_AppData.NavDataTlmTaskId);
    if(Status != CFE_SUCCESS)
    {
    	CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
    			"EIM: Failed to delete telemetry listener task.");
    	EIM_AppData.Hk.NavDataState = EIM_NAVDATA_FAILED;
	}

	Status = CFE_ES_DeleteChildTask(EIM_AppData.NavDataCmdTaskId);
    if(Status != CFE_SUCCESS)
    {
    	CFE_EVS_SendEvent(EIM_TELEM_TASK_ERR_EID, CFE_EVS_ERROR,
    			"EIM: Failed to delete command task.");
    	EIM_AppData.Hk.NavDataState = EIM_NAVDATA_FAILED;
	}

    return EIM_CMD_SUCCESS;
} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_ActivateNavDataTagCmd(uint32 TagID)
{
	char options[100];

    EIM_AppData.navdata_options = EIM_AppData.navdata_options | (1 << TagID);
    sprintf(options, "%u", (unsigned int)EIM_AppData.navdata_options);
    EIM_configATCmd("general:navdata_options", options);

    return EIM_CMD_SUCCESS;

} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_DeactivateNavDataTagCmd(uint32 TagID)
{
	char options[100];

    EIM_AppData.navdata_options = EIM_AppData.navdata_options & ~(1 << TagID);
    sprintf(options, "%u", (unsigned int)EIM_AppData.navdata_options);
    EIM_configATCmd("general:navdata_options", options);

    return EIM_CMD_SUCCESS;

} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_ActivateNavDataDemoCmd(void)
{
	EIM_configATCmd("general:navdata_demo", "TRUE");

    return EIM_CMD_SUCCESS;

} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_DeactivateNavDataDemoCmd(void)
{
	EIM_configATCmd("general:navdata_demo", "FALSE");

    return EIM_CMD_SUCCESS;

} /* End of EIM_ResetCounters() */



EIM_CmdResponse_t EIM_ARDrone2_SetName(char *inName)
{
	char Name[EIM_NAME_LENGTH+1];

	strncpy(Name, inName, EIM_NAME_LENGTH);
	Name[EIM_NAME_LENGTH] = 0;
	EIM_configATCmd("GENERAL:ardrone_name", Name);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetWatchdogTimeout(uint32 Timeout)
{
	char sTimeout[100];

    sprintf(sTimeout, "%u", (unsigned int)Timeout);

	EIM_configATCmd("GENERAL:com_watchdog", sTimeout);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableVideo(void)
{
	EIM_configATCmd("general:video_enable", "TRUE");

    return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableVideo(void)
{
	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableVision(void)
{
	EIM_configATCmd("general:vision_enable", "TRUE");

    return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableVision(void)
{
	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableControl(void)
{
	char ControlLevelText[100];

    EIM_AppData.control_level = EIM_AppData.control_level | 0x0001;
    sprintf(ControlLevelText, "%u", (unsigned int)EIM_AppData.control_level);

    EIM_configATCmd("control:control_level", ControlLevelText);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableControl(void)
{
	char ControlLevelText[100];

    EIM_AppData.control_level = EIM_AppData.control_level & 0xfffe;
    sprintf(ControlLevelText, "%u", (unsigned int)EIM_AppData.control_level);

    EIM_configATCmd("control:control_level", ControlLevelText);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableCombinedYawControl(void)
{
	char ControlLevelText[100];

    EIM_AppData.control_level = EIM_AppData.control_level | 0x0002;
    sprintf(ControlLevelText, "%u", (unsigned int)EIM_AppData.control_level);

    EIM_configATCmd("control:control_level", ControlLevelText);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableCombinedYawControl(void)
{
	char ControlLevelText[100];

    EIM_AppData.control_level = EIM_AppData.control_level & 0xfffd;
    sprintf(ControlLevelText, "%u", (unsigned int)EIM_AppData.control_level);

    EIM_configATCmd("control:control_level", ControlLevelText);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxAngle(float angle)
{
	char angle_text[100];

	sprintf(angle_text, "%f", angle);

	EIM_configATCmd("control:euler_angle_max", angle_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxAltitude(uint32 altitude)
{
	char altitude_text[100];

	sprintf(altitude_text, "%u", (unsigned int)altitude);

	EIM_configATCmd("control:altitude_max", altitude_text);

	return EIM_CMD_SUCCESS;
}



EIM_CmdResponse_t EIM_ARDrone2_SetMinAltitude(uint32 altitude)
{
	char altitude_text[100];

	sprintf(altitude_text, "%u", (unsigned int)altitude);

	EIM_configATCmd("control:altitude_min", altitude_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxIPhoneTilt(float angle)
{
	char angle_text[100];

	sprintf(angle_text, "%f", angle);

	EIM_configATCmd("control:control_iphone_tilt", angle_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxVerticalSpeed(uint32 speed)
{
	char speed_text[100];

	sprintf(speed_text, "%u", (unsigned int)speed);

	EIM_configATCmd("control:control_vz_max", speed_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxYawSpeed(float speed)
{
	char speed_text[100];

	sprintf(speed_text, "%f", speed);

	EIM_configATCmd("control:control_yaw", speed_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorMode(void)
{
	EIM_configATCmd("control:outdoor", "TRUE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorMode(void)
{
	EIM_configATCmd("control:outdoor", "FALSE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorShell(void)
{
	EIM_configATCmd("control:flight_without_shell", "FALSE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorShell(void)
{
	EIM_configATCmd("control:flight_without_shell", "TRUE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableAutonomousMode(void)
{
	EIM_configATCmd("control:autonomous_flight", "TRUE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableAutonomousMode(void)
{
	EIM_configATCmd("control:autonomous_flight", "FALSE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetManualTrim(void)
{
	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxIndoorAngle(float angle)
{
	char angle_text[100];

	sprintf(angle_text, "%f", angle);

	EIM_configATCmd("control:indoor_euler_angle_max", angle_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxIndoorVerticalSpeed(uint32 speed)
{
	char speed_text[100];

	sprintf(speed_text, "%u", (unsigned int)speed);

	EIM_configATCmd("control:indoor_control_vz_max", speed_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableIndoorControl(void)
{
	char control_level_text[100];

    EIM_AppData.indoor_control_level = EIM_AppData.indoor_control_level | 0x0001;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.indoor_control_level);

    EIM_configATCmd("control:indoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableIndoorControl(void)
{
	char control_level_text[100];

    EIM_AppData.indoor_control_level = EIM_AppData.indoor_control_level & 0xfffe;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.indoor_control_level);

    EIM_configATCmd("control:indoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableIndoorCombinedYawControl(void)
{
	char control_level_text[100];

    EIM_AppData.indoor_control_level = EIM_AppData.indoor_control_level | 0x0002;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.indoor_control_level);

    EIM_configATCmd("control:indoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableIndoorCombinedYawControl(void)
{
	char control_level_text[100];

    EIM_AppData.indoor_control_level = EIM_AppData.indoor_control_level & 0xfffd;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.indoor_control_level);

    EIM_configATCmd("control:indoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetIndoorMaxAngle(float angle)
{
	char angle_text[100];

	sprintf(angle_text, "%f", angle);

	EIM_configATCmd("control:indoor_euler_angle_max", angle_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetIndoorMaxAltitude(uint32 altitude)
{
	char altitude_text[100];

	sprintf(altitude_text, "%u", (unsigned int)altitude);

	EIM_configATCmd("control:indoor_altitude_max", altitude_text);

	return EIM_CMD_SUCCESS;
}



EIM_CmdResponse_t EIM_ARDrone2_SetIndoorMinAltitude(uint32 altitude)
{
	char altitude_text[100];

	sprintf(altitude_text, "%u", (unsigned int)altitude);

	EIM_configATCmd("control:indoor_altitude_min", altitude_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxOutdoorAngle(float angle)
{
	char angle_text[100];

	sprintf(angle_text, "%f", angle);

	EIM_configATCmd("control:outdoor_euler_angle_max", angle_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxOutdoorVerticalSpeed(uint32 speed)
{
	char speed_text[100];

	sprintf(speed_text, "%u", (unsigned int)speed);

	EIM_configATCmd("control:outdoor_control_vz_max", speed_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorControl(void)
{
	char control_level_text[100];

    EIM_AppData.outdoor_control_level = EIM_AppData.outdoor_control_level | 0x0001;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.outdoor_control_level);

    EIM_configATCmd("control:outdoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorControl(void)
{
	char control_level_text[100];

    EIM_AppData.outdoor_control_level = EIM_AppData.outdoor_control_level & 0xfffe;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.outdoor_control_level);

    EIM_configATCmd("control:outdoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableOutdoorCombinedYawControl(void)
{
	char control_level_text[100];

    EIM_AppData.outdoor_control_level = EIM_AppData.outdoor_control_level | 0x0002;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.outdoor_control_level);

    EIM_configATCmd("control:outdoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableOutdoorCombinedYawControl(void)
{
	char control_level_text[100];

    EIM_AppData.outdoor_control_level = EIM_AppData.outdoor_control_level & 0xfffd;
    sprintf(control_level_text, "%u", (unsigned int)EIM_AppData.outdoor_control_level);

    EIM_configATCmd("control:outdoor_control_level", control_level_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetOutdoorMaxAngle(float angle)
{
	char angle_text[100];

	sprintf(angle_text, "%f", angle);

	EIM_configATCmd("control:outdoor_euler_angle_max", angle_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetOutdoorMaxAltitude(uint32 altitude)
{
	char altitude_text[100];

	sprintf(altitude_text, "%u", (unsigned int)altitude);

	EIM_configATCmd("control:outdoor_altitude_max", altitude_text);

	return EIM_CMD_SUCCESS;
}



EIM_CmdResponse_t EIM_ARDrone2_SetOutdoorMinAltitude(uint32 altitude)
{
	char altitude_text[100];

	sprintf(altitude_text, "%u", (unsigned int)altitude);

	EIM_configATCmd("control:outdoor_altitude_min", altitude_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetFlyingMode(EIM_ARDrone2_FlightModes_t mode)
{
	char mode_text[100];

    sprintf(mode_text, "%u", mode);

    EIM_configATCmd("control:flying_mode", mode_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetRoundelHoveringRange(uint32 range)
{
	char range_text[100];

	sprintf(range_text, "%u", (unsigned int)range);

	EIM_configATCmd("control:hovering_range", range_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_ExecuteFlightAnimation(EIM_FlightAnimation_t animation, uint32 duration)
{
	char params[100];

	snprintf(params, sizeof(params), "%d,%d", animation, duration);

    EIM_configATCmd("control:flight_anim", params);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetSinglePlayerSSID(char *inName)
{
	char Name[EIM_SSID_LENGTH+1];

	strncpy(Name, inName, EIM_SSID_LENGTH);
	Name[EIM_SSID_LENGTH] = 0;
	EIM_configATCmd("NETWORK:ssid_single_player", Name);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMultiPlayerSSID(char *Name)
{
    /* NETWORK:ssid_multi_player */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetWifiMode(EIM_WifiMode_t Mode)
{
	char param[100];

	snprintf(param, sizeof(param), "%u", Mode);

	EIM_configATCmd("network:wifi_mode", param);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetWifiRate(void)
{
    /* NETWORK:wifi_rate */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetOwnerMac(char *MAC)
{
	char param[100];

	snprintf(param, sizeof(param), "%u", MAC);

	EIM_configATCmd("network:owner_mac", param);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetUltrasoundFreq(EIM_ARDrone2_UltrasoundFreq_t freq)
{
	switch(freq)
	{
		case EIM_ULTRASOUND_22HZ:
		    EIM_configATCmd("pic:ultrasound_freq", "7");
		    return EIM_CMD_SUCCESS;
		    break;

		case EIM_ULTRASOUND_25HZ:
		    EIM_configATCmd("pic:ultrasound_freq", "7");
		    return EIM_CMD_SUCCESS;
		    break;

		default:
		    EIM_configATCmd("pic:ultrasound_freq", "7");
		    return EIM_CMD_FAILED;
	}

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetUltrasoundWatchdog(void)
{
    /* PIC:ultrasound_watchdog */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoCodecFPS(uint32 fps)
{
	char fps_text[100];

	if(fps > 30)
	{
		return EIM_CMD_FAILED;
	}

	sprintf(fps_text, "%u", (unsigned int)fps);

	EIM_configATCmd("video:codec_fps", fps_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoCodec(EIM_VideoCodecType_t codec)
{
	char codec_text[100];
	uint32	ardrone2_codec = 0;

	switch(codec)
	{
		case EIM_NULL_CODEC:
			ardrone2_codec = EIM_ARDRONE2_NULL_CODEC;
			break;

		case EIM_UVLC_CODEC:
			ardrone2_codec = EIM_ARDRONE2_UVLC_CODEC;
			break;

		case EIM_MJPEG_CODEC:
			ardrone2_codec = EIM_ARDRONE2_MJPEG_CODEC;
			break;

		case EIM_P263_CODEC:
			ardrone2_codec = EIM_ARDRONE2_P263_CODEC;
			break;

		case EIM_P264_CODEC:
			ardrone2_codec = EIM_ARDRONE2_P264_CODEC;
			break;

		case EIM_MP4_360P_CODEC:
			ardrone2_codec = EIM_ARDRONE2_MP4_360P_CODEC;
			break;

		case EIM_H264_360P_CODEC:
			ardrone2_codec = EIM_ARDRONE2_H264_360P_CODEC;
			break;

		case EIM_MP4_360P_H264_720P_CODEC:
			ardrone2_codec = EIM_ARDRONE2_MP4_360P_H264_720P_CODEC;
			break;

		case EIM_H264_720P_CODEC:
			ardrone2_codec = EIM_ARDRONE2_H264_720P_CODEC;
			break;

		case EIM_MP4_360P_SLRS_CODEC:
			ardrone2_codec = EIM_ARDRONE2_MP4_360P_SLRS_CODEC;
			break;

		case EIM_H264_360P_SLRS_CODEC:
			ardrone2_codec = EIM_ARDRONE2_H264_360P_SLRS_CODEC;
			break;

		case EIM_H264_720P_SLRS_CODEC:
			ardrone2_codec = EIM_ARDRONE2_H264_720P_SLRS_CODEC;
			break;

		case EIM_H264_AUTO_RESIZE_CODEC:
			ardrone2_codec = EIM_ARDRONE2_H264_AUTO_RESIZE_CODEC;
			break;

		case EIM_MP4_360P_H264_360P_CODEC:
			ardrone2_codec = EIM_ARDRONE2_MP4_360P_H264_360P_CODEC;
			break;

		default:
			return EIM_CMD_FAILED;
	}

	sprintf(codec_text, "%u", (unsigned int)ardrone2_codec);

	EIM_configATCmd("video:video_codec", codec_text);

	return EIM_CMD_SUCCESS;
}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoSlices(void)
{
    /* VIDEO:video_slices */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoLiveSocket(void)
{
    /* VIDEO:video_live_socket */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoBitrate(uint32 bitrate)
{
	char bitrate_text[100];

	snprintf(bitrate_text, sizeof(bitrate_text), "%u", (unsigned int)bitrate);

	EIM_configATCmd("video:bitrate", bitrate_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMaxVideoBitrate(uint32 bitrate)
{
	char bitrate_text[100];

	sprintf(bitrate_text, "%u", (unsigned int)bitrate);

	EIM_configATCmd("video:max_bitrate", bitrate_text);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoBitrateControlMode(EIM_VariableBitrate_t Mode)
{
	char param[100];

	sprintf(param, "%u", (unsigned int)Mode);

	EIM_configATCmd("video:bitrate_control_mode", param);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoBitrateStorage(void)
{
    /* VIDEO:bitrate_storage */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoChannel(EIM_VideoChannel_t Channel)
{
	char param[100];

	sprintf(param, "%u", (unsigned int)Channel);

	EIM_configATCmd("video:bitrate_storage", param);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableVideoOnUSB(void)
{
	EIM_configATCmd("video:video_on_usb", "TRUE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableVideoOnUSB(void)
{
	EIM_configATCmd("video:video_on_usb", "FALSE");

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVideoFileIndex(void)
{
    /* VIDEO:video_file_index */

	return EIM_CMD_FAILED;

}



EIM_CmdResponse_t EIM_ARDrone2_SetLEDAnimation(EIM_LEDAnimation_t Animation, float Frequency, uint32 Duration)
{
	char params[100];

	unsigned int *encFrequency = (unsigned int*)&Frequency;

	snprintf(params, sizeof(params), "%u,%u,%u", (unsigned int)Animation, *encFrequency, (unsigned int)Duration);

	EIM_configATCmd("leds:leds_anim", params);

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetEnemyColorsDetect(void)
{
    /* DETECT:enemy_colors */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetGroundStripeColorsDetect(void)
{
    /* DETECT:groundstripe_colors */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EnableEnemyOutdoorShellDetect(void)
{
    /* DETECT:enemy_without_shell */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_DisableEnemyOutdoorShellDetect(void)
{
    /* DETECT:enemy_without_shell */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetDetectType(void)
{
    /* DETECT:detect_type */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetDetectionsSelectH(void)
{
    /* DETECT:detections_select_h */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetDetectionsSelectVHSync(void)
{
    /* DETECT:detections_select_v_hsync */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetDetectionsSelectV(void)
{
    /* DETECT:detections_select_v */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_UserboxStop(void)
{
    /* USERBOX:userbox_cmd */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_UserboxStart(void)
{
    /* USERBOX:userbox_cmd */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_UserboxScreenshot(void)
{
    /* USERBOX:userbox_cmd */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_UserboxCancel(void)
{
    /* USERBOX:userbox_cmd */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetLatitude(void)
{
    /* GPS:latitude */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetLongitude(void)
{
    /* GPS:longitude */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetAltitude(void)
{
    /* GPS:altitude */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetApplicationID(void)
{
    /* CUSTOM:application_id */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetApplicationDescription(void)
{
    /* CUSTOM:application_desc */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetProfileID(void)
{
    /* CUSTOM:profile_id */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetProfileDescription(void)
{
    /* CUSTOM:profile_desc */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetSessionID(void)
{
    /* CUSTOM:session_id */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetSessionDescription(void)
{
    /* CUSTOM:session_desc */

	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EmergencyStop(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_EmergencyStopReset(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_Launch(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_Land(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_Hover(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetRoll(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetPitch(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetYawSpeed(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetVerticalSpeed(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetMovement(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_SetFlatTrim(void)
{
	return EIM_CMD_SUCCESS;

}



EIM_CmdResponse_t EIM_ARDrone2_CalibrateMagnetometer(void)
{
	return EIM_CMD_SUCCESS;

}



void EIM_SetControlModeCmd(CFE_SB_MsgPtr_t MessagePtr)
{
	EIM_SetControlModeCmd_t *CmdPtr = ((EIM_SetControlModeCmd_t *)MessagePtr);
    if(EIM_VerifyCmdLength(MessagePtr,sizeof(EIM_SetControlModeCmd_t))==EIM_BAD_MSG_LENGTH_RC)
    {
        EIM_AppData.Hk.ErrCounter++;
    }
    else
    {
    	EIM_cmdSetControl((ARDrone2_ControlMode_t)CmdPtr->ControlMode);

    	/* Status of commands processed by EIM task */
    	EIM_AppData.Hk.CmdCounter++;
    }

    CFE_EVS_SendEvent(EIM_RESET_CMD_EID, CFE_EVS_INFORMATION,
            "EIM: Enable NAVDATA DEMO command");
} /* End of EIM_ResetCounters() */



int32 EIM_VerifyCmdLength (CFE_SB_MsgPtr_t MessagePtr, uint32 ExpectedLength)
{
    int32               Status = EIM_SUCCESS;
    CFE_SB_MsgId_t      MessageID;
    uint16              CommandCode;
    uint16              ActualLength;

    ActualLength = CFE_SB_GetTotalMsgLength (MessagePtr);

    if (ExpectedLength != ActualLength)
    {

        MessageID   = CFE_SB_GetMsgId   (MessagePtr);
        CommandCode = CFE_SB_GetCmdCode (MessagePtr);

        CFE_EVS_SendEvent(EIM_CMD_LEN_ERR_EID, CFE_EVS_ERROR,
          "Cmd Msg with Bad length Rcvd: ID = 0x%X, CC = %d, Exp Len = %d, Len = %d",
          MessageID, CommandCode, ExpectedLength, ActualLength);

        Status = EIM_BAD_MSG_LENGTH_RC;

    }

    return Status;

} /* end of EIM_VerifyCmdLength () */

#ifdef __cplusplus
}
#endif
