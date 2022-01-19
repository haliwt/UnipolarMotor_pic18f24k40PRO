#include "motor.h"
#include "run.h"


static void UniploarMotor_Phase_One(void);
static void UniploarMotor_Phase_Two(void);
static void UniploarMotor_Phase_Half(void);
static void UniploarMotor_Step_Stop(void);
static void UniploarMotor_DIR_CCW(void);
static void UniploarMotor_DIR_CW(void);
/*****************************************************
*
*Function Name:void Unipolar_Motor_Initialize(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*****************************************************/
void Unipolar_Motor_Initialize(void)
{
    MOTOR_EN_RA0_SetHigh(); //stop motor step
    HALF_PHASE_RC1_SetHigh();
    ONE_PHASE_RC2_SetHigh();

}
/*********************************************************
*
*Function Name:void UniploarMotor_Phase_One(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************************/
static void UniploarMotor_Phase_One(void)
{
    //PWM1_LoadDutyValue(499);
    ONE_PHASE_RC2_SetHigh();
    HALF_PHASE_RC1_SetLow();
    
}
/*********************************************************
*
*Function Name:void UniploarMotor_Phase_Two(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************************/
static void UniploarMotor_Phase_Two(void)
{
   // PWM1_LoadDutyValue(499);
    ONE_PHASE_RC2_SetLow();
    HALF_PHASE_RC1_SetLow();
    
}
/*********************************************************
*
*Function Name:void UniploarMotor_Phase_Half(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************************/
static void UniploarMotor_Phase_Half(void)
{
   // PWM1_LoadDutyValue(311);
    ONE_PHASE_RC2_SetLow();
    HALF_PHASE_RC1_SetHigh();
    
}
/*********************************************************
*
*Function Name:void UniploarMotor_Step_Stop(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************************/
static void UniploarMotor_Step_Stop(void)
{
    ONE_PHASE_RC2_SetHigh();
    HALF_PHASE_RC1_SetHigh();
    TMR2_StopTimer();
    
}
/*********************************************************
*
*Function Name:void UniploarMotor_DIR_CW(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************************/
static void UniploarMotor_DIR_CW(void)
{
      
    MOTOR_DIR_RA1_SetHigh();
    
}
/*********************************************************
*
*Function Name:void UniploarMotor_DIR_CCW(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************************/
static void UniploarMotor_DIR_CCW(void)
{
      
    MOTOR_DIR_RA1_SetLow();
    
}
/********************************************
*
*Function Name:Unipolar_Motor_Run(void)
*Function :MOTOR 35BYJ26
*Input Ref:
*Return Ref:
*
*********************************************/
void Unipolar_Motor_Run(uint8_t dir,uint8_t stepvalue)
{
    static uint8_t motorfast =0xff,motormiddle=0xff,motorslow=0xff;
    // if(run_t.gPowerOn ==1)
    //     MOTOR_EN_RA0_SetLow();//MOTOR_EN_RA0_SetHigh(); //stop motor step 
    // else{
    //     MOTOR_EN_RA0_SetHigh(); //Motor stop
    // }
      MOTOR_EN_RA0_SetLow();
    if(dir==CW){ //CW
        //PWM3_LoadDutyValue(61);//499//CCP1_SetCompareCount(32767);//PWM1_LoadDutyValue(485);    
         
         UniploarMotor_DIR_CW();//UniploarMotor_DIR_CCW();
        switch(stepvalue){
             
             case 0:
                  if(!stepvalue)
                    return ;
             break;
             
             
             
             case 1:
                
                if(motorfast != motor_t.motor_fast ){
                    motorfast = motor_t.motor_fast;
                    LED1_TurnOn();
                    LED2_TurnOff();
                    TMR2_StartTimer();
                   //  TMR2_Period8BitSet(0x3A);
                     PWM3_LoadDutyValue(100);
                    motor_t.motor_fast_flag=1;
                    motor_t.motor_slow++;
                    motor_t.motor_middle++;
                }
                 PWM3_LoadDutyValue(499);
                 UniploarMotor_Phase_One();
             break;
             
             case 2:
                 
                  if(motormiddle != motor_t.motor_middle){
                    motormiddle = motor_t.motor_middle;
                    LED1_TurnOff();
                    LED2_TurnOn();
                    TMR2_StartTimer();
                   // TMR2_Period8BitSet(0x32);
                    PWM3_LoadDutyValue(50);
                    motor_t.motor_middle_flag =1;
                    motor_t.motor_slow++;
                    motor_t.motor_fast++;
                  }
                   PWM3_LoadDutyValue(0);
                     __delay_us(32);
                    PWM3_LoadDutyValue(1);
                   UniploarMotor_Phase_One();
             break;
             
             case 3:
                 
                  if(motorslow != motor_t.motor_slow){
                    motorslow = motor_t.motor_slow;
                    TMR2_StartTimer();
                    // TMR2_Period8BitSet(0x30);//
                    PWM3_LoadDutyValue(100);
                    LED1_TurnOn();
                    LED2_TurnOn();
                    motor_t.motor_middle_flag =0;
                    motor_t.motor_fast_flag=0;
                    motor_t.motor_fast++;
                    motor_t.motor_middle++;
                  }
                
                   PWM3_LoadDutyValue(499);
                  UniploarMotor_Phase_Half();
             break;
             
             default:
             
             break;
             
        }
        
    } //
    if(dir==CCW){//CCW
      
        UniploarMotor_DIR_CCW();//UniploarMotor_DIR_CW();
        switch(stepvalue){
            
             case 1:
                  if(motorfast != motor_t.motor_fast ){
                    motorfast = motor_t.motor_fast;
                    TMR2_StartTimer();
                    // TMR2_Period8BitSet(0x3A);
                     PWM3_LoadDutyValue(499);
                    motor_t.motor_fast_flag=1;
                    motor_t.motor_slow++;
                     motor_t.motor_middle++;
                }
                   PWM3_LoadDutyValue(499);
                 UniploarMotor_Phase_One();
             break;
             
             case 2:
                  if(motormiddle != motor_t.motor_middle ){
                    motormiddle = motor_t.motor_middle;
                    TMR2_StartTimer();
                   // TMR2_Period8BitSet(0x32);//
                    PWM3_LoadDutyValue(999);
                    motor_t.motor_middle_flag =1;
                    motor_t.motor_slow++;
                     motor_t.motor_fast++;
                  }
                    PWM3_LoadDutyValue(0);
                     __delay_us(32);
                    PWM3_LoadDutyValue(1);
                   UniploarMotor_Phase_One();
             break;
             
             case 3:
                 
                   if(motorslow != motor_t.motor_slow){
                    motorslow = motor_t.motor_slow;
                    TMR2_StartTimer();
                   // TMR2_Period8BitSet(0x30);//
                    PWM3_LoadDutyValue(999);
                    motor_t.motor_middle_flag =0;
                    motor_t.motor_fast_flag=0;
                    motor_t.motor_middle++;
                     motor_t.motor_fast++;
                    
                  }
                 
                   PWM3_LoadDutyValue(499);
                  UniploarMotor_Phase_Half();
             break;
             
             default:
               
             break;
             
        }
        
    }
    
    
    
}

void Unipolar_MotorStop(void)
{
    MOTOR_EN_RA0_SetHigh(); //stop motor step
    HALF_PHASE_RC1_SetHigh();
    ONE_PHASE_RC2_SetHigh();
}