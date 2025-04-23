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

STD_ERROR CLCD_8DataPinsInit (void)
{  
    STD_ERROR ret = NOK;
        GPIO_SetPortDir(DATA_PORT,PORT_OUTPUT);        // Set data port as output
	GPIO_SetPinDir(CTRL_PORT,ENA,PIN_OUTPUT);      // Set EN pin as output
	GPIO_SetPinDir(CTRL_PORT,RW,PIN_OUTPUT);       // Set RW pin as output
	GPIO_SetPinDir(CTRL_PORT,RS,PIN_OUTPUT);       // Set RS pin as output
   

         Systick_DelayIn_ms(1);
        CLCD_8DataPinssendCommand(0x38);                // Function set: 8-bit, 2 lines, 5x8 font   0b00111000
        Systick_DelayIn_ms(1);
        CLCD_8DataPinssendCommand(0xC);                 // Display ON, cursor OFF    0b00001100
        Systick_DelayIn_ms(1);
        CLCD_8DataPinssendCommand(0x1);                 // Clear display       0b00000001
        Systick_DelayIn_ms(1);
          // Set success
    ret = OK;
    return ret;
    }
   
STD_ERROR  CLCD_8DataPinssendCommand( u8 command){
    STD_ERROR ret = NOK;
    //RS    0   command mode
   GPIO_WritePin(CTRL_PORT,RS,PIN_LOW);
    //RW    0  write mode
    GPIO_WritePin(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
   GPIO_WritePort(DATA_PORT, command);
    //E     PULSE
    GPIO_WritePin(CTRL_PORT,ENA,PIN_HIGH);   // Pulse EN = HIGH
    Systick_DelayIn_ms(1);
    GPIO_WritePin(CTRL_PORT,ENA,PIN_LOW);     // Pulse EN = LOW

    Systick_DelayIn_ms(2);

    // Set success
    ret = OK;
    return ret;

}

STD_ERROR CLCD_8DATASendData(u8 Data){
    STD_ERROR ret = NOK;

    //RS    1  data mode
    GPIO_WritePin(CTRL_PORT,RS,PIN_HIGH);
    //RW    0   write mode
    GPIO_WritePin(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
    GPIO_WritePort(DATA_PORT,Data);
    //E     PULSE
    GPIO_WritePin(CTRL_PORT,ENA,PIN_HIGH);    // Pulse EN = HIGH
    Systick_DelayIn_ms(1);
    GPIO_WritePin(CTRL_PORT,ENA,PIN_LOW);      // Pulse EN = LOW
    Systick_DelayIn_ms(2);

    // Set success
    ret = OK;
    return ret;
}


STD_ERROR CLCD_8DATASendString( u8 *str){
    STD_ERROR ret = NOK;
    u8 LOCAL_Str=0;
    while(str[LOCAL_Str] != '\0'){
    	CLCD_8DATASendData(str[LOCAL_Str]);         // Send each char    SendData function from private
    	LOCAL_Str++;

    }
    ret = OK;

    return ret;

}


 STD_ERROR CLCD_8DATASetCursor(u8 row, u8 column) {
    STD_ERROR ret = NOK;

    // Validate input
    if ((row >= 1) || (column == 0 || column > 15)) {
        return NOK;
    }

    column--;  // Convert to 0-based index

    switch (row) {
        case 0: ret = CLCD_8DataPinssendCommand(0x80 + column); break;   //The "column" is added to this base address. 
        case 1: ret = CLCD_8DataPinssendCommand(0xC0 + column); break;
        
        default: ret = NOK; break;
    }

    return ret;
}

void CLCD_ClearDisplay(){
    CLCD_8DataPinssendCommand(1);
	Systick_DelayIn_ms(2);
}



void CLCD_voidSendSpecialCharacter(u8 Copy_u8BlockNum, u8 Copy_HorizontalValue,u8 copy_AbsVerticalValue,u8 *Pu8ArrayPattern){
    u8 Local_u8AddressPosition=Copy_u8BlockNum*8;          // Calculate CGRAM address
	u8 i;
    //go to CGRAM -->CMD SETT_GCRAM_ADD
    CLCD_8DataPinssendCommand(Local_u8AddressPosition+lcd_CGRAM_START );      // Set CGRAM address
    //START DRAWING PATTERN
    for (i = 0; i < 8; i++)
    {
        CLCD_8DATASendData (Pu8ArrayPattern[i]);                // Write pattern
    }
    //DISPLAY PATTERN
    CLCD_8DATASetCursor(Copy_HorizontalValue,copy_AbsVerticalValue);     // Set cursor to display location
    CLCD_8DATASendData(Copy_u8BlockNum);                                 // Display special character



}



void CLCD_SendNum(u16 Num){
    u8 LOCAL_u8Num,LOCAL_u8counter=0;
    u8 arr[100]={0};
	u8 i;
    do{
        LOCAL_u8Num=Num%10;           // Extract last digit
        Num/=10;                    // Remove last digit
        arr[LOCAL_u8counter]=LOCAL_u8Num + '0';    //ASCII
        LOCAL_u8counter++;
    }while(Num!=0);
    for (i = LOCAL_u8counter; i >0 ; i--)
    {
        CLCD_8DATASendData(arr[i-1]);         // Send digits in correct order
        Systick_DelayIn_ms(1);
    }
}

