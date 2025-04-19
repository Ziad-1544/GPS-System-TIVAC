/*
----->Layer:  HAL
----->SWC:    LCD
----->DATE:   12-4-200
----->VERSION:V1.0.0
----->AUTHOR: Randa Ayman    
*/

#ifndef LCD_INTERFACE_h_
#define LCD_INTERFACE_h_

#include "CLCD_config.h"
#include "CLCD_private.h"
#include "GPIO_Interface.h"




STD_ERROR CLCD_8DataPinsInit (void);


STD_ERROR CLCD_8DATASendString( u8 *str);
STD_ERROR CLCD_8DATASetCursor( u8 row, u8 column);
STD_ERROR convert_uint16_to_string(u16 value);
void CLCD_ClearDisplay();
void CLCD_voidSendSpecialCharacter(u8 Copy_u8BlockNum, u8 Copy_HorizontalValue,u8 copy_AbsVerticalValue,u8 *Pu8ArrayPattern);
void CLCD_SendNum(u16 Num);

#endif
