

#include "pin_manager.h"


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x00;
    TRISB = 0x6F; //0B 0101 1111 
    TRISC = 0xA0; //0B 1010 0000

    /**
    ANSELx registers
    */
    ANSELC = 0x56; //0B 0101 0110  
    ANSELB = 0x40;//0B 0100 0000
    ANSELA = 0x73;//0B 0111 0011

    /**
    WPUx registers
    */
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;

    /**
    INLVLx registers input level RES
    */
    INLVLA = 0xFF; //0B 1111 1111 -> ST
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLE = 0x08;

   // RC0PPS = 0x08;   //RC0->PWM4:PWM4; //RxxPPS :output register   
    RXPPS = 0x17;   //RC7->EUSART:RX;    
   // INT0PPS = 0x08;   //RB0->EXT_INT:INT0;    
    RC0PPS = 0x07;   //RC0->PWM3:PWM3;    
    RC6PPS = 0x09;   //RC6->EUSART:TX;    
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/