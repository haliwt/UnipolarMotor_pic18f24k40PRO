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
    
}UNIPOLAR_T;

UNIPOLAR_T motor_t;

void Unipolar_Motor_Initialize(void);

void Unipolar_Motor_Run(uint8_t dir,uint8_t stepvalue);

void Unipolar_MotorStop(void);


#endif 