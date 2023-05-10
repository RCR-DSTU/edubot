#pragma once
#include "stdbool.h"
#include "ssd1306.h"
#include <stdio.h>

extern const uint8_t indicator_X;
extern uint8_t indicator_Y;

extern uint8_t number_program;

extern uint8_t number_clicks_button5;

extern int parameter_value;


void FirstScreen();

void MenuRectangle();

void ShowMenuItems();

void NewFrameMenu();

void Indicator(bool IsUp);

void ParameterMenu(uint8_t value);

void SelectParameter(bool IsUp);

void ScreenExecution(uint8_t value);

void ProgressBar(float progress);



