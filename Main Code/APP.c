#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "UART_interface.h"
#include "CLCD_interface.h"
#include "SW_interface.h"
#include "LED_interface.h"
#include "EEPROM_interface.h"
#include "INT_interface.h"
#include "APP.h"


void PeripheralsInit(void){
    UART_CONFIG_t uart2configuration; 
    
    uart2configuration.Module = UART2;
    uart2configuration.DataBits = DataBits8;
    uart2configuration.StopBits = OneStopBit;
    uart2configuration.ParOnOff = ParityDisable;
    uart2configuration.Parity = OddParity; // doesnt matter already disabled
    uart2configuration.BaudRate = 9600;

    //Switch Initialization
    GPIO_StdErrorInit(PortA);
	GPIO_StdErrorInit(PortB);
    GPIO_StdErrorInit(PortC);
    GPIO_StdErrorInit(PortD);

    //Switch Initialization
    SW_StdErrorInitExternal(PortC, PIN6);
    //SW_StdErrorInitExternal(PortC, PIN5);

    //Interrupt Switch For the Report
    //INT_voidPORTC_Enable(PIN5);

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
    GPIO_StdErrorSetPinDir(PortD, PIN0, PIN_OUTPUT);


}

void BuzzerTrigger(void){
    // Imperial March (Star Wars theme) ringtone
    u8 i;
    // First phrase
    for(i = 0; i < 2; i++) {
        // G note
        GPIO_StdErrorWritePin(PortD, PIN0, PIN_HIGH);
        Systick_StdErrorDelayIn_ms(300);
        GPIO_StdErrorWritePin(PortD, PIN0, PIN_LOW);
        Systick_StdErrorDelayIn_ms(100);
        
        // G repeat
        GPIO_StdErrorWritePin(PortD, PIN0, PIN_HIGH);
        Systick_StdErrorDelayIn_ms(300);
        GPIO_StdErrorWritePin(PortD, PIN0, PIN_LOW);
        Systick_StdErrorDelayIn_ms(100);
        
        // G repeat
        GPIO_StdErrorWritePin(PortD, PIN0, PIN_HIGH);
        Systick_StdErrorDelayIn_ms(300);
        GPIO_StdErrorWritePin(PortD, PIN0, PIN_LOW);
        Systick_StdErrorDelayIn_ms(100);
    }
    
    // Second phrase - lower note
    GPIO_StdErrorWritePin(PortD, PIN0, PIN_HIGH);
    Systick_StdErrorDelayIn_ms(200);
    GPIO_StdErrorWritePin(PortD, PIN0, PIN_LOW);
    Systick_StdErrorDelayIn_ms(50);
    
    // Higher note
    GPIO_StdErrorWritePin(PortD, PIN0, PIN_HIGH);
    Systick_StdErrorDelayIn_ms(400);
    GPIO_StdErrorWritePin(PortD, PIN0, PIN_LOW);
    Systick_StdErrorDelayIn_ms(100);
    
    // G finale
    GPIO_StdErrorWritePin(PortD, PIN0, PIN_HIGH);
    Systick_StdErrorDelayIn_ms(600);
    GPIO_StdErrorWritePin(PortD, PIN0, PIN_LOW);
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
