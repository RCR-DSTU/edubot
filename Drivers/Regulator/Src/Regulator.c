#include "Regulator.h"

int16_t Enc[2] = {0.0,0.0};
float wheel_angle[2] = {0.0,0.0};
float wheel_w[2] = {0.0,0.0};
float wheel_v[2] ={0.0,0.0};
PID PID_regulator[2];

float goal = 0.0;


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
			HAL_GPIO_WritePin(GPIOB, BTN1_DIR_Pin, GPIO_PIN_SET);
			TIM1->CCR2 = ((int32_t)(TIM1->ARR + (Duty * TIM1->ARR)));
		}
}



void PID_Init()
{
PID_regulator[0].K_p = 1.0;
PID_regulator[0].I_p = 0.0;
PID_regulator[0].D_p = 0.0;
PID_regulator[0].current = 0.0;
PID_regulator[0].target = 0.2;
PID_regulator[0].error = 0.0;
PID_regulator[0].Max_output = 1.0;
PID_regulator[0].Min_output = 0.01;
PID_regulator[0].Max_sum_error = 5.0;
PID_regulator[0].prev_error = 0.0;
PID_regulator[0].sum_error = 0.0;

PID_regulator[1].K_p = 1.0;
PID_regulator[1].I_p = 0.0;
PID_regulator[1].D_p = 0.0;
PID_regulator[1].current = 0.0;
PID_regulator[1].target = 0.2;
PID_regulator[1].error = 0.0;
PID_regulator[1].Max_output = 1.0;
PID_regulator[1].Min_output = 0.01;
PID_regulator[1].Max_sum_error = 5.0;
PID_regulator[1].prev_error = 0.0;
PID_regulator[1].sum_error = 0.0;
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
}










