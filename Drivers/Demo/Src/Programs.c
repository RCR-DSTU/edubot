#include "Programs.h"
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"
#include "ADC_Bottom.h"





EduBot robot;
Program demo;


void Robot_Init(void){
	robot.currentProg = 0;
	robot.currentPage = 0;
	robot.number_clicks_button5 = 0;
	robot.input_arg = 0.0;
	robot.isStart = false;
	robot.currentCycle = 0;
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
			Line_regulator.target = robot.input_arg;

//			HAL_TIM_Base_Start_IT(&htim5);
			robot.demo.runner = &RunnerProgram1;
			robot.demo.draw = &DrawProgram1;
			break;
		case 2:
			PID_Init();

			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

			robot.isStart = true;

			Line_regulator.target = 75;

//			HAL_TIM_Base_Start_IT(&htim5);

			robot.demo.runner = &RunnerProgram2;
			robot.demo.draw = &DrawProgram2;
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

			Line_regulator.target = 0.0;

//			HAL_TIM_Base_Stop_IT(&htim5);


			robot.demo.runner = 0;

			break;
		case 2:
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);

//			HAL_TIM_Base_Stop_IT(&htim5);

			Line_regulator.target = 0.0;

			robot.demo.runner = 0;
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
		if(Line_regulator.error <= Line_regulator.pid_error_end &&
		   Line_regulator.error >= -Line_regulator.pid_error_end) Line_regulator.pid_finish = 1;
		else Line_regulator.pid_finish = 0;

		PID_regulator[0].target = Line_regulator.output;
		PID_regulator[1].target = Line_regulator.output;
		SetVoltage_Left(PID_regulator[0].output);
		SetVoltage_Right(PID_regulator[1].output);
	}
}


void InformationForProgram1(void)
{
	robot.dist[0] += wheel_angle[0];

	robot.dist[1] += wheel_angle[1];

	Line_regulator.current = (-robot.dist[0] + robot.dist[1]) / 2;

	robot.distanse = Line_regulator.current; // Distance to screen

	robot.speed = (-wheel_v[0] + wheel_v[1]) / 2; // Speed to screen

	robot.progress = Line_regulator.current / Line_regulator.target; // Progress bar

	TIM2->CNT = 0;
	TIM3->CNT = 0;
}



void RunnerProgram2(void)
{
	if(Line_regulator.pid_finish)
	{
		PID_regulator[0].target = 0.0;
		PID_regulator[1].target = 0.0;
		PID_regulator[0].current = 0.0;
		PID_regulator[1].current = 0.0;
		Line_regulator.target = 0.0;
		Line_regulator.sum_error = 0.0;
		SetVoltage_Left(0.0);
		SetVoltage_Right(0.0);
		robot.isStart = false;

	} else
	{
		PID_Calc();
		PID_regulator[0].target = 0.2 + Line_regulator.output;
		PID_regulator[1].target = 0.2 - Line_regulator.output;
		SetVoltage_Left(PID_regulator[0].output);
		SetVoltage_Right(PID_regulator[1].output);

	}
}


void InformationForProgram2(void)
{
	ADC_Read(4);
	HAL_ADC_Start(&hadc1);

	HAL_ADC_PollForConversion(&hadc1, 100);

	robot.ADC_Values[1] = (uint32_t) HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Stop(&hadc1);

	HAL_Delay(200);

	ADC_Read(1);
	HAL_ADC_Start(&hadc1);

	HAL_ADC_PollForConversion(&hadc1, 100);

	robot.ADC_Values[3] = (uint32_t) HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Stop(&hadc1);

	HAL_Delay(200);

	Line_regulator.current = robot.ADC_Values[1] - robot.ADC_Values[3];

}

void DrawProgram1(void)
{
	switch(robot.currentCycle)
	{
		case 0:
			ProgressBar(robot.progress);
			robot.currentCycle++;
			break;
		case 1:
			FloatToChar(robot.speed, speed_str);
			robot.currentCycle++;
			break;
		case 2:
			FloatToChar(robot.distanse, dist_str);
			robot.currentCycle++;
			break;
		case 3:
			SSD1306_GotoXY(10, 30);
			SSD1306_Puts("Distance:", &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(75, 30);
			FloatToChar(robot.distanse, dist_str);
			SSD1306_Puts(dist_str, &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			robot.currentCycle++;
			break;
		case 4:
			SSD1306_GotoXY(10, 18);
			SSD1306_Puts("Speed:", &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(54, 18);
			FloatToChar(robot.speed, speed_str);
			SSD1306_Puts(speed_str, &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			robot.currentCycle = 0;
			break;

	}
}

void DrawProgram2(void)
{
	switch(robot.currentCycle)
	{
		case 0:
			ProgressBar(robot.progress);
			robot.currentCycle++;
			break;
		case 1:
			FloatToChar(robot.speed, speed_str);
			robot.currentCycle++;
			break;
		case 2:
			FloatToChar(robot.distanse, dist_str);
			robot.currentCycle++;
			break;
		case 3:
			SSD1306_GotoXY(10, 30);
			SSD1306_Puts("Distance:", &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(75, 30);
			FloatToChar(robot.distanse, dist_str);
			SSD1306_Puts(dist_str, &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			robot.currentCycle++;
			break;
		case 4:
			SSD1306_GotoXY(10, 18);
			SSD1306_Puts("Speed:", &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_GotoXY(54, 18);
			FloatToChar(robot.speed, speed_str);
			SSD1306_Puts(speed_str, &Font_7x10, SSD1306_COLOR_WHITE);
			SSD1306_UpdateScreen();
			robot.currentCycle = 0;
			break;

	}
}





