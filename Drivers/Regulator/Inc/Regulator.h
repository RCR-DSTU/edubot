#pragma once

#define wheel_r  0.022
#define length  0.1256628
#define enc_cnt_per_rot  1580.0
#define disk_to_real	((2*3.14157*wheel_r) / enc_cnt_per_rot)

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
#include <stdint.h>
#include "demo.h"

extern int16_t Enc[2];
extern float wheel_angle[2];
extern float wheel_w[2];
extern float wheel_v[2];

extern float goal;

typedef struct
{
float K_p;
float I_p;
float D_p;
float Max_output;
float Min_output;
float Max_sum_error;
float output;
float current;
float target;
float error;
float prev_error;
float sum_error;
float pid_error_end;
char pid_finish;
}PID;

extern PID PID_regulator[2];
extern PID Line_regulator;

extern void SetVoltage_Left(float Duty);

extern void SetVoltage_Right(float Duty);

void PID_Init();

extern void PID_Calc();


