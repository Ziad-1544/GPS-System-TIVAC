/*
----->Layer:  HAL
----->SWC:    LCD
----->DATE:   12-4-200
----->VERSION:V1.0.0
----->AUTHOR: Randa Ayman    
*/

#ifndef LCD_INTERFACE_h_
#define LCD_INTERFACE_h_

#include "lcd_config.h"
#include "lcd_private.h"
#include "GPIO_Interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"
//.........................................................................................Macro declarations(character lcd interfacing)....................................................................................................//
 


#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];

}chr_lcd_8bit_t;

STD_ERROR lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);
STD_ERROR lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);
STD_ERROR lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);
STD_ERROR lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
STD_ERROR lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);
STD_ERROR lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
STD_ERROR convert_uint8_to_string(uint8 value, uint8 *str);
STD_ERROR convert_uint16_to_string(uint16 value, uint8 *str);
STD_ERROR convert_uint32_to_string(uint32 value, uint8 *str);


#endif