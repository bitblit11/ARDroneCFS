/*
 * eim_msg.h
 *
 *  Created on: Jun 25, 2013
 *      Author: userdev
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
