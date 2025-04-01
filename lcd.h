////////////////////////////////////////////////////
///////           File:LED.C              /////////
///////      Ain Shams University        /////////
//////     Intro To Embedded Project    /////////
/////     AUTHOR: Randa Ayman Samir    /////////
/////           CREATED:28/03/2025     ////////
////////////////////////////////////////////// 

#ifndef LCD_H_
#define LCD_H_

#define RS  0x01  
#define EN  0x04  

#define lcd_Clear            0x01          
#define lcd_Home             0x02          
#define lcd_EntryMode        0x06         
#define lcd_DisplayOff       0x08          
#define lcd_DisplayOn        0x0F          
#define Set5x7FontSize    	 0x20					
#define four_bit_mode		     0x28					     
#define first_row            0x80         
#define second_row           0xC0          
#define CURSOR_OFF           0x0C					 
#define CURSOR_ON            0x0E					 


#include "GPIO_Interface.h"

typedef struct {
    void (*delayMs)(uint32_t);  //  millisecond delay
    void (*delayUs)(uint32_t);  //  microsecond delay
} LCD_t;

//.......................................................................................... Function prototypes...............................................................................................//
void lcd_init(LCD_t *lcd);
void lcd_cmd(LCD_t *lcd, uint8_t cmd);
void lcd_write(LCD_t *lcd, uint8_t c, uint8_t ctrl);
void lcd_char(LCD_t *lcd, char data);
void lcd_str(LCD_t *lcd, char *str);
void lcd_str_2nd_row(LCD_t *lcd, char *str);
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);

#endif 
