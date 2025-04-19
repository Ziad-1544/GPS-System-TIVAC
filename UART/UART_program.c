//////////////////////////////////////////////////////////////////
////////        Ain Shams University                    /////////
///////       Intro To Embedded Project                /////////
//////            Layer:  MCAL                        /////////
/////                UART                            /////////
////            Version:1.0                         /////////
///          DATE:   4-19-2025                     /////////
//        AUTHOR: Ahmad Ayman , Hussein Bahaa     /////////
//////////////////////////////////////////////////////////

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "UART_interface.h"
#include "GPIO_Interface.h"


static STD_ERROR UARTGPIO_CC( UARTConfig *config){
    STD_ERROR Local_FunctionStatus = NOK;

    if(config->Module == UART0){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 0);
        GPIO_INIT(PortA);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortA, PIN0, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortA, PIN1, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortA, PIN0, 0);
        GPIO_PinAnalogModeSelect(PortA, PIN1, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART1){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 1);
        GPIO_INIT(PortB);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortB, PIN0, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortB, PIN1, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortB, PIN0, 0);
        GPIO_PinAnalogModeSelect(PortB, PIN1, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART2){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 2);
        GPIO_INIT(PortD);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortD, PIN6, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortD, PIN7, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortD, PIN6, 0);
        GPIO_PinAnalogModeSelect(PortD, PIN7, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART3){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 3);
        GPIO_INIT(PortC);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortC, PIN6, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortC, PIN7, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortC, PIN6, 0);
        GPIO_PinAnalogModeSelect(PortC, PIN7, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART4){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 4);
        GPIO_INIT(PortC);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortC, PIN4, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortC, PIN5, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortC, PIN4, 0);
        GPIO_PinAnalogModeSelect(PortC, PIN5, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART5){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 5);
        GPIO_INIT(PortE);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortE, PIN0, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortE, PIN1, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortE, PIN0, 0);
        GPIO_PinAnalogModeSelect(PortE, PIN1, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART6){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 6);
        GPIO_INIT(PortD);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortD, PIN4, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortD, PIN5, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortD, PIN4, 0);
        GPIO_PinAnalogModeSelect(PortD, PIN5, 0);
        return Local_FunctionStatus = OK;
    }
    else if(config->Module == UART7){
        // Enable Clocks for GPIO and UART
        UARTEnable |= SET_BIT(UARTEnable, 7);
        GPIO_INIT(PortE);
        
        //Disable UART
        CLR_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_SetPinAlternateFunction(PortE, PIN0, PIN_ON, 1);
        GPIO_SetPinAlternateFunction(PortE, PIN1, PIN_ON, 1);
        GPIO_PinAnalogModeSelect(PortE, PIN0, 0);
        GPIO_PinAnalogModeSelect(PortE, PIN1, 0);
        return Local_FunctionStatus = OK;
    }
    else {
        Local_FunctionStatus = NOK;
    }
    return Local_FunctionStatus;
}

STD_ERROR UART_INIT(UARTConfig *config){
    STD_ERROR Local_FunctionStatus = OK;
    UARTGPIO_CC(config);
    
    // Setting Up Baud Rate
    f32 ClockDivisor = (UARTSystemClock) / (16 * config->BaudRate); // Known formula for calculating Baud Rate

    config->Module->IBRD = (u32)ClockDivisor; // Type casting the clockdivisor to remove the decimal
    config->Module->FBRD = (u32)(((ClockDivisor - (u32)ClockDivisor)*64) + 0.5); // Known formula

    // Parity
    if (config->ParOnOff == ParityEnable){ // Checking if Parity is enabled
        SET_BIT(config->Module->LCRH, UART_LCRH_PENBIT);
        if(config->Parity == OddParity){ // If OddParity
            CLR_BIT(config->Module->LCRH, UART_LCRH_EVENORODDBIT); // Clearing the 2nd bit of LCRH register sets it to odd parity
        }
        else { // If EvenParity
            SET_BIT(config->Module->LCRH, UART_LCRH_EVENORODDBIT); // Enabling the 2nd bit of LCRH register sets it to even parity
        }
    } else if(config->ParOnOff == ParityDisable){ 
        CLR_BIT(config->Module->LCRH, UART_LCRH_PENBIT); // Disable parity (1st bit of LCRH Register is cleared)
        
    }
    else {
        return Local_FunctionStatus = NOK;
    }
    
    // Data Bits
    CLR_BIT(config->Module->LCRH, 5);
    CLR_BIT(config->Module->LCRH, 6); // Clearing the WLEN bits for appropriate logic
    config->Module->LCRH |= config->DataBits; // LCRH || DataBits Mask

    // Stop Bits
    if (config->StopBits == OneStopBit){
        CLR_BIT(config->Module->LCRH, UART_LCRH_STPBIT);
    } 
    else if(config->StopBits == TwoStopBit){
        SET_BIT(config->Module->LCRH, UART_LCRH_STPBIT);
    } 
    else { return Local_FunctionStatus = NOK; }

    // Enable FIFO
    SET_BIT(config->Module->LCRH, UART_LCRH_FENBIT);

    // Enable UART and set it to Dual mode (Set RXE and TXE and ENABLE bit of CTL register to 1)
    SET_BIT(config->Module->CTL, UART_CTL_ENABLEBIT);
    SET_BIT(config->Module->CTL, UART_CTL_TXEBIT);
    SET_BIT(config->Module->CTL, UART_CTL_RXEBIT); // Enabling both RXE and TXE bits enables dual mode where you can send/receive

    return Local_FunctionStatus;
}

STD_ERROR UART_SendByte(UARTConfig *config, u8 data){
    STD_ERROR Local_FunctionStatus = NOK;

    while(IS_BIT_SET(config->Module->FR, UART_FR_TXFFBIT)){ // Checks if Transmit FIFO is full or not, if full then infinite loop, exit loop when empty
    };

    Local_FunctionStatus = OK;
    config->Module->DR = data;
    return Local_FunctionStatus;
}

STD_ERROR UART_ReceiveByte(UARTConfig *config, u8 *ptr_u8Data){
    STD_ERROR Local_FunctionStatus = NOK;

    while(IS_BIT_SET(config->Module->FR, UART_FR_RXFEBIT)) {};

    Local_FunctionStatus = OK;
    *ptr_u8Data = (config->Module->DR && 0x000000FF);
    return Local_FunctionStatus;
}