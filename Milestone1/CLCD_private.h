////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                CLCD              /////////
////                Version:1.1       /////////
///         DATE:   12-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef CLCD_PRIVATE
#define CLCD_PRIVATE
STD_ERROR  CLCD_StdErrorDataPinssendCommand(u8 Copy_u8Command);
STD_ERROR CLCD_StdErrorDataSendData(u8 Copy_u8Data);

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
