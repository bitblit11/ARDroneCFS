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

#ifndef _EIM_NAVCMDS_H_
#define _EIM_NAVCMDS_H_

/*
** Include Files
*/
#include "cfe.h"
#include "navdata.h"


typedef enum
{
  NO_CONTROL_MODE = 0,          /**< Doing nothing */
  ARDRONE_UPDATE_CONTROL_MODE,  /**< Not used */
  PIC_UPDATE_CONTROL_MODE,      /**< Not used */
  LOGS_GET_CONTROL_MODE,        /**< Not used */
  CFG_GET_CONTROL_MODE,         /**< Send active configuration file to a client
                                     through the 'control' socket UDP 5559 */
  ACK_CONTROL_MODE,             /**< Reset command mask in navdata */
  CUSTOM_CFG_GET_CONTROL_MODE   /**< Requests the list of custom config. IDs */
} ARDrone2_ControlMode_t;

/* CFS App function prototypes */
void EIM_ATCmdMain(void);
int  EIM_InitATCmdSockets(void);
void EIM_configATCmd(const char *, const char *);
void EIM_cmdSetControl(ARDrone2_ControlMode_t controlMode);

void EIM_setFlatTrim(void);
void EIM_takeOff(void);
void EIM_land(void);
void EIM_eStop(void);
void EIM_reset(void);
void EIM_hover(void);
void EIM_pitch(float pitch);
void EIM_roll(float roll);
void EIM_yaw(float ySpeed);
void EIM_climb(float vSpeed);
void EIM_move(int, float, float, float, float);
void EIM_CalibMagneto(void);
void EIM_cmdComWdg(void);

#endif /* EIM_NAVCMDS_H_ */
