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

#ifndef _eim_events_
#define _eim_events_

/*************************************************************************
**
** Include section
**
**************************************************************************/

/*
** (none)
*/

/*************************************************************************
**
** Macro definitions
**
**************************************************************************/

#define EIM_STARTUP_INF_EID             1
#define EIM_COMMAND_ERR_EID             2
#define EIM_LEN_ERR_EID                 4
#define EIM_IMU_READ_ERR_EID            6
#define EIM_IMU_INIT_ERR_EID            7
#define EIM_MAG_READ_ERR_EID            8
#define EIM_IMU_QUEUE_OVERRUN_ERR_EID   9
#define EIM_IMU_QUEUE_UNDERRUN_ERR_EID  10
#define EIM_MAG_INIT_ERR_EID            11
#define EIM_I2C_ERR_EID                 12
#define EIM_INVALID_PARAM_ERR_EID       13

#define EIM_NOOP_CMD_EID				20
#define EIM_RESET_CMD_EID				21
#define EIM_ENABLE_NAVDATA_CMD_EID		22
#define EIM_DISABLE_NAVDATA_CMD_EID		23
#define EIM_CMD_LEN_ERR_EID				24
#define EIM_TELEM_TASK_ERR_EID			25
#define EIM_TELEM_SOCKET_READ_ERR_EID	26
#define EIM_TELEM_INIT_EID				27
#define EIM_TELEM_CHECKSUM_ERR_EID		28
#define EIM_TELEM_SEQUENCE_ERR_EID		29
#define EIM_NAVCMD_INIT_ERR_EID			30
#define EIM_TELEM_PACKET_ERR_EID		31

/************************/
/*  End of File Comment */
/************************/

#endif
