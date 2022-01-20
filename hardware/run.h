#ifndef __RUN_H_
#define __RUN_H_
#include "key.h"

typedef struct{

    
    uint8_t gBle_Mode;
    uint8_t gBleItem;
    uint8_t gRunOrder;
    uint8_t gPowerOn;
    
    uint8_t gTimer2_fast_flag;
    uint8_t eusartTx_flag;
    uint8_t eusartTx_Num;
    uint8_t bleOpenBaud;
    uint8_t bleSetBaud;
    uint8_t bleSetName;
    uint8_t bleLinked;
  
    uint8_t eusartTx_Baud_flag;
    uint8_t eusartTx_Baud_n;
    uint8_t gReadEEPROM_flag;
    uint8_t gEEPROM_start;
    
    uint8_t gfastNumbers;
    uint8_t gmiddleNumbers;
    uint8_t gslowNumbers;
    
    uint8_t gMotorState_flag;
    
    uint16_t gStepNumbers;
    
 
}RUNREF_T;
RUNREF_T run_t;

typedef enum motorstep{noRun,CCW,CW,slow,middle,fast};

 void CheckMode(uint8_t keyValue);
 void CheckRun(void);

void RunMain(void);
void MotorRun(void);
void Timer_Function(void);
#endif 