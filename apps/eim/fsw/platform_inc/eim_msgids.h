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

#ifndef _eim_msgids_h_
#define _eim_msgids_h_

/**************************
** EIM Command Message IDs
***************************/
#define EIM_CMD_MID                    0x18d0 /**< \brief EIM Ground Commands Message ID */
#define EIM_SEND_HK_MID                0x18d1 /**< \brief EIM Send Housekeeping Message ID */
#define EIM_UNUSED_MID                 0x18d2 /**< \brief EIM MDT Unused Message Message ID */


/**************************
** Wake Up Message IDs
***************************/
#define EIM_GPS_IN_MID          0x0697
#define EIM_GPS_OUT_MID         0x0698
#define EIM_IMU_IN_MID          0x0699
#define EIM_BARO_IN_MID         0x069a
#define EIM_LED_OUT_MID         0x069b
#define EIM_SWITCH_IN_MID       0x069c
#define EIM_BUTTON_IN_MID       0x069d
#define EIM_SONIC_ALT_IN_MID    0x069e
#define EIM_ALARM_OUT_MID       0x069f
#define EIM_MOTOR_SPEED_OUT_MID 0x06a0
#define EIM_MAG_IN_MID          0x06a1

/***************************
 * Sensor and Effector Msgs
 */
#define EIM_IMU_MID                 0x0896
#define EIM_SET_MOTOR_SPEED_MID     0x0897


/***************************
** EIM Telemetry Message IDs
****************************/
#define EIM_HK_TLM_MID                 0x0898 /**< \brief EIM Housekeeping Telemetry Message ID */
#define EIM_DIAG_TLM_MID               0x0899 /**< \brief EIM Diagnostic Telemetry Message ID */
/* 
#define EIM_TLM_SPARE1                 0x0899
#define EIM_TLM_SPARE2                 0x089A
*/

#endif /* _eim_msgids_h_ */

/************************/
/*  End of File Comment */
/************************/
