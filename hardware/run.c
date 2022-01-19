#include "run.h"
#include "key.h"
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
             run_t.gBleItem=0;
             TMR2_StopTimer();
            
             Unipolar_MotorStop();
          
              LED1_TurnOff();
              LED2_TurnOff();
            TMR0_StopTimer();
            motor_t.motorRunOrder=0xff;
             break;
             
        case CCW:
            LED2_TurnOff();
            LED1_TurnOn();
            TMR2_StartTimer();
            run_t.gMotorState_flag =1; //anticlockwise 
            motor_t.motor_Dir =CCW;//
            motor_t. motorRunOrder = middle;
            EUSART_BleResponseEvent(0);
          
            motor_t.motorTimer0_numbers=0;
            TMR0_StartTimer();
            motor_t.motorTimer0_rec=1;
           
        break;
            
             
        case CW:
            LED2_TurnOn();
            LED1_TurnOff();
           // run_t.gMotorState_flag =2; //clockwise
            motor_t.motorTimer0_numbers=0;
            TMR0_StartTimer();
            TMR2_StartTimer();
            motor_t.motorTimer0_rec=1;
            motor_t. motorRunOrder = middle;
            motor_t.motor_Dir =CW;
            
            EUSART_BleResponseEvent(0);
     
          
           
          break;
        
         case slow:
              LED1_TurnOn();
              LED2_TurnOn();
             run_t.gMotorState_flag =0xA3;
              motor_t. motorRunOrder = slow;//Unipolar_Motor_Run(motor_t.motor_Dir,3);
             EUSART_BleResponseEvent(0);  
             run_t.gStepNumbers =0;
              
             break;
         case middle:
              LED1_TurnOff();
              LED2_TurnOff();
             run_t.gMotorState_flag =0xA2;
              motor_t. motorRunOrder = middle;//Unipolar_Motor_Run(motor_t.motor_Dir,2);
             EUSART_BleResponseEvent(0);
             run_t.gStepNumbers =0;
         
             break;
             
         case fast:
              LED1_TurnOn();
              LED2_TurnOn();
              TMR0_StartTimer();
             run_t.gMotorState_flag =0xA1;
              motor_t. motorRunOrder = fast;//Unipolar_Motor_Run(motor_t.motor_Dir,1) ;
             run_t.gStepNumbers =0;
             EUSART_BleResponseEvent(0);
         
        
             break;
             
        
       
          default:
         
            break;
             
             
             
     
     }
 }
  /***************************************************************************
	*
	*Function Name: void RunMain(void)
	*Function: Run order
	*Input Ref:NO
	*Return Ref:NO
	*
****************************************************************************/ 
 void MotorRun(void)
 {
 
   Unipolar_Motor_Run();
 }
 /***************************************************************************
	*
	*Function Name: void RunMain(void)
	*Function: Run order
	*Input Ref:NO
	*Return Ref:NO
	*
****************************************************************************/ 
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
          MotorRun();
          Timer_Function();  
        }
    
    
    
}
 
 void Timer_Function(void)
 {
      if(motor_t.motorTimer0_numbers>=6570){ //6570
      //  motor_t.motorRunOrder=0xff;
        run_t.gRunOrder=noRun;
        motor_t.motorStopStep_flag =1;
        LED1_TurnOff();
        LED2_TurnOff();
        }
        if(run_t.gStepNumbers>=4096){
                 LED1_TurnOff();
                     LED2_TurnOff();
                   run_t.gTimer2_fast_flag=1;
                   run_t.gRunOrder=noRun;
                 //  motor_t.motorRunOrder=0xff;
                   run_t.gMotorState_flag =0;
         }
 
 
 }