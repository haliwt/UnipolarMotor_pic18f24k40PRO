#ifndef __LAMP_H_
#define __LAMP_H_
#include "key.h"

#define LASER_RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LASER_RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)

void ColorWhite_32_ON(void);
void ColorWhite_32_OFF(void);
void ColorWhite_8_ON(void);
void ColorWhite_8_OFF(void);
void Laser_ON(void);
void Laser_OFF(void);

void LED6_Power_ON(void);
void LED6_Power_OFF(void);




void ALL_LED_OFF(void);
void TurnOff_ALL_Lamp(void);


void WhichOneColorLamp_ON(uint8_t colorlamp);
void WhichOneLed_ON(uint8_t onelamp);

void TurnOff_ALL_Lamp(void);




#endif 