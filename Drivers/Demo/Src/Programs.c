#include "Programs.h"

EduBot robot;
Program demo;



//robot.demo.constructor();

void Robot_Init(void){
	robot.currentProg = 0;
	robot.currentPage = 0;
	robot.number_clicks_button5 = 0;
	robot.input_arg = 0.0;
	robot.isStart = false;
}



void ConstrctionProgram(void) {

	switch(robot.currentProg + 1)
	{
		case 1:
			PID_Init();

			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

			HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
			HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);

			HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
			HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);

			robot.isStart = true;

			HAL_TIM_Base_Start_IT(&htim4);
			HAL_TIM_Base_Start_IT(&htim5);

			robot.demo.runner = &RunnerProgram1;
			robot.demo.critical_ticks = 50;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
	}
}


void DestrctionProgram(void) {

	switch(robot.currentProg + 1)
	{
		case 1:
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);

			HAL_TIM_Encoder_Stop(&htim2, TIM_CHANNEL_1);
			HAL_TIM_Encoder_Stop(&htim2, TIM_CHANNEL_2);

			HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_1);
			HAL_TIM_Encoder_Stop(&htim3, TIM_CHANNEL_2);

			robot.distanse = 0.0;

			HAL_TIM_Base_Stop_IT(&htim5);
			HAL_TIM_Base_Stop_IT(&htim4);

			robot.demo.runner = 0;

			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
	}
}


void RunnerProgram1(void){


	if(Line_regulator.pid_finish)
	{
		PID_regulator[0].target = 0.0;
		PID_regulator[1].target = 0.0;
		Line_regulator.target = 0.0;
		Line_regulator.sum_error = 0.0;
		SetVoltage_Left(0.0);
		SetVoltage_Right(0.0);
		robot.isStart = false;

	} else
	{
		PID_Calc();
		PID_regulator[0].target = Line_regulator.output;
		PID_regulator[1].target = Line_regulator.output;
		SetVoltage_Left(PID_regulator[0].output);
		SetVoltage_Right(PID_regulator[1].output);

	}


}









