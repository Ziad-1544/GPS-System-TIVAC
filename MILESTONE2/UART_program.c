//////////////////////////////////////////////////////////////////
////////        Ain Shams University                    /////////
///////       Intro To Embedded Project                /////////
//////            Layer:  MCAL                        /////////
/////                UART                            /////////
////            Version:1.2                         /////////
///          DATE:   4-24-2025                     /////////
//        AUTHOR: Ahmad Ayman , Hussein Bahaa     /////////
//////////////////////////////////////////////////////////

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "UART_interface.h"



static STD_ERROR UART_StdErrorRcc( UART_CONFIG_t *Copy_ptrConfig){
    STD_ERROR Local_FunctionStatus = NOK;

    if(Copy_ptrConfig->Module == UART0){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 0);
        GPIO_StdErrorInit(PortA);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortA, PIN0, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortA, PIN1, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortA, PIN0, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortA, PIN1, 0);
        // Waiting for the Peripheral Ready register to be ready for access
        while(GET_BIT(UARTReady, UART_PR_UART0) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART1){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 1);
        GPIO_StdErrorInit(PortB);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortB, PIN0, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortB, PIN1, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortB, PIN0, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortB, PIN1, 0);

        while(GET_BIT(UARTReady, UART_PR_UART1) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART2){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 2);
        GPIO_StdErrorInit(PortD);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortD, PIN6, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortD, PIN7, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortD, PIN6, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortD, PIN7, 0);

        while(GET_BIT(UARTReady, UART_PR_UART2) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART3){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 3);
        GPIO_StdErrorInit(PortC);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortC, PIN6, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortC, PIN7, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortC, PIN6, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortC, PIN7, 0);

        while(GET_BIT(UARTReady, UART_PR_UART3) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART4){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 4);
        GPIO_StdErrorInit(PortC);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortC, PIN4, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortC, PIN5, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortC, PIN4, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortC, PIN5, 0);

        while(GET_BIT(UARTReady, UART_PR_UART4) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART5){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 5);
        GPIO_StdErrorInit(PortE);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortE, PIN0, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortE, PIN1, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortE, PIN0, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortE, PIN1, 0);

        while(GET_BIT(UARTReady, UART_PR_UART5) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART6){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 6);
        GPIO_StdErrorInit(PortD);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortD, PIN4, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortD, PIN5, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortD, PIN4, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortD, PIN5, 0);

        while(GET_BIT(UARTReady, UART_PR_UART6) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else if(Copy_ptrConfig->Module == UART7){
        // Enable Clocks for GPIO and UART
        SET_BIT(UARTEnable, 7);
        GPIO_StdErrorInit(PortE);
        
        //Disable UART
        CLR_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);

        // Initialize GPIO
        GPIO_StdErrorSetPinAlternateFunction(PortE, PIN0, PIN_ON, 1);
        GPIO_StdErrorSetPinAlternateFunction(PortE, PIN1, PIN_ON, 1);
        GPIO_StdErrorPinAnalogModeSelect(PortE, PIN0, 0);
        GPIO_StdErrorPinAnalogModeSelect(PortE, PIN1, 0);

        while(GET_BIT(UARTReady, UART_PR_UART7) == 0){
            Local_FunctionStatus = NOK;
        }
        Local_FunctionStatus = OK;
        return Local_FunctionStatus;
    }
    else {
        Local_FunctionStatus = NOK;
    }
    return Local_FunctionStatus;
}

STD_ERROR UART_StdErrorInit(UART_CONFIG_t *Copy_ptrConfig){
    STD_ERROR Local_FunctionStatus = OK;
    
		f32 Local_f32ClockDivisor ; // pre-define for KEIL 4 error handling
		UART_StdErrorRcc(Copy_ptrConfig);
    
    // Setting Up Baud Rate
    Local_f32ClockDivisor = (UARTSystemClock) / (16 * Copy_ptrConfig->BaudRate); // Known formula for calculating Baud Rate

    Copy_ptrConfig->Module->IBRD = (u32)Local_f32ClockDivisor; // Type casting the Local_f32ClockDivisor to remove the decimal
    Copy_ptrConfig->Module->FBRD = (u32)(((Local_f32ClockDivisor - (u32)Local_f32ClockDivisor)*64) + 0.5); // Known formula

    // Parity
    if (Copy_ptrConfig->ParOnOff == ParityEnable){ // Checking if Parity is enabled
        SET_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_PENBIT);
        if(Copy_ptrConfig->Parity == OddParity){ // If OddParity
            CLR_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_EVENORODDBIT); // Clearing the 2nd bit of LCRH register sets it to odd parity
        }
        else { // If EvenParity
            SET_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_EVENORODDBIT); // Enabling the 2nd bit of LCRH register sets it to even parity
        }
    } else if(Copy_ptrConfig->ParOnOff == ParityDisable){ 
        CLR_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_PENBIT); // Disable parity (1st bit of LCRH Register is cleared)
        
    }
    else {
        return Local_FunctionStatus = NOK;
    }
    
    // Data Bits
    CLR_BIT(Copy_ptrConfig->Module->LCRH, 5);
    CLR_BIT(Copy_ptrConfig->Module->LCRH, 6); // Clearing the WLEN bits for appropriate logic
    Copy_ptrConfig->Module->LCRH |= Copy_ptrConfig->DataBits; // LCRH || DataBits Mask

    // Stop Bits
    if (Copy_ptrConfig->StopBits == OneStopBit){
        CLR_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_STPBIT);
    } 
    else if(Copy_ptrConfig->StopBits == TwoStopBit){
        SET_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_STPBIT);
    } 
    else { return Local_FunctionStatus = NOK; }

    // Enable FIFO
    SET_BIT(Copy_ptrConfig->Module->LCRH, UART_LCRH_FENBIT);

    // Enable UART and set it to Dual mode (Set RXE and TXE and ENABLE bit of CTL register to 1)
    SET_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_ENABLEBIT);
    SET_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_TXEBIT);
    SET_BIT(Copy_ptrConfig->Module->CTL, UART_CTL_RXEBIT); // Enabling both RXE and TXE bits enables dual mode where you can send/receive

    return Local_FunctionStatus;
}

STD_ERROR UART_StdErrorSendByte(UART_CONFIG_t *Copy_ptrConfig, u8 Copy_u8Data){
    STD_ERROR Local_FunctionStatus = NOK;

    while(IS_BIT_SET(Copy_ptrConfig->Module->FR, UART_FR_TXFFBIT)){ // Checks if Transmit FIFO is full or not, if full then infinite loop, exit loop when empty
    };

    Local_FunctionStatus = OK;
    Copy_ptrConfig->Module->DR = Copy_u8Data;
    return Local_FunctionStatus;
}

STD_ERROR UART_StdErrorReceiveByte(UART_CONFIG_t *Copy_ptrConfig, u8 *Copy_ptru8Data){
    STD_ERROR Local_FunctionStatus = NOK;

    while(IS_BIT_SET(Copy_ptrConfig->Module->FR, UART_FR_RXFEBIT)) {};

    Local_FunctionStatus = OK;
    *Copy_ptru8Data = (Copy_ptrConfig->Module->DR & 0x000000FF); // BITWISE AND
    return Local_FunctionStatus;
}
