#include "led.h"

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


