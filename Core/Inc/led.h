#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


typedef struct blinkflag
{
		uint8_t leftLine:2;
		uint8_t rightLine:2;
		uint8_t car:3;
		uint8_t r1:1;
		uint8_t people:3;
		uint8_t aebState:3;
		uint8_t fault:2;
		uint8_t digitalState:2;
		uint8_t point:2;
		uint8_t ledGreen:2;
		uint8_t ledRed:2;
		uint8_t numRight:4;
		uint8_t numLeft:4;
		uint8_t voice;
		uint8_t r2[3];
}BlinkFlag_t;

extern BlinkFlag_t blinkflag;
#define LED_COM1 PBout(0)
#define LED_COM2 PBout(1)
#define LED_COM3 PBout(3)
#define LED_COM4 PBout(4)
#define LED_COM5 PBout(5)
#define LED_COM6 PBout(6)
#define LED_COM7 PBout(7)
#define LED_COM8 PBout(8)


#define LED_COL9 PBout(9)
#define LED_COL10 PBout(10)// PB1
#define LED_COL11 PBout(11)// PB1
#define LED_COL12 PBout(12)// PB1
#define LED_COL13 PBout(13)// PB1
#define LED_COL14 PBout(14)// PB1
#define LED_COL15 PBout(15)// PB1
#define LED_COL16 PAout(15)// PB1


void  LedDisplay(uint8_t row,uint8_t code);
void LedLoop(void);
void SetLeftLine(uint8_t state);
void SetRightLine(uint8_t state);
void SetCar(uint8_t state);
void SetPeople(uint8_t state);
void SetAeb(uint8_t state);
void SetFault(uint8_t state);
void SetDigitalNumLeft(uint8_t state);
void SetDigitalNumRight(uint8_t state);
void SetPoint(uint8_t state);
		 				    
#endif
