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
	u8 command;
	UART_CONFIG_t uart0configuration;
		
	GPIO_StdErrorInit(PortA);
	GPIO_StdErrorInit(PortB);
		
   
    uart0configuration.Module = UART4;
    uart0configuration.DataBits = DataBits8;
    uart0configuration.StopBits = OneStopBit;
    uart0configuration.ParOnOff = ParityDisable;
    uart0configuration.Parity = OddParity; // doesnt matter already disabled
    uart0configuration.BaudRate = 9600;

    UART_StdErrorInit(&uart0configuration);

    LED_voidInitExternalLed(PortA, 7); // RED
    LED_voidInitExternalLed(PortA, 5); // GREEN
    LED_voidInitExternalLed(PortA, 6); // YELLOW

    CLCD_StdErrorDataPinsInit();
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(LINE_1,0);
    CLCD_voidDataSendString("Milestone 2");
    CLCD_voidDataSetCursor(LINE_2,0);
    while(1){
        if(UART_StdErrorReceiveByte(&uart0configuration, &command) == OK){
            switch(command){
                case 'r': LED_voidTurnOnLed(PortA, 7); Systick_StdErrorDelayIn_ms(500); break;
                case 'y': LED_voidTurnOnLed(PortA, 5); Systick_StdErrorDelayIn_ms(500); break;
                case 'g': LED_voidTurnOnLed(PortA, 6); Systick_StdErrorDelayIn_ms(500); break;
                case 'o': TurnOffAllLeds(); Systick_StdErrorDelayIn_ms(1000); break;
             }
            TurnOffAllLeds();
            CLCD_StdErrorSendData(command);
        }
    }

}


void TurnOffAllLeds(void){
    LED_voidTurnOffLed(PortA, 7);
    LED_voidTurnOffLed(PortA, 5);
    LED_voidTurnOffLed(PortA, 6);
}
