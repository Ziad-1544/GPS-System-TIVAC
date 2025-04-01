////////////////////////////////////////////////////
///////           File:LED.C              /////////
///////      Ain Shams University        /////////
//////     Intro To Embedded Project    /////////
/////     AUTHOR: Randa Ayman Samir    /////////
/////           CREATED:1/04/2025     ////////
////////////////////////////////////////////// 

#include "microconfig.h"

void lcd_init(LCD_t *lcd) {
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {}

    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |= 0xFF;
    GPIO_PORTB_AMSEL_R = 0;
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_PCTL_R = 0;
    GPIO_PORTB_DEN_R = 0xFF;
    GPIO_PORTB_DIR_R = 0xFF;

    lcd_cmd(lcd, Set5x7FontSize);
    lcd_cmd(lcd, four_bit_mode);
    lcd_cmd(lcd, lcd_EntryMode);
    lcd_cmd(lcd, lcd_Clear);
    lcd_cmd(lcd, lcd_DisplayOn);
    lcd_cmd(lcd, first_row);
}

// ........................................................................................Send a command to the LCD.....................................................................................//
void lcd_cmd(LCD_t *lcd, uint8_t cmd) {
    lcd_write(lcd, cmd & 0xF0, 0);
    lcd_write(lcd, cmd << 4, 0);
    if (cmd < 4) {
        lcd->delayMs(20);
    } else {
        lcd->delayUs(400);
    }
}

// ........................................................................................Send data or command to LCD.....................................................................................//
void lcd_write(LCD_t *lcd, uint8_t c, uint8_t ctrl) {
    c &= 0xF0;
    ctrl &= 0x0F;
    GPIO_PORTB_DATA_R = c | ctrl;
    GPIO_PORTB_DATA_R = c | ctrl | EN;
    lcd->delayMs(50);
    GPIO_PORTB_DATA_R = c;
    GPIO_PORTB_DATA_R = 0;
}

//........................................................................................... Print a character to LCD.....................................................................................//
void lcd_char(LCD_t *lcd, char data,uint8_t ctrl) {
    lcd_write(lcd, data & 0xF0, RS);
    lcd_write(lcd, data << 4, RS);
    lcd->delayUs(40);
}

// ............................................................................................Print a string to LCD........................................................................................//
void lcd_str(LCD_t *lcd, char *str) {
   int i;	
	for( i = 0; *str!=0; i++){
		lcd_char(*(str++),RS);
    }
}

//....................................................................................... Print a string on the second row...................................................................................//
void lcd_str_2nd_row(LCD_t *lcd, char *str) {
 int i;
    lcd_cmd(lcd, second_row);	
	for( i = 0; *str!=0; i++){
		lcd_char(*(str++),RS);
}

// ..............................................................................................Reverse a string............................................................................................//
void reverse(char* str, int len) {
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

//....................................................................................... Convert an integer to a string......................................................................................//
int intToStr(int x, char str[], int d) {
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
