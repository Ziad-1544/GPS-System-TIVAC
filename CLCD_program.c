/*
----->Layer:  HAL
----->SWC:    LCD
----->DATE:   12-4-200
----->VERSION:V1.0.0
----->AUTHOR: Randa Ayman    
*/


#include "GPIO_interface.h" 
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "STD_TYPES.h"
#include "SYSTICK_interface.h"
//INCLUDE SYSTICK INTERFACE & CHANGE ANY FUNCTION OF DELAY TO SISTICK DELAY 
//ADJUST ALL GPIO FUNCTION AND IT'S INPUT 
//add delay between each command 1 ms 
STD_ERROR CLCD_8DataPinsInit (void)
{  
    STD_ERROR ret = NOK;
    DIO_voidSetPortDirection(DATA_PORT,PORT_OUTPUT);
	DIO_voidSetPinDirection(CTRL_PORT,ENA,PIN_OUTPUT);
	DIO_voidSetPinDirection(CTRL_PORT,RW,PIN_OUTPUT);
	DIO_voidSetPinDirection(CTRL_PORT,RS,PIN_OUTPUT);
   

        Systick_DelayIn_ms(1);
        CLCD_voidSendCommand(0b00111000);
        Systick_DelayIn_ms(1);
        CLCD_voidSendCommand(0b00001100);
        Systick_DelayIn_ms(1);
        CLCD_voidSendCommand(0b00000001);
        Systick_DelayIn_ms(1);
          // Set success
    ret = OK;
    return ret;
    }
   
STD_ERROR  CLCD_8DataPinssendCommand( u8 command){
    STD_ERROR ret = NOK;
    //RS    0
    DIO_voidSetPinValue(CTRL_PORT,RS,PIN_LOW);
    //RW    0
    DIO_voidSetPinValue(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
    DIO_voidSetPortValue(DATA_PORT, command);
    //E     PULSE
    DIO_voidSetPinValue(CTRL_PORT,ENA,PIN_HIGH);
    Systick_DelayIn_ms(1);
    DIO_voidSetPinValue(CTRL_PORT,ENA,PIN_LOW);

    Systick_DelayIn_ms(2);

    // Set success
    ret = OK;
    return ret;

}

STD_ERROR CLCD_8DATASendData(u8 Data){
    STD_ERROR ret = NOK;

    //RS    1
    DIO_voidSetPinValue(CTRL_PORT,RS,PIN_HIGH);
    //RW    0
    DIO_voidSetPinValue(CTRL_PORT,RW,PIN_LOW);
    //SET DATA ->DATA PORT
    DIO_voidSetPortValue(DATA_PORT,Data);
    //E     PULSE
    DIO_voidSetPinValue(CTRL_PORT,ENA,PIN_HIGH);
    Systick_DelayIn_ms(1);
    DIO_voidSetPinValue(CTRL_PORT,ENA,PIN_LOW);
    Systick_DelayIn_ms(2);

    // Set success
    ret = OK;
    return ret;
}


STD_ERROR CLCD_8DATASendString( u8 *str){
    STD_ERROR ret = NOK;
    u8 LOCAL_Str=0;
    while(str[LOCAL_Str] != '\0'){
    	CLCD_8DATASendData(str[LOCAL_Str]);
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

void CLCD_voidClearDisplay(){
    CLCD_8DataPinssendCommand(1);
}



void CLCD_voidSendSpecialCharacter(u8 Copy_u8BlockNum, u8 Copy_HorizontalValue,u8 copy_AbsVerticalValue,u8 *Pu8ArrayPattern){
    u8 Local_u8AddressPosition=Copy_u8BlockNum*8;
    //go to CGRAM -->CMD SETT_GCRAM_ADD
    CLCD_8DataPinssendCommand(Local_u8AddressPosition+lcd_CGRAM_START );
    //START DRAWING PATTERN
    for (u8 i = 0; i < 8; i++)
    {
        CLCD_8DATASendData (Pu8ArrayPattern[i]);
    }
    //DISPLAY PATTERN
    CLCD_8DATASetCursor(Copy_HorizontalValue,copy_AbsVerticalValue);
    CLCD_8DATASendData(Copy_u8BlockNum);



}



void CLCD_SendNum(u16 Num){
    u8 LOCAL_u8Num,LOCAL_u8counter=0;
    u8 arr[100]={0};
    do{
        LOCAL_u8Num=Num%10;
        Num/=10;
        arr[LOCAL_u8counter]=LOCAL_u8Num + '0';
        LOCAL_u8counter++;
    }while(Num!=0);
    for (u8 i = LOCAL_u8counter; i >0 ; i--)
    {
        CLCD_8DATASendData(arr[i-1]);
        Systick_DelayIn_ms(1);
    }
}

