#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "UART_interface.h"
#include "SYSTICK_interface.h"
#include "LED_interface.h"
#include "CLCD_interface.h"
#include "SW_interface.h"


void TurnOffAllLeds(void);

int main(void){
    //initialize uart, gpio and leds

    UART_CONFIG_t uart0configuration;
    uart0configuration.Module = UART0;
    uart0configuration.DataBits = DataBits8;
    uart0configuration.StopBits = OneStopBit;
    uart0configuration.ParOnOff = ParityDisable;
    uart0configuration.Parity = OddParity; // doesnt matter already disabled
    uart0configuration.BaudRate = 9600;

    UART_StdErrorInit(&uart0configuration);

    LED_voidInitExternalLed(PortC, 4); // RED
    LED_voidInitExternalLed(PortC, 5); // GREEN
    LED_voidInitExternalLed(PortC, 6); // YELLOW

    u8 command;
    while(1){
        if(UART_StdErrorReceiveByte(&uart0configuration, &command) == OK){
            switch(command){
                case 'r': LED_voidTurnOnLed(PortC, 4); Systick_StdErrorDelayIn_ms(250); break;
                case 'g': LED_voidTurnOnLed(PortC, 5); Systick_StdErrorDelayIn_ms(250); break;
                case 'y': LED_voidTurnOnLed(PortC, 6); Systick_StdErrorDelayIn_ms(250); break;
                case 'o': TurnOffAllLeds(); Systick_StdErrorDelayIn_ms(250); break;
            }
        }
    }

}


void TurnOffAllLeds(void){
    LED_voidTurnOffLed(PortC, 4);
    LED_voidTurnOffLed(PortC, 5);
    LED_voidTurnOffLed(PortC, 6);
}