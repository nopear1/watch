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

typedef struct LED
{
		uint8_t leftLine;
		uint8_t rightLine;
		uint8_t carGreen;
		uint8_t carRed;
		uint8_t carYellow;
		uint8_t peopleGreen;
		uint8_t peopleRed;
		uint8_t peopleYellow;
		uint8_t aebStateGreen;
		uint8_t aebStateRed;
		uint8_t fault;
		uint8_t point;
		uint8_t ledGreen;
		uint8_t ledRed;
		uint8_t numRight;
		uint8_t numLeft;
}LED_t;

typedef struct LED_USED
{
		uint8_t car;
		uint8_t people;
		uint8_t fault;
		uint8_t point;
		uint8_t ledGreen;
		uint8_t ledRed;
		uint8_t numRight;
		uint8_t numLeft;
}LedUsed_t;

extern LedUsed_t ledUsed;
extern LED_t led;
extern BlinkFlag_t blinkflag;
extern uint8_t numTab[];

#define LED_ROADLINE  (0x3F)
#define LED_NONE   (0)
#define LED_PEOPLE (0X0F)
#define LED_CAR (0XF0)
#define LED_AEB_GREEN (0X40)
#define LED_AEB_RED (0X01)
#define LED_FAULT (0X02)
#define LED_POINT   (0X80)



#define LED_COM1 PBout(0)
#define LED_COM2 PBout(1)
#define LED_COM3 PBout(3)
#define LED_COM4 PBout(4)
#define LED_COM5 PBout(5)
#define LED_COM6 PBout(6)
#define LED_COM7 PBout(7)
#define LED_COM8 PBout(8)


#define LED_COL9 PBout(9)
#define LED_COL10 PBout(10)
#define LED_COL11 PBout(11)
#define LED_COL12 PBout(12)
#define LED_COL13 PBout(13)
#define LED_COL14 PBout(14)
#define LED_COL15 PBout(15)
#define LED_COL16 PAout(15)


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
