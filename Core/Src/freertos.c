/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "demo.h"
#include "Regulator.h"
#include "Programs.h"
#include "ADC_Bottom.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .cb_mem = &defaultTaskControlBlock,
  .cb_size = sizeof(defaultTaskControlBlock),
  .stack_mem = &defaultTaskBuffer[0],
  .stack_size = sizeof(defaultTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Display */
osThreadId_t DisplayHandle;
uint32_t DisplayBuffer[ 128 ];
osStaticThreadDef_t DisplayControlBlock;
const osThreadAttr_t Display_attributes = {
  .name = "Display",
  .cb_mem = &DisplayControlBlock,
  .cb_size = sizeof(DisplayControlBlock),
  .stack_mem = &DisplayBuffer[0],
  .stack_size = sizeof(DisplayBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for demo1 */
osThreadId_t demo1Handle;
const osThreadAttr_t demo1_attributes = {
  .name = "demo1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for demo2 */
osThreadId_t demo2Handle;
const osThreadAttr_t demo2_attributes = {
  .name = "demo2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for SpeedPID */
osTimerId_t SpeedPIDHandle;
const osTimerAttr_t SpeedPID_attributes = {
  .name = "SpeedPID"
};
/* Definitions for LinePID */
osTimerId_t LinePIDHandle;
const osTimerAttr_t LinePID_attributes = {
  .name = "LinePID"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartTask(void *argument);
void DisplayTask(void *argument);
void Program1Task(void *argument);
void Program2Task(void *argument);
void SpeedPID_Callback(void *argument);
void LinePID_Callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of SpeedPID */
  SpeedPIDHandle = osTimerNew(SpeedPID_Callback, osTimerPeriodic, NULL, &SpeedPID_attributes);

  /* creation of LinePID */
  LinePIDHandle = osTimerNew(LinePID_Callback, osTimerPeriodic, NULL, &LinePID_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartTask, NULL, &defaultTask_attributes);

  /* creation of Display */
  DisplayHandle = osThreadNew(DisplayTask, NULL, &Display_attributes);

  /* creation of demo1 */
//  demo1Handle = osThreadNew(Program1Task, NULL, &demo1_attributes);

  /* creation of demo2 */
//  demo2Handle = osThreadNew(Program2Task, NULL, &demo2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  osThreadSuspend(DisplayHandle);
  osThreadSuspend(demo1Handle);
  osThreadSuspend(demo2Handle);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask */
void StartTask(void *argument)
{
  /* USER CODE BEGIN StartTask */
	  robot.globalState = 0;
  /* Infinite loop */
  for(;;)
  {
	  Robot_Init();

	  osThreadResume(DisplayHandle);
	  osThreadSuspend(defaultTaskHandle);
	  taskYIELD();

	  robot.demo.constructor = &ConstrctionProgram;
	  robot.demo.destructor = &DestrctionProgram;
	  robot.globalState++;

	  if(robot.currentProg == 0) demo1Handle = osThreadNew(Program1Task, NULL, &demo1_attributes);
	  if(robot.currentProg == 1) demo2Handle = osThreadNew(Program2Task, NULL, &demo2_attributes);

	  osThreadResume(DisplayHandle);
	  osThreadResume(demo1Handle);
	  osThreadSuspend(defaultTaskHandle);

  }
  /* USER CODE END StartTask */
}

/* USER CODE BEGIN Header_DisplayTask */
/**
* @brief Function implementing the Display thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DisplayTask */
void DisplayTask(void *argument)
{
  /* USER CODE BEGIN DisplayTask */
  /* Infinite loop */
  for(;;)
  {
	  switch(robot.globalState)
	  {
	  // welcome window
	  case 0:
		  SSD1306_Init();

		  FirstScreen();
		  SSD1306_UpdateScreen();

		  HAL_Delay(4000);
		  SSD1306_Fill(SSD1306_COLOR_BLACK);

		  MenuRectangle();
		  SSD1306_DrawFilledRectangle(indicator_X, indicator_Y, 110, 13, SSD1306_COLOR_WHITE);
		  ShowMenuItems();

		  SSD1306_UpdateScreen();
		  robot.globalState = 1;
		  break;
	  // select program
	  case 1:
			NewFrameMenu();
			break;
	  // select input value
	  case 2:
			ParameterMenu(robot.currentProg);
			break;
	 // suspend task
	  case 3:
		  osThreadResume(defaultTaskHandle);
		  osThreadSuspend(DisplayHandle);
		  taskYIELD();
		  break;
	  // draw progress window
	  case 4:
			ScreenExecution();
			robot.globalState = 5;
			break;
	 // draw real time progress
	  case 5:
		  robot.demo.draw();
		  break;
	  }

	  SSD1306_UpdateScreen();
	  osDelay(200 / portTICK_RATE_MS);
  }
  /* USER CODE END DisplayTask */
}

/* USER CODE BEGIN Header_Program1Task */
/**
* @brief Function implementing the demo1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Program1Task */
void Program1Task(void *argument)
{
  /* USER CODE BEGIN Program1Task */
	osTimerStart(SpeedPIDHandle, (10 / portTICK_RATE_MS));

	robot.demo.constructor();
  /* Infinite loop */
  for(;;)
  {
		if(robot.isStart){
			robot.demo.runner();
		}
		else
		{
			robot.globalState = 1;
			osThreadSuspend(DisplayHandle);
			osTimerStop(SpeedPIDHandle);
			robot.demo.destructor();
			osThreadResume(defaultTaskHandle);
			break;
		}
		InformationForProgram1();
		osDelay(25 / portTICK_RATE_MS);
  }
  /* USER CODE END Program1Task */
  vTaskDelete(NULL);
}

/* USER CODE BEGIN Header_Program2Task */
/**
* @brief Function implementing the demo2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Program2Task */
void Program2Task(void *argument)
{
  /* USER CODE BEGIN Program2Task */
  /* Infinite loop */
  for(;;)
  {
	  //				InformationForProgram2();
    osDelay(1);
  }
  /* USER CODE END Program2Task */
}

/* SpeedPID_Callback function */
void SpeedPID_Callback(void *argument)
{
  /* USER CODE BEGIN SpeedPID_Callback */
	Enc[0] = TIM2->CNT;
	Enc[1] = TIM3->CNT;

	wheel_angle[0] = Enc[0] * disk_to_real; // angle distanse
	wheel_v[0] = wheel_angle[0] / 0.01;

	wheel_angle[1] = Enc[1] * disk_to_real; // angle distanse
	wheel_v[1] = wheel_angle[1] / 0.01;

	PID_regulator[0].current = -wheel_v[0];
	PID_regulator[1].current = wheel_v[1];
  /* USER CODE END SpeedPID_Callback */
}

/* LinePID_Callback function */
void LinePID_Callback(void *argument)
{
  /* USER CODE BEGIN LinePID_Callback */

  /* USER CODE END LinePID_Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

