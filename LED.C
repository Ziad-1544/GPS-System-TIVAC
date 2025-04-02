////////////////////////////////////////////////////
///////           File:LED.C              /////////
///////      Ain Shams University        /////////
//////     Intro To Embedded Project    /////////
/////     AUTHOR: Randa Ayman Samir    /////////
/////           CREATED:28/03/2025     ////////
////////////////////////////////////////////// 

#include "microconfig.h"

void RGB_Output(uint32_t data) {
    // Ensure LEDs are set as outputs before writing data
    GPIO_PORTF_DATA_R = data;
}

void LED_SetColor(distance) {
   void LED_SetColor(int distance) {  
    int category = (distance > 5) * 3 + (distance > 2.5 && distance <= 5) * 2 + (distance > 0 && distance <= 2.5) * 1;

    switch (category) {  
        case 3:  
            RGB_Output(0x02); // Red LED  
            break;  
        case 2:  
            RGB_Output(0x0A); // Yellow LED  
            break;  
        case 1:  
            RGB_Output(0x08); // Green LED  
            break;  
        default:  
            RGB_Output(0x00); // LEDs Off  
            break;  
    }  
}

