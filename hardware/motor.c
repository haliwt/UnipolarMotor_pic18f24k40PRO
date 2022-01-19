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
void Unipolar_Motor_Run(void)
{
    static uint8_t motorfast =0xff,motormiddle=0xff,motorslow=0xff;
    // if(run_t.gPowerOn ==1)
    //     MOTOR_EN_RA0_SetLow();//MOTOR_EN_RA0_SetHigh(); //stop motor step 
    // else{
    //     MOTOR_EN_RA0_SetHigh(); //Motor stop
    // }
    
  
    if(motor_t.motor_Dir==CW){ //CW
        //PWM3_LoadDutyValue(61);//499//CCP1_SetCompareCount(32767);//PWM1_LoadDutyValue(485);    
         MOTOR_EN_RA0_SetLow();
         UniploarMotor_DIR_CW();//UniploarMotor_DIR_CCW();
        switch(motor_t.motorRunOrder){
              case fast:
                if(run_t.gTimer2_fast_flag==0){
                    TMR2_StartTimer();
                    PWM3_LoadDutyValue(499);
                    UniploarMotor_Phase_One();
                }
              
             break;
             
             case middle:
               
                    TMR2_StartTimer();
                  
                   PWM3_LoadDutyValue(0);
                    __delay_us(32);
                   PWM3_LoadDutyValue(1);
                   UniploarMotor_Phase_One();
               
                
             break;
             
             case slow:
                 TMR2_StartTimer();
                 
                
                   PWM3_LoadDutyValue(499);
                  UniploarMotor_Phase_Half();
             break;
             
            case 0xff:
                
                run_t.gPowerOn=0;
                run_t.gBleItem=0;
                TMR2_StopTimer();
                TMR0_StopTimer();
                Unipolar_MotorStop();
                
                break;
             
            
             
             default:
             
             break;
             
        }
        
    } //
    if(motor_t.motor_Dir==CCW){//CCW
         MOTOR_EN_RA0_SetLow();
        UniploarMotor_DIR_CCW();//UniploarMotor_DIR_CW();
        switch(motor_t.motorRunOrder){
            
             case fast:
                 TMR2_StartTimer();
                 
                 PWM3_LoadDutyValue(499);
                 UniploarMotor_Phase_One();
             break;
             
             case middle:
                 TMR2_StartTimer();
                
                    PWM3_LoadDutyValue(0);
                     __delay_us(32);
                    PWM3_LoadDutyValue(1);
                   UniploarMotor_Phase_One();
             break;
             
             case slow:
                 TMR2_StartTimer();
                 PWM3_LoadDutyValue(499);
                 UniploarMotor_Phase_Half();
             break;
             
              case 0xff:
                
                run_t.gPowerOn=0;
                run_t.gBleItem=0;
                TMR2_StopTimer();
                TMR0_StopTimer();
                Unipolar_MotorStop();
                
                break;
             
             default:
               
             break;
        }
     }
    
      Timer_Function();  
}

void Unipolar_MotorStop(void)
{
    MOTOR_EN_RA0_SetHigh(); //stop motor step
    HALF_PHASE_RC1_SetHigh();
    ONE_PHASE_RC2_SetHigh();
}
/************************************************************
 * 
 * Timer2 interrupter function by callback 
 * 
 ***********************************************************/
void OneCycle_Times(void)
{
    if(run_t.gMotorState_flag == 1){
         run_t.gStepNumbers ++;
    }
    if(run_t.gMotorState_flag == 2){
         run_t.gStepNumbers ++;
    }
    if(run_t.gMotorState_flag == 0xA1){ //fast
         run_t.gStepNumbers ++;
    }
    if(run_t.gMotorState_flag == 0xA2){ //middle
         run_t.gStepNumbers ++;
    }
     if(run_t.gMotorState_flag == 0xA3){ //slow
         run_t.gStepNumbers ++;
    }
    

}

void Timer0_Count(void)
{
    if(motor_t.motorTimer0_rec==1){
        motor_t.motorTimer0_numbers++;
    }

}