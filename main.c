/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F24K40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "hardware/key.h"
#include "hardware/run.h"
#include "hardware/bluetooth.h"
#include "hardware/lamp.h"
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