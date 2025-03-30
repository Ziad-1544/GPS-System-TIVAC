#include "led.h"

void RGB_Output(uint32_t data) {
    // Ensure LEDs are set as outputs before writing data
    GPIO_PORTF_DATA_R = data;
}

void LED_SetColor(distance) {
    switch (1) {  
        case (distance > 5):
            RGB_Output(0x02); // Red LED
            break;
        case (distance > 2.5):
            RGB_Output(0x0A); // Yellow LED
            break;
        case (distance > 0):
            RGB_Output(0x08); // Green LED
            break;
        default:
            RGB_Output(0x00); // LEDs Off
            break;
    }
}


