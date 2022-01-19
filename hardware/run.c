#include "run.h"
#include "key.h"
#include "lamp.h"
#include"../hardware/bluetooth.h"
#include "motor.h"

#define NORMAL_LEVEL_DEFAULT	10
#define NORMAL_LEVEL_MAX		20
#define NORMAL_LEVEL_MIN		10
#define NORMAL_LEVEL_STEP		2
#define NORMAL_LEVEL_PWM_STEP	8
#define NORMAL_LEVEL_PWM_MAX	156//155//151//159//127 //80%

#define PWM_WHITE_32_MAX       156//155//151//159//127 //


static uint16_t level_32;
static uint16_t level_8;


static void setColorWhite_32(uint16_t val);	// green brightness'
static void setColorWhite_8(uint16_t val);
static void FAN_ON(void);
/***************************************************************************
	*
	*Function Name:void CheckMode(uint8_t value)
	*Function: The first input LED ON,the second input key LED OFF
	*Input Ref:key be pressed of value
	*Return Ref:NO
	*
****************************************************************************/
 void CheckMode(uint8_t keyValue)
 {
 
    static uint8_t  inputKey_power;

	switch(keyValue){
       case 0:

	     if(!keyValue)
		  	return ;
		break;

	   case 0x1: //power On
	  
	       
           inputKey_power = inputKey_power ^ 0x01;
            run_t.gBleItem=0;
            run_t.gBle_Mode=0;
	        if(inputKey_power ==1){
	            run_t.gPowerOn =1;
	            run_t.gRunOrder=1;
	         
                
	        }
	        else{
	             
	           run_t.gPowerOn =0;
               run_t.gRunOrder= noRun;
               run_t.gTurnOffLamp=0;
               run_t.gKeyItem = 0;
               
	       }
            
			    
	  break;

	
   
	   default:
   
   		break;
 
    }
 }
 /***************************************************************************
	*
	*Function Name:void CheckRun(void)
	*Function: Run order
	*Input Ref:NO
	*Return Ref:NO
	*
****************************************************************************/  
 void CheckRun(void)
 {
     switch(run_t.gRunOrder){
        case noRun:
             run_t.gPowerOn=0;
             run_t.gKeyItem = 0;
             run_t.gBleItem=0;
           
             Unipolar_MotorStop();
             break;
             
        case CCW:
            LED2_TurnOff();
            motor_t.motor_Dir =CCW;//
            Unipolar_Motor_Run(motor_t.motor_Dir,2);
            EUSART_BleResponseEvent(0);
        break;
            
             
        case CW:
             LED2_TurnOn();
             LED1_TurnOn();
            motor_t.motor_Dir =CW;
            Unipolar_Motor_Run(motor_t.motor_Dir,2);
            EUSART_BleResponseEvent(0);
         
        
        break;
        
         case slow:
             
             Unipolar_Motor_Run(motor_t.motor_Dir,3);
             EUSART_BleResponseEvent(0);  
             break;
         case middle:
         
             Unipolar_Motor_Run(motor_t.motor_Dir,2);
             EUSART_BleResponseEvent(0);
             break;
             
         case fast:
             Unipolar_Motor_Run(motor_t.motor_Dir,1) ;
             EUSART_BleResponseEvent(0);
             break;
             
        
       
          default:
         
            break;
             
             
             
     
     }
 }
 
 /**************************************************************
	*
	*Function Name:static void ADJ_LampBrightnessADD(void)
	*Function: 
	*Input Ref:NO
	*Return Ref:NO
	*
**************************************************************/
void ADJ_LampBrightnessADD(void)
{
    static uint8_t adjadd=0xff,adjsub=0xff;
	  switch( run_t.gADJ_brightness ){

	     case 0x01://Color -white 32 
                 run_t.gFAN_flag =0;
            
             ColorWhite_8_OFF();
             
             if(adjadd !=run_t.gAddbrightness_mid ){
                 adjadd = run_t.gAddbrightness_mid;
                 run_t.gColorPwm=143;//111;//79; //50
                 PWM3_LoadDutyValue(run_t.gColorPwm);
                 ColorWhite_32_ON();
                 DELAY_microseconds(500);
             }
             else
             {
                level_32+=NORMAL_LEVEL_STEP; //10
                if(level_32>NORMAL_LEVEL_MAX) level_32=NORMAL_LEVEL_MAX; //20
                setColorWhite_32(level_32);	// green brightness
                ColorWhite_32_ON();
              }
             
           // IO_POWER_RB7_SetLow() ;
             run_t.gSubbrightness_mid++;
            run_t.gFAN_timers=0;
             run_t.gFAN_flag=1;
             
	     break;

		 case 0x02: //Color white 8
              run_t.gFAN_flag =0;
		 	  ColorWhite_32_OFF();
           //   IO_POWER_RB7_SetHigh();
          
            if(adjsub !=run_t.gSubbrightness_mid ){
                 adjsub = run_t.gSubbrightness_mid;
                 run_t.gColorPwm=143;//111;//79; //50
                 PWM3_LoadDutyValue(run_t.gColorPwm);
                 ColorWhite_8_ON();
                 DELAY_microseconds(500);
                
             }
            else{
              level_8+=NORMAL_LEVEL_STEP; //2
              if(level_8>NORMAL_LEVEL_MAX) level_8=NORMAL_LEVEL_MAX; //20
              setColorWhite_32(level_8);	// green brightness
              ColorWhite_8_ON();
            }
             run_t.gAddbrightness_mid++;
             run_t.gFAN_flag=1;
              run_t.gFAN_timers=0; //Fan timer start
         
		 break;

	}


}

void ADJ_LampBrightnessSUB(void)
{
     switch(run_t.gADJ_brightness ){

	     case 0x01://Color -white 32 
           run_t.gFAN_flag =0;
             ColorWhite_8_OFF();
             if(level_32<NORMAL_LEVEL_MIN+NORMAL_LEVEL_STEP)	level_32=NORMAL_LEVEL_MIN;//10
			 else 	level_32-=NORMAL_LEVEL_STEP;
           
             setColorWhite_32(level_32);	// green brightness
             ColorWhite_32_ON();
              run_t.gAddbrightness_mid++;
             run_t.gSubbrightness_mid++;
              run_t.gFAN_timers=0; //Fan timer start
                 run_t.gFAN_flag=1;
           break;
           
         case 0x02:
             run_t.gFAN_flag =0;
              ColorWhite_32_OFF();
             if(level_8<NORMAL_LEVEL_MIN+NORMAL_LEVEL_STEP)	level_8=NORMAL_LEVEL_MIN;//10
			 else 	level_8-=NORMAL_LEVEL_STEP;
           
             setColorWhite_8(level_8);	// green brightness
             ColorWhite_8_ON();
             run_t.gAddbrightness_mid++;
             run_t.gSubbrightness_mid++;
             
             run_t.gFAN_timers=0; //Fan timer start
  
              run_t.gFAN_flag=1;
             break;

     }
}

static void setColorWhite_32(uint16_t val)	// green brightness
{
	uint16_t pwmValue;

	if(val>NORMAL_LEVEL_MAX) val=NORMAL_LEVEL_MAX;//20
	pwmValue=(val)*NORMAL_LEVEL_PWM_STEP; //20*7=160

	if(pwmValue>PWM_WHITE_32_MAX) pwmValue=PWM_WHITE_32_MAX;
	PWM3_LoadDutyValue(pwmValue);
}
static void setColorWhite_8(uint16_t val)	// green brightness
{
	uint16_t pwmValue;

	if(val>NORMAL_LEVEL_MAX) val=NORMAL_LEVEL_MAX;
	pwmValue=(val)*NORMAL_LEVEL_PWM_STEP; //20*8=160

	if(pwmValue>NORMAL_LEVEL_PWM_MAX) pwmValue=NORMAL_LEVEL_PWM_MAX;
	PWM3_LoadDutyValue(pwmValue);
}





void RunMain(void)
{
    uint8_t  KeyValue;  
    if( run_t.eusartTx_flag==4||run_t.gEEPROM_start==1){
           // run_t.bleLinked = BlueTooth_CheckLink();
           BLE_MODE_RA7_SetHigh();// BLE_MODE_RC2_SetHigh();
            
          KeyValue = KEY_Scan();
          EUSART_SetRxInterruptHandler(EUSART_RxDataHandler);
          if(KeyValue !=0){
            CheckMode(KeyValue);
          }
          else if(run_t.gBle_Mode==1){
             Bluetooth_RunCmd();
             run_t.gBle_Mode=0;
             ble_t.ble_responseTimes++;
          } 
          CheckRun();
         // FAN_Run();
              
        }
    
    
    
}