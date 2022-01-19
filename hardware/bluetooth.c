#include "../hardware/bluetooth.h"
#include "../hardware/run.h"
#include "../hardware/lamp.h"
#include"../mcc_generated_files/eusart.h"

#define TX_MAX_NUMBER    25
#define TX_RESPONSE_TEXT_NUMBER     10

volatile uint8_t i=0;
uint8_t outputBuf[TX_MAX_NUMBER];
uint8_t outputBaudBuf[9];
uint8_t outputResetBuf[8];
uint8_t outputBaudSetBuf[12];
static uint8_t bleBuf[9];
static uint8_t outputResponseText[TX_RESPONSE_TEXT_NUMBER];



void BlueTooth_Init(void)
{
   BLE_RST_RC4_SetHigh() ; //BLE is high
   BLE_MODE_RC2_SetLow();
   
}


void BlueTooth_SetupAT_Function(void)
{
     static uint8_t i,j,n,m,times;
	 static uint8_t seq=1;
	 
	 n= sizeof(BleAssignedName)/sizeof(BleAssignedName[0]);
	 m= sizeof(BleAssignedBaud)/sizeof(BleAssignedBaud[0]);

	 switch(seq){
		 
	 case 0:
	      
         return ;
         
	 break;
	
	 case 1 :
          BLE_MODE_RC2_SetLow();
         
          if(run_t.bleSetName==0){
			//for(i=0;i<n;i++){
              seq=1;
			EUSART_Write(BleAssignedName[i]);
             i++; 
            if(i==(n-1)){
                run_t.bleSetName=1;
              
            }
          }
          else{ 
              seq=2;
              DELAY_milliseconds(200);
          }
          
	     
		
		
	 break;
	 
	 case 2:
         BLE_MODE_RC2_SetLow();
		if(run_t.bleSetBaud==0){
            seq=2;
		   EUSART_Write(BleAssignedBaud[j]);
                j++;
				if(j==(m-1)){
                    run_t.bleSetBaud=1;
                    
				}
			}
        else{
            seq=3;
            DELAY_milliseconds(200);
        }
          
        
		
		
	 break;
	 
	 case 3:
         if(run_t.bleSetName==1 && run_t.bleSetBaud==1){
             times++;
              seq=1;
              i=0;
              j=0;
              run_t.bleSetName=0;
               run_t.bleSetBaud=0;
             if(times==30){
             seq =0;
             run_t.bleSetName=1;
              run_t.bleSetBaud=1;
             EUSART_Initialize_9600();
             BLE_MODE_RC2_SetHigh();
             }
         }
         else{
           seq =1;
         }
		
	  break;
     }
	 
}
/*****************************************************************************
 * 
 *Function Name: void BlueTooth_CheckLink(void)
 *Function: check blue tooth if link for phone
 *Input Ref:NO
 *Return Ref:NO
 * 
 *****************************************************************************/
uint8_t BlueTooth_CheckLink(void)
{
	if(BLE_LINK_RC5_GetValue() ==0){ //blue tooth has link
		
		return 1;
		
	}
	else{
		
		return 0; //blie don't link for phone
	}
	
	
}
/******************************************************************************
 * 
 *Function Name: EUSART_TxData(uint8_t index) 
 * 
 * 
 *****************************************************************************/
void EUSART_CommandTxData(uint8_t index)
{
   

	outputBuf[0]='F'; //0x46
	outputBuf[1]='P'; //0x50
    outputBuf[2]='O'; //0x4F ->order
	outputBuf[3]=index; 
//	outputBuf[3]=index+0x30;	// change to ascii number for decimal number 0~9
   if(run_t.eusartTx_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputBuf[run_t.eusartTx_Num];
	        run_t.eusartTx_Num++;
            
       }
	   transOngoingFlag=1;
	   if(run_t.eusartTx_Num==4)run_t.eusartTx_flag=1;
	    PIE3bits.TXIE=1;
   	}
   
}

void Ble_RxData_EUSART(void)
{
	PIE3bits.RC1IE = 0;
        
        
      bleBuf[i]=RC1REG;
    
		if(i==0){
			
			
	        if(bleBuf[0]=='M'){
	             TX1REG = bleBuf[0];//recdata[i]; // ???????? // ??
                 
			}
			else i=0;
		}
		else if(i==1){
            
	        if(bleBuf[1]=='X'){
	            // TX1REG = bleBuf[1];//recdata[i]; // ???????? // ??
            }
	        else i=0;
		}
        /******/
        else if(i==2){
            if(bleBuf[2]=='S'){
            
            }
            else
                i=0;
        
        }
        else if(i==3){
            if(bleBuf[3]=='P'){
            
            }
            else
                i=0;
        
        }
        else if(i==4){
            if(bleBuf[4]=='O'){
            
            }
            else
                i=0;
        }
        else if(i==5){
             if(bleBuf[5]=='R'){
            
            }
            else
                i=0;
        
        
        }
         else if(i==6){
             if(bleBuf[6]=='T'){
            
            }
            else
                i=0;
        
       }
        /*up add new item*/
		else if(i==7){
            if(bleBuf[7]=='B' || bleBuf[7]=='L' || bleBuf[7]=='F' ){
                ble_t.bleInputCmd[0]=bleBuf[7];
	            // TX1REG = bleBuf[7];//recdata[i]; // ???????? // ??
            }
			else i=0;
		}
		else if(i==8){

		    if((bleBuf[7] -0x30) >12){
                 i=0;
            }
			else{
			   ble_t.bleInputCmd[1]=bleBuf[8]; 
              
			  // TX1REG = bleBuf[8];//recdata[i]; // ???????? // ??
			}

		 }
        i++;
		if(i==9){
            i=0;
            run_t.gBle_Mode=1;
        }
        
     PIE3bits.RC1IE = 1; 
   //  PIE3bits.TX1IE = 1;
	
	
}

/******************************************************************************
 * 
 *Function Name: void Ble_RxData_EUSART_ISR(void)
 * 
 * 
 *****************************************************************************/
void Ble_RxData_EUSART_ISR(void)
{
	PIE3bits.RC1IE = 0;
    static uint8_t i=0;  
  
        bleBuf[i]=RC1REG;
    
        switch(i){
            
            case 0:
             if(bleBuf[0]=='M'){
                     i++;
                 
			  }
		     break;
             
            case 1:
		       if(bleBuf[1]=='X'){
	              i++;
              }
	        else i=0;
		   break;
        /*****/
            case 2:
    
            if(bleBuf[2]=='S'){
                i++;
            }
            else
                i=0;
        
            break;
            
            case 3:
            if(bleBuf[3]=='P'){
                i++;
            }
            else
                i=0;
        
            break;
            
            case 4:
            if(bleBuf[4]=='O'){
                i=5;
            }
            else
                i=0;
            break;
            
            case 5:
             if(bleBuf[5]=='R'){
                 i++;
            }
            else
                i=0;
        
        
             break;
             
            case 6:
             if(bleBuf[6]=='T'){
                 i++;
            }
            else
                i=0;
        
             break;
        /*up add new item*/
            case 7:
            if(bleBuf[7]=='B' || bleBuf[7]=='L' || bleBuf[7]=='F' ){
                ble_t.bleInputCmd[0]=bleBuf[7];
                i++;
            }
			else i=0;
            
            break;
            
            case 8:

		    if((bleBuf[7] -0x30) >12){
                 i=0;
            }
			else{
			   ble_t.bleInputCmd[1]=bleBuf[8]; 
               i++;
             }
            break;
     
		if(i==9){
            i=0;
            
            run_t.gBle_Mode=1;
        }
        
    PIE3bits.RC1IE = 1; 
   //  PIE3bits.TX1IE = 1;
	
        }
}

/*********************************************************************
	*
	*Function Name:void Bluetooth_RunCmd(void)
	*Funciton :key input value of response active
	*Input Ref: input key pressed of value .
	*Return Ref: NO
	*
*********************************************************************/
void Bluetooth_RunCmd(void)
{
    
    static uint8_t flag =0,bleTarget;
	//uint8_t cmdType=ble_t.bleInputCmd[0];
     bleTarget=ble_t.bleInputCmd[1]-0x30;

	if(ble_t.bleInputCmd[0] =='B'  ) //open lamp or laser
	{
		flag =1;
	    run_t.gBleItem=1;
       
    }
	else if(ble_t.bleInputCmd[0]=='L'){ //adjust lamp brightness
		
		flag =2;
		 run_t.gBleItem=1;
	}
	else if(ble_t.bleInputCmd[0]=='F' ){ //turn off lamp and laser
		
		flag=3;
		 run_t.gBleItem=1;
	}
	else{
		flag =0;
		run_t.gBleItem=0;
	}
	 

	if(flag==1){ //LED AND LASE
        switch(bleTarget ){
            

            case 1:	            

              run_t.gRunOrder= CCW;              
                            
                                
            break;
            case 2:
                    
              run_t.gRunOrder= CW;            
           
            break;

        
            
            default:
            break;

        }
	}
    if(flag ==2){ //brightness lamp 
	
	    if(bleTarget == 0){
			
			//ADJ_LampBrightnessADD();
			 run_t.gRunOrder= middle;
			
		}
		if(bleTarget == 1){
			
			//ADJ_LampBrightnessSUB();
			run_t.gRunOrder= slow;
			
		}
        if(bleTarget == 2){
			
			//ADJ_LampBrightnessSUB();
			run_t.gRunOrder= fast;
			
		}
	
	}
	//turn off all lamp and laser 
	if(flag==3){ //turn off lamp 
		
       
        run_t.gRunOrder= noRun;
        run_t.gBleItem=1;
	}
	
}

/******************************************************************************
 * 
 *Function Name: EUSART_TxData_Name(uint8_t index) 
 * Function:transmit data
 * Input Ref:
 * Return Ref:
 * 
 *****************************************************************************/
void EUSART_BleCommandTxData_Name(void)
{
    
   //AT+SPPNAME=ForenScope CSI
    
     outputBuf[0]='A';
     outputBuf[1]='T';
     outputBuf[2]='+';
     outputBuf[3]='S';
     outputBuf[4]='P';
     outputBuf[5]='P';
     outputBuf[6]='N';
     outputBuf[7]='A';
     outputBuf[8]='M';
     outputBuf[9]='E';
     outputBuf[10]='=';
       
	outputBuf[11]='F'; //0x46
	outputBuf[12]='o'; //0x50
    outputBuf[13]='r'; //0x4F ->order
    outputBuf[14]='e';
	outputBuf[15]='n'; 
    outputBuf[16]='S';
    outputBuf[17]='c';
    outputBuf[18]='o';
    outputBuf[19]='p';
    outputBuf[20]='e';
    outputBuf[21]=' ';
    outputBuf[22]='R';
    outputBuf[23]='O';
    outputBuf[24]='T';
//	outputBuf[3]=index+0x30;	// change to ascii number for decimal number 0~9
   if(run_t.eusartTx_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputBuf[run_t.eusartTx_Num];
	        run_t.eusartTx_Num++;
            
       }
	   transOngoingFlag=1;
	   if(run_t.eusartTx_Num==25)run_t.eusartTx_flag=1;
	    PIE3bits.TXIE=1;
   	}
   
}
/******************************************************************************
 * 
 *Function Name: void EUSART_BleCommandTxBaud(void)
 * Function:transmit data
 * Input Ref:NO
 * Return Ref:NO
 * 
 *****************************************************************************/
void EUSART_BleCommandTxBaud(uint8_t baudrate)
{
   //AT+BAUD=1
    
     outputBaudBuf[0]='A';
     outputBaudBuf[1]='T';
     outputBaudBuf[2]='+';
     outputBaudBuf[3]='B';
     outputBaudBuf[4]='A';
     outputBaudBuf[5]='U';
     outputBaudBuf[6]='D';
     outputBaudBuf[7]='=';
     outputBaudBuf[8]=baudrate; //'0x31'-9600bit ;'0x38'-115200bit
   if(run_t.eusartTx_Baud_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputBaudBuf[run_t.eusartTx_Baud_n];
	        run_t.eusartTx_Baud_n++;
            
       }
	   transOngoingFlag=1;
	   if(run_t.eusartTx_Baud_n==9)run_t.eusartTx_Baud_flag=1;
	    PIE3bits.TXIE=1;
   	}
}

void EUSART_BleCommandTxOpenSetBaud(void)
{
   //AT+BAUD=1
    
     outputBaudSetBuf[0]='A';
     outputBaudSetBuf[1]='T';
     outputBaudSetBuf[2]='+';
     outputBaudSetBuf[3]='B';
     outputBaudSetBuf[4]='A';
     outputBaudSetBuf[5]='U';
     outputBaudSetBuf[6]='D';
     outputBaudSetBuf[7]='A';
     outputBaudSetBuf[8]='B';
     outputBaudSetBuf[9]='T';
     outputBaudSetBuf[10]='=';
     outputBaudSetBuf[11]='1';
   if(ble_t.ble_openbaud_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputBaudSetBuf[ble_t.ble_openbaud_n];
	        ble_t.ble_openbaud_n++;
            
       }
	   transOngoingFlag=1;
	   if(ble_t.ble_openbaud_n==12)ble_t.ble_openbaud_flag=1;
	    PIE3bits.TXIE=1;
   	}
}

void EUSART_BleCommandTxReset(void)
{
   //AT+BAUD=1
    //AT+SPPNAME=ForenScope CSI
    
     outputResetBuf[0]='A';
     outputResetBuf[1]='T';
     outputResetBuf[2]='+';
     outputResetBuf[3]='R';
     outputResetBuf[4]='E';
     outputResetBuf[5]='S';
     outputResetBuf[6]='E';
     outputResetBuf[7]='T';
  
   if(ble_t.ble_reset_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputResetBuf[ble_t.ble_reset_n];
	        ble_t.ble_reset_n++;
            
       }
	   transOngoingFlag=1;
	   if( ble_t.ble_reset_n==8)ble_t.ble_reset_flag=1;
	    PIE3bits.TXIE=1;
   	}
}
/******************************************************************************
 * 
 *Function Name: void EUSART_BleResponseEvent(void)
 * Function:transmit data
 * Input Ref:NO
 * Return Ref:NO
 * 
 *****************************************************************************/
void EUSART_BleResponseEvent(uint8_t lampNum)
{
        
    
     outputResponseText[0]='L';
     outputResponseText[1]='O';
     outputResponseText[2]= 0x30+lampNum;
    if(ble_t.ble_response_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputResponseText[ble_t.ble_response_n];
	        ble_t.ble_response_n++;
            
       }
	   transOngoingFlag=1;
	   if(ble_t.ble_response_n==3)ble_t.ble_response_flag =1;
	    PIE3bits.TXIE=1;
   	} 

}
/******************************************************************************
 * 
 *Function Name: void BLUETOOTH_MainRun(void)
 * Function:
 * Input Ref:NO
 * Return Ref:NO
 * 
 *****************************************************************************/
void BLUETOOTH_MainRun(void)
{
     static uint8_t n,m;
     if(run_t.gEEPROM_start==0){
           IO_POWER_RB7_SetLow();
           BLE_MODE_RA7_SetLow();//BLE_MODE_RC2_SetLow();
           run_t.gReadEEPROM_flag=DATAEE_ReadByte(0x10);
         // if(run_t.gReadEEPROM_flag==0x0A){
            //  run_t.gEEPROM_start++;
            //  EUSART_Initialize_9600();
         // }
        //  else{ 
                if(run_t.eusartTx_flag<2){
                    BLE_MODE_RA7_SetLow();//BLE_MODE_RC2_SetLow();
                    EUSART_BleCommandTxData_Name();
                    if(run_t.eusartTx_flag==1){
                        n++;
                        run_t.eusartTx_Num=0;
                        run_t.eusartTx_flag=0;
                        DELAY_milliseconds(200); 
                        if(n>5){
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
                        if(m>5){
                            run_t.eusartTx_flag=4;
                            DATAEE_WriteByte(0x10,0x0A);
                            run_t.gEEPROM_start++;
                            //EUSART_Initialize_9600();
                        }
                    }
                }
           // }
        }
    
}