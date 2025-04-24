////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                CLCD              /////////
////                Version:1.1       /////////
///         DATE:   12-4-2025        /////////
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
   

        Systick_DelayIn_ms(1);
        CLCD_StdErrorDataPinssendCommand(0x38);                // Function set: 8-bit, 2 lines, 5x8 font   0b00111000
        Systick_DelayIn_ms(1);
        CLCD_StdErrorDataPinssendCommand(0xC);                 // Display ON, cursor OFF    0b00001100
        Systick_DelayIn_ms(1);
        CLCD_StdErrorDataPinssendCommand(0x1);                 // Clear display       0b00000001
        Systick_DelayIn_ms(1);
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
    Systick_DelayIn_ms(1);
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_LOW);     // Pulse EN = LOW

    Systick_DelayIn_ms(2);

    // Set success
    local_functionstatus = OK;
    return local_functionstatus;

}

STD_ERROR CLCD_StdErrorDataSendData(u8 Copy_u8Data){
    STD_ERROR local_functionstatus = NOK;

    //RS    1  data mode
    GPIO_StdErrorWritePin(CTRL_PORT,RS,PIN_HIGH);
    //RW    0   write mode
   GPIO_StdErrorWritePin(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
    GPIO_StdErrorWritePort(DATA_PORT,Copy_u8Data);
    //E     PULSE
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_HIGH);    // Pulse EN = HIGH
    Systick_DelayIn_ms(1);
    GPIO_StdErrorWritePin(CTRL_PORT,ENA,PIN_LOW);      // Pulse EN = LOW
    Systick_DelayIn_ms(2);

    // Set success
    local_functionstatus = OK;
    return local_functionstatus;
}


STD_ERROR CLCD_StdErrorDataSendString(u8 *Copy_u8Str){
    STD_ERROR local_functionstatus = NOK;
    u8 LOCAL_Str=0;
    while(Copy_u8Str[LOCAL_Str] != '\0'){
    	CLCD_StdErrorDataSendData(Copy_u8Str[LOCAL_Str]);         // Send each char    SendData function from private
    	LOCAL_Str++;

    }
    local_functionstatus = OK;

    return local_functionstatus;

}


 STD_ERROR CLCD_StdErrorDataSetCursor(u8 Copy_u8row, u8 Copy_u8column) {
    STD_ERROR local_functionstatus = NOK;

    // Validate input
    if ((Copy_u8row >= 1) || (Copy_u8column == 0 || Copy_u8column > 15)) {
        return NOK;
    }

    Copy_u8column--;  // Convert to 0-based index

    switch (Copy_u8row) {
        case 0: local_functionstatus = CLCD_StdErrorDataPinssendCommand(0x80 + Copy_u8column); break;   //The "column" is added to this base address. 
        case 1: local_functionstatus = CLCD_StdErrorDataPinssendCommand(0xC0 + Copy_u8column); break;
        
        default: local_functionstatus = NOK; break;
    }

    return local_functionstatus;
}

void CLCD_VoidClearDisplay(){
    CLCD_StdErrorDataPinssendCommand(1);
	Systick_DelayIn_ms(2);
}



void CLCD_VoidSendSpecialCharacter(u8 Copy_u8BlockNum, u8 Copy_u8HorizontalValue,u8 copy_u8AbsVerticalValue,u8 *Copy_u8ArrayPattern){
    u8 Local_u8AddressPosition=Copy_u8BlockNum*8;          // Calculate CGRAM address
	u8 i;
    //go to CGRAM -->CMD SETT_GCRAM_ADD
    CLCD_StdErrorDataPinssendCommand(Local_u8AddressPosition+lcd_CGRAM_START );      // Set CGRAM address
    //START DRAWING PATTERN
    for (i = 0; i < 8; i++)
    {
        CLCD_StdErrorDATASendData (Copy_u8ArrayPattern[i]);                // Write pattern
    }
    //DISPLAY PATTERN
    CLCD_StdErrorDataSetCursor(Copy_u8HorizontalValue,copy_u8AbsVerticalValue);     // Set cursor to display location
    CLCD_StdErrorDataSendData(Copy_u8BlockNum);                                 // Display special character



}



void CLCD_VoidSendNum(u16 Copy_u16Num){
    u8 LOCAL_u8Num,LOCAL_u8counter=0;
    u8 arr[100]={0};
	u8 i;
    do{
        LOCAL_u8Num=Copy_u16Num%10;           // Extract last digit
        Copy_u16Num/=10;                    // Remove last digit
        arr[LOCAL_u8counter]=LOCAL_u8Num + '0';    //ASCII
        LOCAL_u8counter++;
    }while(Copy_u16Num!=0);
    for (i = LOCAL_u8counter; i >0 ; i--)
    {
        CLCD_StdErrorDataSendData(arr[i-1]);         // Send digits in correct order
        Systick_DelayIn_ms(1);
    }
}
