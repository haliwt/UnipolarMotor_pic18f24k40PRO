
#include "mcc_generated_files/mcc.h"
#include "hardware/key.h"
#include "hardware/run.h"
#include "hardware/bluetooth.h"
#include "hardware/motor.h"


/*
                         Main application
 */
void main(void)
{
    
      static uint8_t n,m,i;
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:
      BlueTooth_Init();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
   
    while (1)

    {
#if 0
                   MOTOR_EN_RA0_SetLow();
                 
                     LED1_TurnOn();
                    TMR2_StartTimer();
                    TMR2_Period8BitSet(0x30);//TMR2_Initialize_Period_10ms();//middle
                    PWM3_LoadDutyValue(100);
                   
                    ONE_PHASE_RC2_SetLow();
                     HALF_PHASE_RC1_SetHigh();
    }
#endif 
#if 0  
        MOTOR_EN_RA0_SetLow();
           if(KEY_Scan()==0x1){
                    MOTOR_EN_RA0_SetLow();
                    i++;
                    if(i>4)i=1;
           }
        while(i==1){
                    
                        LED1_TurnOn();
                    TMR2_StartTimer();
                    TMR2_Period8BitSet(0x30);//TMR2_Initialize_Period_10ms();//middle
                   
                    
                    PWM3_LoadDutyValue(100);
                     ONE_PHASE_RC2_SetLow();
                      HALF_PHASE_RC1_SetHigh();
                 
                    
                    }
             while(i==2){
                        LED2_TurnOn();
                         TMR2_Period8BitSet(0x3A);//TMR2_Initialize_Period_10ms();//middle
                   
                    
                    PWM3_LoadDutyValue(100);
                     ONE_PHASE_RC2_SetLow();
                      HALF_PHASE_RC1_SetHigh();
             
                    
                    }
                   while(i==3){
                       LED1_TurnOn();
                       LED2_TurnOn();
                       TMR2_Period8BitSet(0x32);//TMR2_Initialize_Period_10ms();//middle
                   
                    
                    PWM3_LoadDutyValue(100);
                     ONE_PHASE_RC2_SetLow();
                      HALF_PHASE_RC1_SetHigh();
                 
             }
                   
           
         }
#endif   
#if 1 
        // BLUETOOTH_MainRun();
     // Unipolar_Motor_Run(1,2);
     if(run_t.gEEPROM_start==0){
           BLE_MODE_RA7_SetLow();//BLE_MODE_RC2_SetLow();
           run_t.gReadEEPROM_flag=DATAEE_ReadByte(0x10);
          if(run_t.gReadEEPROM_flag==0x0A){
              run_t.gEEPROM_start++;
              EUSART_Initialize_9600();
          }
         else{ 
                if(run_t.eusartTx_flag<2){
                    BLE_MODE_RA7_SetLow();//BLE_MODE_RC2_SetLow();
                    EUSART_BleCommandTxData_Name();
                    if(run_t.eusartTx_flag==1){
                        n++;
                        run_t.eusartTx_Num=0;
                        run_t.eusartTx_flag=0;
                        DELAY_milliseconds(200); 
                        if(n>10){
                            run_t.eusartTx_flag=3;
                        }
                    }
                }
                if(run_t.eusartTx_flag==3){
                   BLE_MODE_RA7_SetLow();// BLE_MODE_RC2_SetLow();
                    EUSART_BleCommandTxBaud(0x31);
                    if(run_t.eusartTx_Baud_flag==1){
                        m++;
                        EUSART_Initialize_9600();
                        run_t.eusartTx_Baud_n=0;
                        run_t.eusartTx_Baud_flag=0;
                        DELAY_milliseconds(200);
                        if(m>10){
                            run_t.eusartTx_flag=4;
                            DATAEE_WriteByte(0x10,0x0A);
                            run_t.gEEPROM_start++;
                            EUSART_Initialize_9600();
                        }
                    }
                }
           }
        }
         
      RunMain();
    
    }
#endif
}

/**
 End of File
*/