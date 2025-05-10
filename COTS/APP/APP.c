#include "../../LIB/STD/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"  
#include "../../MCAL/UART/UART_interface.h"
#include "../../HAL/CLCD/CLCD_interface.h"
#include "../../HAL/SW/SW_interface.h"
#include "../../HAL/LED/LED_interface.h"
#include "../../MCAL/EEPROM/EEPROM_interface.h"
#include "../../MCAL/GPIO_INT/INT_interface.h"
#include "APP.h"




void PeripheralsInit(void){
    UART_CONFIG_t uart2configuration; 
    GPIO_PadConfig_t GPIO_PF2;

    uart2configuration.Module = UART2;
    uart2configuration.DataBits = DataBits8;
    uart2configuration.StopBits = OneStopBit;
    uart2configuration.ParOnOff = ParityDisable;
    uart2configuration.Parity = OddParity; // doesnt matter already disabled
    uart2configuration.BaudRate = 9600;

 
    GPIO_PF2.resType = GPIO_PULL_DOWN; // Pull-down resistor
    GPIO_PF2.lockFlag = GPIO_UNLOCKED; // Unlocked
    GPIO_PF2.slewRate = GPIO_SLEW_RATE_DISABLE; // Slew rate enabled

    //Switch Initialization
    GPIO_StdErrorInit(PortA);
	GPIO_StdErrorInit(PortB);
    GPIO_StdErrorInit(PortC);
    GPIO_StdErrorInit(PortF);

    //Switch Initialization
    SW_StdErrorInitExternal(PortC, PIN4); //Slide Show "Exit" Button // bony
    SW_StdErrorInitExternal(PortC, PIN5); //Slide Show "Enter" Button // a5dar
    SW_StdErrorInitExternal(PortC, PIN6); //Main_Functionality //ahmar
    SW_StdErrorInitExternal(PortC, PIN7); //Slide Show turn on and choose location   // Azra2

    SW_StdErrorInitExternal(PortE, PIN3);

    //Interrupt Switch For the Report
    INT_voidPORTE_Enable(PIN3);

    //LED Initialization
    LED_voidInitExternalLed(PortA, PIN5); //RED LED
    LED_voidInitExternalLed(PortA, PIN6); // YELLOW LED
    LED_voidInitExternalLed(PortA, PIN7); // GREEN LED

    //CLCD Initialization
    CLCD_StdErrorDataPinsInit();

    //UART2 Initialization
    UART_StdErrorInit(&uart2configuration);

    //EEPROM Initialization
    EEPROM_STD_ERROR_Init();

    //Buzzer Initialization
    GPIO_StdErrorSetPinDir(PortF, PIN2, PIN_OUTPUT);
    GPIO_StdErrorSetPinPadConfig(PortF, PIN2, &GPIO_PF2); 


}

void BuzzerTrigger(void){
    
    u8 i;
    
    for(i = 0; i < 2; i++) {
        // G note
        GPIO_StdErrorWritePin(PortF, PIN2, PIN_HIGH);
        Systick_StdErrorDelayIn_ms(300);
        GPIO_StdErrorWritePin(PortF, PIN2, PIN_LOW);
        Systick_StdErrorDelayIn_ms(100);
    }
    GPIO_StdErrorWritePin(PortF, PIN2, PIN_HIGH);
    Systick_StdErrorDelayIn_ms(1000);
    GPIO_StdErrorWritePin(PortF, PIN2, PIN_LOW);
}

void TurnOffAllLeds(void){
    LED_voidTurnOffLed(PortA, 5); // red
    LED_voidTurnOffLed(PortA, 6); // yellow
    LED_voidTurnOffLed(PortA, 7); // green  
}

void EEPROM_TimesVisitedIncrement(u32 Copyu32_EEPROMAddresses){
    u32 Local_TimesVisited = EEPROM_u32ReadData(Copyu32_EEPROMAddresses);
    
    EEPROM_STD_ERROR_WriteData(Copyu32_EEPROMAddresses, ++Local_TimesVisited);

}


void ConvertUTCtoLocalTime(f64 utcTime, u8* timeStr) {
    // Extract hours, minutes, seconds
    u32 hours = (int)(utcTime / 10000);
    u32 minutes = (int)((utcTime - hours * 10000) / 100);
    u32 seconds = utcTime - hours * 10000 - minutes * 100;
    
    // Adjust to UTC+3
    hours += 3;
    if (hours >= 24) {
        hours -= 24;
    }
    
    // Format the time string as hh:mm:ss.ss
    timeStr[0] = (hours / 10) + '0';
    timeStr[1] = (hours % 10) + '0';
    timeStr[2] = ':';
    timeStr[3] = (minutes / 10) + '0';
    timeStr[4] = (minutes % 10) + '0';
    timeStr[5] = ':';
    timeStr[6] = (seconds / 10) + '0';
    timeStr[7] = (seconds % 10) + '0';
    timeStr[8] = '\0';
}

void StringCopy(u8 *destination, u8 *source, u8 maxLength) {
    u8 i;
    for (i = 0; i < maxLength && source[i] != '\0'; i++) {
        destination[i] = source[i];
    }
    // Null-terminate the destination string
    destination[i] = '\0';
}



