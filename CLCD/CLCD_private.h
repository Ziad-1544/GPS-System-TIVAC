////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                CLCD              /////////
////                Version:1.1       /////////
///         DATE:   12-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef CLCD_PRIVATE_h_
#define CLCD_PRIVATE_h_


//#define lcd_Clear              0x01          
//#define lcd_Home               0x02          
//#define lcd_EntryMode          0x06         
//#define lcd_DisplayOff         0x08          
//#define lcd_DisplayOn          0x0F          
//#define Set5x7FontSize         0x20					
//#define eight_bit_mode		   0x38					     
//#define first_row              0x80         
//#define second_row             0xC0          
//#define CURSOR_OFF             0x0C					 
//#define CURSOR_ON              0x0E		


STD_ERROR CLCD_8DATASendData(u8 data);
STD_ERROR CLCD_8DataPinssendCommand( u8 command);

#define lcd_CGRAM_START        0X40
#define lcd_DDRAM_START        0X80	

#define COLUMN0 0
#define COLUMN1 1
#define COLUMN2 2
#define COLUMN3 3
#define COLUMN4 4
#define COLUMN5 5
#define COLUMN6 6
#define COLUMN7 7
#define COLUMN8 8
#define COLUMN9 9
#define COLUMN10 10
#define COLUMN11 11
#define COLUMN12 12
#define COLUMN13 13
#define COLUMN14 14
#define COLUMN15 15

#define ROW0 0
#define ROW1 1

#endif
