#include "Programs.h"

typedef struct{
	void (*constructor)(void);
	void (*destructor)(void);
	void (*runner)(void);
}Program;


typedef struct{
	uint32_t globalTime;
	uint8_t currentProg;
	float speed;
	float distane;
	Program demo;
}EduBot;



