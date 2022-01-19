#ifndef __KEY_H_
#define __KEY_H_
#include"../mcc_generated_files/mcc.h"


#define KEY_POWER_RB5_GetValue()           PORTBbits.RB5
typedef struct {
  
   
    uint8_t gPowerOn;
    
    
}KEY_T;
extern  KEY_T key_t;
uint8_t KEY_Scan(void);

void LED1_TurnOn(void);
void LED1_TurnOff(void);
void LED2_TurnOn(void);
void LED2_TurnOff(void);

#endif 