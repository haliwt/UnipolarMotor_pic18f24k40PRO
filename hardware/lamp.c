#include "lamp.h"
/***************************************************************
 * *
 *Function Name: void ColorWhite_32_ON(void)
 *Function: On LAMP white 32 pcs
 *Input Ref: NO
 *Return Ref: NO
 *
***************************************************************/
void ColorWhite_32_ON(void)
{
  
}
void ColorWhite_32_OFF(void)
{
   
}
void ColorWhite_8_ON(void)
{
    
}
void ColorWhite_8_OFF(void)
{
    
}


void WhichOneColorLamp_ON(uint8_t colorlamp)
{
    switch(colorlamp){
        
        case 1:
            
        break;
        
        case 2:
          
        break;
        
        default:
        break;
    }
    
    
    
}
/***************************************************************
 * *
 *Function Name:TurnOff_ALL_Lamp(void)
 *Function: 
 *Input Ref:NO
 *Return Ref:NO
 * 
***************************************************************/
void TurnOff_ALL_Lamp(void)
{
    ColorWhite_32_OFF();
    ColorWhite_8_OFF();
    Laser_OFF();

}
/***************************************************************
 * *
 *Function Name: void LED_1_ON(void)
 *Function: On LED ONE 
 *Input Ref: NO
 *Return Ref: NO
 *






/***************************************************************
 * *
 *Function Name: void LED_1_ON(void)
 *Function: On LED ONE 
 *Input Ref: NO
 *Return Ref: NO
 *
***************************************************************/
void ALL_LED_OFF(void)
{
    LED1_RA0_SetLow(); 
    LED2_RA1_SetLow() ;
  
}
/***************************************************************
 * *
 *Function Name: void WhichOneLamp(uint8_t onelamp)
 *Function: be selected lamp is ON
 *Input Ref: define lamp is ON
 *Return Ref: NO
 *
***************************************************************/
void WhichOneLed_ON(uint8_t onelamp)
{
    switch(onelamp){
        
        
        case 0:
            LED1_RA0_SetLow(); //On
            LED2_RA1_SetLow() ;
         
           
        
        break;
        
        case 1:
           
            LED1_RA0_SetHigh(); //On
            
            LED2_RA1_SetLow() ;
         
           
        
        break;
        
        case 2:
            
             LED2_RA1_SetHigh() ;//On
        
            LED1_RA0_SetLow(); 
           
        
          
        
        break;
        
        case 3:
           
            
            LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
            
            
          
            
        
        
        break;
        
        case 4:
         
        
             LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
         
           
        
        break;
        
        case 5:
             LED5_RA4_SetHigh() ;//ON
        
             LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
         
           
            
        
        break;
        
     
        
        default:
        
        break;
        
        
        
    }
    
    
}