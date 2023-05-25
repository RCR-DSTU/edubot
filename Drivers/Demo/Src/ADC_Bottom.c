#include "ADC_Bottom.h"


void ADC_Read(uint8_t channel)
{
	channel &= 0x7;

	if((channel & 0x4) != 0) HAL_GPIO_WritePin(GPIOB, MULPLXA_PIN_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOB, MULPLXA_PIN_Pin, GPIO_PIN_RESET);

	if((channel & 0x2) != 0) HAL_GPIO_WritePin(GPIOB, MULPLXB_PIN_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOB, MULPLXB_PIN_Pin, GPIO_PIN_RESET);

	if((channel & 0x1) != 0) HAL_GPIO_WritePin(GPIOB, MULPLXC_PIN_Pin, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(GPIOC, MULPLXC_PIN_Pin, GPIO_PIN_RESET);
}

