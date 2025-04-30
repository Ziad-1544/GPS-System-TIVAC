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

void CLCD_voidDataSendString(u8 *Copy_u8Str);

void CLCD_voidDataSetCursor(u8 Copy_u8LineNum, u8 Copy_u8Location);

void CLCD_voidClearDisplay(void);

void CLCD_voidSendNum(u16 Copy_u16Num);

#define LINE_1   0
#define LINE_2   1

#endif
