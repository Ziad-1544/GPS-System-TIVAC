#include"GPIO_Interface.h"
#include"BIT_MATH.h"
#include"SYSTICK_config.h"
int main()
{
     // 1. Initialize ports for LCD, Switch, LEDs
    //initialize PORT A
   //initialize PORT B
  //initialize PORT C
 //initialize PORT D
//initialzie SysTick 

    u8 mode_variable = 0;
    u8 sw1_prev = 1;  // to detect edge
    u8 sw2_prev = 1;

    RGB_Output(0x02);   //red led on
    
    CLCD_8DATASendString((u8 *)"loading");   // Display on LCD

    
    
    

   
    while (1)
    {
        u8 sw1_val = GPIO_ReadPin(PORT_D, SW1_BIT); // SW1 for mode selection
        u8 sw2_val = GPIO_ReadPin(PORT_D, SW1_BIT); // SW2 for choosing option

        // Handle mode switch (SW1)
        if (sw1_val == 0 && sw1_prev == 1)  // falling edge detection
        {
            mode_variable++;
            if (mode_variable > 3)
                mode_variable = 0;

            // Optional: Show mode number on LCD
            CLCD_8DATASendCommand(0x01); // clear display
            CLCD_8DATASendString((u8 *)"Mode: ");
            CLCD_8DATASendNumber(mode_variable);

            RGB_Output(0x0A); // yellow LED to indicate mode change

            Systick_DelayIn_ms(300); // debounce delay
        }
        sw1_prev = sw1_val;

        // Handle action switch (SW2)
        if (sw2_val == 0 && sw2_prev == 1)  // falling edge detection
        {
            CLCD_8DATASendCommand(0x01); // clear display

            switch (mode_variable)
            {
            case 0:
                CLCD_8DATASendString((u8 *)"Option A");
                RGB_Output(0x04);  // green LED
                break;
            case 1:
                CLCD_8DATASendString((u8 *)"Option B");
                RGB_Output(0x02);  // red LED
                break;
            case 2:
                CLCD_8DATASendString((u8 *)"Option C");
                RGB_Output(0x08);  // blue LED
                break;
            case 3:
                CLCD_8DATASendString((u8 *)"Option D");
                RGB_Output(0x0E);  // white LED (all on)
                break;
            default:
                CLCD_8DATASendString((u8 *)"Invalid Mode");
                RGB_Output(0x01);  // red-only for error
                break;
            }

            Systick_DelayIn_ms(300); // debounce delay
        }
        sw2_prev = sw2_val;
    }

    return 0;
}