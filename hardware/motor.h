#ifndef __MOTOR_H
#define __MOTOR_H
#include"../mcc_generated_files/mcc.h"


typedef struct _UNIPOLAR{
     
     uint8_t motor_fast;
     uint8_t motor_middle;
     uint8_t motor_slow;
     uint8_t motor_fast_flag;
     uint8_t motor_middle_flag;
     uint8_t motor_Dir;
     uint8_t motorRunOrder;
     uint8_t motorTimer0_rec;
     uint8_t motorStopStep_flag;
     uint16_t motorTimer0_numbers;
    
}UNIPOLAR_T;

UNIPOLAR_T motor_t;

void Unipolar_Motor_Initialize(void);

void Unipolar_Motor_Run(void);

void Unipolar_MotorStop(void);

void OneCycle_Times(void);
void Timer0_Count(void);

void UniploarMotor_DIR_CCW(void);
void UniploarMotor_DIR_CW(void);

#endif 