#ifndef __RUN_H_
#define __RUN_H_
#include "key.h"

typedef struct{

    
    uint8_t gBle_Mode;
    uint8_t gBleItem;
    uint8_t gRunOrder;
    uint8_t gPowerOn;
    uint8_t gLampWhite_32;
    uint8_t gLampWhite_8;
    uint8_t gTurnOffLamp;
    uint8_t gID_flag;
    uint8_t gADJ_brightness;
    uint8_t gFAN_flag;
    uint8_t gTim0_30s;
    uint8_t gTimer_flag;
    uint8_t eusartTx_flag;
    uint8_t eusartTx_Num;
    uint8_t bleOpenBaud;
    uint8_t bleSetBaud;
    uint8_t bleSetName;
    uint8_t bleLinked;
    uint8_t gKeyItem;  //key input whiche item name laser or lamp
    uint8_t eusartTx_Baud_flag;
    uint8_t eusartTx_Baud_n;
    uint8_t gReadEEPROM_flag;
    uint8_t gEEPROM_start;
    uint8_t gFAN_timers;
    uint8_t gFAN_numbers;
    uint8_t gAddbrightness_mid;
    uint8_t gSubbrightness_mid;
    
    uint16_t gColorPwm;
 
}RUNREF_T;
RUNREF_T run_t;

typedef enum motorstep{noRun,CCW,CW,slow,middle,fast};

 void CheckMode(uint8_t keyValue);
 void CheckRun(void);

void RunMain(void);

#endif 