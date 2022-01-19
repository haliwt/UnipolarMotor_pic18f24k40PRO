#include "key.h"
#include "run.h"
KEY_T key_t;


uint8_t   KEY_Scan(void)
{
    static uint16_t  k1=0 ;

    uint8_t cnt;

   if(KEY_POWER_RB5_GetValue()==0){
        if(k1<181)
        k1++;   
    }
    else {  
      k1=0;  
    }

   if(k1==180){
       cnt= 0x1  ;  //power key
      // k1=0; //BUG
       return cnt ;
    }

   
    return 0 ;
    
}


void LED1_TurnOn(void)
{
    LED1_RA2_SetHigh();
    
}

void LED2_TurnOn(void)
{
    LED2_RA3_SetHigh();
    
}

void LED1_TurnOff(void)
{
    LED1_RA2_SetLow();
    
}

void LED2_TurnOff(void)
{
    LED2_RA3_SetLow();
    
}
