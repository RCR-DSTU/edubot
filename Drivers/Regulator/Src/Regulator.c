#include "Regulator.h"

int16_t Enc[2] = {0.0,0.0};
float wheel_angle[2] = {0.0,0.0};
float wheel_w[2] = {0.0,0.0};
float wheel_v[2] ={0.0,0.0};
PID PID_regulator[2];
PID Line_regulator;

float goal = 0.04;


void SetVoltage_Left(float Duty)
{

	if(Duty >= 0)
	{
		HAL_GPIO_WritePin(GPIOB, BTN1_DIR_Pin, GPIO_PIN_RESET);
		TIM1->CCR1 = ((int32_t) (Duty * TIM1->ARR));
		return;
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, BTN1_DIR_Pin, GPIO_PIN_SET);
		TIM1->CCR1 = ((int32_t)(TIM1->ARR + (Duty * TIM1->ARR)));
	}
}


void SetVoltage_Right(float Duty)
{
	if(Duty >= 0)
		{
			HAL_GPIO_WritePin(GPIOB, BTN2_DIR_Pin, GPIO_PIN_RESET);
			TIM1->CCR2 = ((int32_t) (Duty * TIM1->ARR));
			return;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, BTN2_DIR_Pin, GPIO_PIN_SET);
			TIM1->CCR2 = ((int32_t)(TIM1->ARR + (Duty * TIM1->ARR)));
		}
}

void PID_on(void) {
	Line_regulator.pid_finish = 0;
}

void PID_Init()
{
PID_regulator[0].K_p = 1.0;
PID_regulator[0].I_p = 0.35;
PID_regulator[0].D_p = 0.25;
PID_regulator[0].current = 0.0;
PID_regulator[0].target = 0.0;
PID_regulator[0].error = 0.0;
PID_regulator[0].Max_output = 1.0;
PID_regulator[0].Min_output = 0.01;
PID_regulator[0].Max_sum_error = 5.0;
PID_regulator[0].prev_error = 0.0;
PID_regulator[0].sum_error = 0.0;

PID_regulator[1].K_p = 1.0;
PID_regulator[1].I_p = 0.35;
PID_regulator[1].D_p = 0.2;
PID_regulator[1].current = 0.0;
PID_regulator[1].target = 0.0;
PID_regulator[1].error = 0.0;
PID_regulator[1].Max_output = 1.0;
PID_regulator[1].Min_output = 0.01;
PID_regulator[1].Max_sum_error = 5.0;
PID_regulator[1].prev_error = 0.0;
PID_regulator[1].sum_error = 0.0;

Line_regulator.K_p = 0.15;
Line_regulator.I_p = 0.1;
Line_regulator.D_p = 0.0;
Line_regulator.current = 0.0;
Line_regulator.target = robot.input_arg;
Line_regulator.error = 0.0;
Line_regulator.Max_output = 0.04;
Line_regulator.Min_output = 0.02;
Line_regulator.Max_sum_error = 2.0;
Line_regulator.prev_error = 0.0;
Line_regulator.sum_error = 0.0;
Line_regulator.pid_error_end = 0.001;
}


void PID_Calc()
{
PID_regulator[0].error = PID_regulator[0].target - PID_regulator[0].current;
PID_regulator[0].sum_error += PID_regulator[0].error;
if(PID_regulator[0].sum_error > PID_regulator[0].Max_sum_error) PID_regulator[0].sum_error = PID_regulator[0].Max_sum_error;
if(PID_regulator[0].sum_error < -PID_regulator[0].Max_sum_error) PID_regulator[0].sum_error = -PID_regulator[0].Max_sum_error;

PID_regulator[0].output = (PID_regulator[0].K_p * PID_regulator[0].error) + (PID_regulator[0].I_p * PID_regulator[0].sum_error) + (PID_regulator[0].D_p * PID_regulator[0].prev_error);
if(PID_regulator[0].output < -PID_regulator[0].Max_output) PID_regulator[0].output = -1.0;
if(PID_regulator[0].output > PID_regulator[0].Max_output) PID_regulator[0].output = 1.0;
PID_regulator[0].prev_error = PID_regulator[0].error;


PID_regulator[1].error = PID_regulator[1].target - PID_regulator[1].current;
PID_regulator[1].sum_error += PID_regulator[1].error;
if(PID_regulator[1].sum_error > PID_regulator[1].Max_sum_error) PID_regulator[1].sum_error = PID_regulator[1].Max_sum_error;
if(PID_regulator[1].sum_error < -PID_regulator[1].Max_sum_error) PID_regulator[1].sum_error = -PID_regulator[1].Max_sum_error;

PID_regulator[1].output = (PID_regulator[1].K_p * PID_regulator[1].error) + (PID_regulator[1].I_p * PID_regulator[1].sum_error) + (PID_regulator[1].D_p * PID_regulator[1].prev_error);
if(PID_regulator[1].output < -PID_regulator[1].Max_output) PID_regulator[1].output = -1.0;
if(PID_regulator[1].output > PID_regulator[1].Max_output) PID_regulator[1].output = 1.0;
PID_regulator[1].prev_error = PID_regulator[1].error;


Line_regulator.error = Line_regulator.target - Line_regulator.current;
Line_regulator.sum_error += Line_regulator.error;
if(Line_regulator.sum_error > Line_regulator.Max_sum_error) Line_regulator.sum_error = Line_regulator.Max_sum_error;
if(Line_regulator.sum_error < -Line_regulator.Max_sum_error) Line_regulator.sum_error = -Line_regulator.Max_sum_error;

Line_regulator.output = (Line_regulator.K_p * Line_regulator.error) + (Line_regulator.I_p * Line_regulator.sum_error) + (Line_regulator.D_p * Line_regulator.prev_error);
if(Line_regulator.output < -Line_regulator.Max_output) Line_regulator.output = Line_regulator.Min_output;
if(Line_regulator.output > Line_regulator.Max_output) Line_regulator.output = Line_regulator.Max_output;
Line_regulator.prev_error = Line_regulator.error;
if(Line_regulator.error <= Line_regulator.pid_error_end &&
   Line_regulator.error >= -Line_regulator.pid_error_end) Line_regulator.pid_finish = 1;
else Line_regulator.pid_finish = 0;
}










