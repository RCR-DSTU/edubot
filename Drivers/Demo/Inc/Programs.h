#pragma once

#include "Regulator.h"


typedef struct{
	void (*constructor)(void);
	void (*destructor)(void);
	void (*runner)(void);
	void (*draw)(void);
}Program;

typedef struct{
	uint8_t globalState;
	bool isStart;
	uint32_t globalTime;
	uint8_t currentProg;
	uint8_t currentPage;
	uint8_t currentCycle;
	uint8_t number_clicks_button5;
	float input_arg;
	float speed;
	float distanse;
	float progress;
	uint16_t ADC_Values[5];
	float dist[2];
	Program demo;
}EduBot;

extern Program demo;
extern EduBot robot;

void Robot_Init(void);

void ConstrctionProgram(void);

void DestrctionProgram(void);

void RunnerProgram1(void);

void InformationForProgram1(void);

void RunnerProgram2(void);

void InformationForProgram2(void);

void DrawProgram1(void);

void DrawProgram2(void);
