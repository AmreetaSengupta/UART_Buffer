/***********************************************************************************
* @ledtoggle.c
* @This code implements function for LED toggle.
* @Tools used : GCC & GNU make
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "ledtoggle.h"
extern int led_flag;

void led_init()
{
	SIM->SCGC5 |= 0x400;
	PORTB->PCR[19] = 0x100;
	GPIOB->PDDR |=0x80000;
}

void led_toggle()
{
	if(led_flag == 0)
	GPIOB->PSOR |= 0x80000;
	else
	GPIOB->PCOR |= 0x80000;
}


