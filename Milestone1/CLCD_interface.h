////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                CLCD              /////////
////                Version:1.1       /////////
///         DATE:   12-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef LCD_INTERFACE_h_
#define LCD_INTERFACE_h_

#include "CLCD_config.h"
#include "CLCD_private.h"
#include "GPIO_Interface.h"




STD_ERROR CLCD_StdErrorDataPinsInit (void);

STD_ERROR CLCD_StdErrorDataSendString(u8 *Copy_u8Str);
STD_ERROR CLCD_StdErrorDataSetCursor(u8 Copy_u8row, u8 Copy_u8column);
void CLCD_VoidClearDisplay();
void CLCD_VoidSendSpecialCharacter(u8 Copy_u8BlockNum, u8 Copy_u8HorizontalValue,u8 copy_u8AbsVerticalValue,u8 *Copy_u8ArrayPattern);
void CLCD_VoidSendNum(u16 Copy_u16Num);

#endif
