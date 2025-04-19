////////////////////////////////////////////////////
///////           File:LED.C              /////////
///////      Ain Shams University        /////////
//////     Intro To Embedded Project    /////////
/////     AUTHOR: Randa Ayman Samir    /////////
/////           CREATED:28/03/2025     ////////
////////////////////////////////////////////// 

#include"GPIO_Interface.h"
#include "LED_interface.h"
#include "LED_private.h"


static void LED_ClearAll(void)
{
    GPIO_WritePin(LED_PORT, RED_LED, 0);   // Turn off red
    GPIO_WritePin(LED_PORT, GREEN_LED, 0); // Turn off green
}

void LED_ExternalControl(u32 InputPort, u8 InputPin)
{
    u8 inputValue;
    GPIO_ReadPin(InputPort, InputPin, &inputValue);

    if (inputValue)
    {
        GPIO_WritePin(LED_PORT, EXTERNAL_LED, 1);  // Turn ON external LED
    }
    else
    {
        GPIO_WritePin(LED_PORT, EXTERNAL_LED, 0);  // Turn OFF external LED
    }
}

//void LED_SetColor(distance) {
  
//    int category = (distance > 5) * 3 + (distance > 2.5 && distance <= 5) * 2 + (distance > 0 && distance <= 2.5) * 1;

//    switch (category) {  
   //     case 3:  
    //        RGB_Output(0x02); // Red LED  
    //        break;  
    //    case 2:  
    //        RGB_Output(0x0A); // Yellow LED  
   //         break;  
     //   case 1:  
     //       RGB_Output(0x08); // Green LED  
     //       break;  
     //   default:  
     //       RGB_Output(0x00); // LEDs Off  
      //      break;  
    }  
}

