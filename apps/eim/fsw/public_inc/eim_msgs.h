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


#ifndef EIM_MSG_H_
#define EIM_MSG_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "common_types.h"
#include "cfe.h"

#define EIM_IMU_SAMPLE_RATE_IN_HZ           400
#define EIM_IMU_CYCLE_RATE_IN_HZ            200
#define EIM_IMU_SAMPLE_PERIOD_IN_MICROS     (1000000 / EIM_IMU_SAMPLE_RATE_IN_HZ)
#define EIM_IMU_SAMPLES_PER_CYCLE           (EIM_IMU_SAMPLE_RATE_IN_HZ / EIM_IMU_CYCLE_RATE_IN_HZ)

#define EIM_IMU_MAX_SAMPLES_PER_MSG         (EIM_IMU_SAMPLES_PER_CYCLE + 1)
#define EIM_IMU_MIN_SAMPLES_PER_MSG         (EIM_IMU_SAMPLES_PER_CYCLE - 1)
#define EIM_MAX_MOTOR_SPEED_CONTROL_CNT     3

typedef struct
{
    CFE_TIME_SysTime_t  TimeStamp;
    uint32              RateValidity;
    double              MsgRateData[EIM_IMU_MAX_SAMPLES_PER_MSG]; /* d/s Rate data on IMU measurements */
    uint32              AccValidity;
    double              MsgAccData[3];  /* Gs  Accel data on IMU measurements */
    uint32              MagValidity;
    double              MsgMagData[3];  /* ?  Magnetometer measurements of IMU */
} EIM_IMU_Sample_t;

typedef struct
{
    uint8               TlmHeader[CFE_SB_TLM_HDR_SIZE]; /** s cFE Software Bus Telemetry Message Header */
    uint32              SampleCnt;
    EIM_IMU_Sample_t    ImuSample[EIM_IMU_MAX_SAMPLES_PER_MSG];
} EIM_IMU_Msg_t;

typedef struct
{
    uint8               TlmHeader[CFE_SB_TLM_HDR_SIZE]; /** s cFE Software Bus Telemetry Message Header */
    uint32              SampleCnt;
    uint32              Validity;
    double              Sample[3];
} EIM_Mag_Msg_t;


typedef struct
{
    uint8               TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32              MotorCnt;
    double              Speed[EIM_MAX_MOTOR_SPEED_CONTROL_CNT];
} EIM_MotorSpeed_Msg_t;


#ifdef __cplusplus
}
#endif

#endif /* EIM_MSG_H_ */
