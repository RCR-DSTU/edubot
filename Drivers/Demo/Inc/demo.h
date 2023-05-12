#pragma once
#include "stdbool.h"
#include "ssd1306.h"
#include <stdio.h>
#include "Programs.h"


extern const uint8_t indicator_X;
extern uint8_t indicator_Y;

void FirstScreen();

void MenuRectangle();

void ShowMenuItems();

void NewFrameMenu();

void Indicator(bool IsUp);

void ParameterMenu(uint8_t value);

void SelectParameter(bool IsUp);

void ScreenExecution(uint8_t value);

void ProgressBar(float progress);



