////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                CLCD              /////////
////                Version:3.0       /////////
///         DATE:   10-5-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////


#include "GPIO_interface.h" 
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "STD_TYPES.h"
#include "SYSTICK_interface.h"

STD_ERROR CLCD_StdErrorDataPinsInit (void)
{  
    STD_ERROR local_functionstatus = NOK;

    GPIO_StdErrorSetPortDir(DATA_PORT,PORT_OUTPUT);        // Set data port as output
	GPIO_StdErrorSetPinDir(CTRL_PORT,ENA,PIN_OUTPUT);      // Set EN pin as output
	GPIO_StdErrorSetPinDir(CTRL_PORT,RW,PIN_OUTPUT);       // Set RW pin as output
	GPIO_StdErrorSetPinDir(CTRL_PORT,RS,PIN_OUTPUT);       // Set RS pin as output
    
    Systick_StdErrorDelayIn_ms(50);

    CLCD_StdErrorDataPinssendCommand(0x38);                // Function set: 8-bit, 2 lines, 5x8 font   0b00111000
    Systick_StdErrorDelayIn_ms(4);
    CLCD_StdErrorDataPinssendCommand(0xF);                 // Display ON, cursor OFF    0b00001100
    Systick_StdErrorDelayIn_ms(4);
    CLCD_StdErrorDataPinssendCommand(0x1);                 // Clear display       0b00000001
    Systick_StdErrorDelayIn_ms(4);
    CLCD_StdErrorDataPinssendCommand(0x6);                 // Entry mode set: increment, no shift   0b00000110
    // Set success
    local_functionstatus = OK;
    return local_functionstatus;
    }
   
STD_ERROR  CLCD_StdErrorDataPinssendCommand(u8 Copy_u8Command){
    STD_ERROR local_functionstatus = NOK;
    //RS    0   command mode
    GPIO_StdErrorWritePin(CTRL_PORT,RS,PIN_LOW);
    //RW    0  write mode
    GPIO_StdErrorWritePin(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
    GPIO_StdErrorWritePort(DATA_PORT, Copy_u8Command);
    //E     PULSE
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_HIGH);   // Pulse EN = HIGH
    Systick_StdErrorDelayIn_ms(2);
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_LOW);     // Pulse EN = LOW

    Systick_StdErrorDelayIn_ms(2);

    // Set success
    local_functionstatus = OK;
    return local_functionstatus;

}

STD_ERROR CLCD_StdErrorSendData(u8 Copy_u8Data){
    STD_ERROR local_functionstatus = NOK;

    //RS    1  data mode
    GPIO_StdErrorWritePin(CTRL_PORT,RS,PIN_HIGH);
    //RW    0   write mode
   GPIO_StdErrorWritePin(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
    GPIO_StdErrorWritePort(DATA_PORT,Copy_u8Data);
    //E     PULSE
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_HIGH);    // Pulse EN = HIGH
    Systick_StdErrorDelayIn_ms(2);
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_LOW);      // Pulse EN = LOW
    Systick_StdErrorDelayIn_ms(2);

    // Set success
    local_functionstatus = OK;
    return local_functionstatus;
}

void CLCD_VoidDataSendString(u8 *Copy_u8Str){
    u8 LOCAL_Str=0;
    while(Copy_u8Str[LOCAL_Str] != '\0'){
    	CLCD_StdErrorSendData(Copy_u8Str[LOCAL_Str]);         // Send each char    SendData function from private
    	LOCAL_Str++;
    }
}

void CLCD_VoidDataSetCursor(u8 Copy_u8LineNum, u8 Copy_u8Location){
    
    switch (Copy_u8LineNum) {
        case LINE_1: CLCD_StdErrorDataPinssendCommand(0x80 + Copy_u8Location); break;   //The "column" is added to this base address. 
        case LINE_2: CLCD_StdErrorDataPinssendCommand(0xC0 + Copy_u8Location); break;
    }
}

void CLCD_VoidClearDisplay(void){
    CLCD_StdErrorDataPinssendCommand(0x01);
	Systick_StdErrorDelayIn_ms(2);
}

void CLCD_VoidSendNum(u16 Copy_u16Num){
    u16 LOCAL_u8Num,LOCAL_u8counter=0;
    u16 arr[100]={0};
	u16 i;
    do{
        LOCAL_u8Num=Copy_u16Num % 10;           // Extract last digit

        Copy_u16Num/=10;                    // Remove last digit
        
        arr[LOCAL_u8counter] = LOCAL_u8Num + '0';    //ASCII
        
        LOCAL_u8counter++;
    
    }while(Copy_u16Num!=0);
    
    for (i = LOCAL_u8counter; i >0 ; i--)
    {
    
        CLCD_StdErrorSendData(arr[i-1]);         // Send digits in correct order
    
        Systick_StdErrorDelayIn_ms(2);
    }
}
