#include "led.h"

void RGB_Output(uint32_t data) {
    // Ensure LEDs are set as outputs before writing data
    GPIO_PORTF_DATA_R = data;
}

void LED_SetColor(distance) {
    if (distance >= 5) {
        MCAL_GPIO_SetPinValue(GPIO_PORTF, RED_LED, GPIO_HIGH);
        MCAL_GPIO_SetPinValue(GPIO_PORTF, YELLOW_LED, GPIO_LOW);
        MCAL_GPIO_SetPinValue(GPIO_PORTF, GREEN_LED, GPIO_LOW);

    } else if (distance > 0) {
        MCAL_GPIO_SetPinValue(GPIO_PORTF, RED_LED, GPIO_LOW);
        MCAL_GPIO_SetPinValue(GPIO_PORTF, YELLOW_LED, GPIO_HIGH);
        MCAL_GPIO_SetPinValue(GPIO_PORTF, GREEN_LED, GPIO_LOW);

    } else {
        MCAL_GPIO_SetPinValue(GPIO_PORTF, RED_LED, GPIO_LOW);
        MCAL_GPIO_SetPinValue(GPIO_PORTF, YELLOW_LED, GPIO_LOW);
        MCAL_GPIO_SetPinValue(GPIO_PORTF, GREEN_LED, GPIO_HIGH);
    }
}


