//////////////////////////////////////////////////////////////////
////////        Ain Shams University                    /////////
///////       Intro To Embedded Project                /////////
//////            Layer:  MCAL                        /////////
/////                UART                            /////////
////            Version:1.1                         /////////
///          DATE:   4-2-2025                      /////////
//        AUTHOR: Ahmad Ayman , Hussein Bahaa     /////////
//////////////////////////////////////////////////////////

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "UART_private.h"
#include "UART_config.h"
#include "STD_TYPES.h"

typedef enum{
    DataBits5 = UART_LCRH_WLEN_5, // 5 data bits
    DataBits6 = UART_LCRH_WLEN_6, // 6 data bits
    DataBits7 = UART_LCRH_WLEN_7,  // 7 data bits 
    DataBits8 = UART_LCRH_WLEN_8 // 8 data bits
} UART_DataBit;

typedef enum{
    OneStopBit, // Only one stop bit
    TwoStopBit  // 2 stop bits
} UART_StopBits;

typedef enum{
    ParityDisable,
    ParityEnable

} UART_ParityOnOff;

typedef enum{
    OddParity,
    EvenParity
} UART_Parity;


typedef struct{
    volatile u32 DR;  // UART data register
    union 
    {
        volatile u32 RSR;  // Error clear / Receive status
        volatile u32 ECR;  // Error clear / Receive status
    }UART_StatusReg; /*NAMING THE UNION IS MANDATORY IN KEIL 4*/
    
    volatile u32 reserve[4];
    volatile u32 FR;  // UART Flag Register
    volatile u32 ILPR; // IrDA Low Power Register
    volatile u32 IBRD; // Integer Baud-Rate Register
    volatile u32 FBRD; // Fraction Baud-Rate Register
    volatile u32 LCRH; // Line Control Register
    volatile u32 CTL; // Control Register
} UART_Type;

typedef struct{
    UART_Type *Module; // UARTnum (e.g. UART0, UART1, UART2 -> UART7)
    UART_DataBit DataBits; // How many data bits we are using (Choose: 1) DataBits5 2) DataBits6 3) DataBits7 4) DataBits8 )
    UART_StopBits StopBits; // How many stop bits (1 or 2)
    UART_ParityOnOff ParOnOff; // Disable or Enable Parity
    UART_Parity Parity; // Even or Odd Parity
    u32 BaudRate; 
    
} UARTConfig;


STD_ERROR UART_INIT(UARTConfig *config); // Initialize and define the struct before calling the fn
STD_ERROR UART_SendByte(UARTConfig *config, u8 data); 
STD_ERROR UART_ReceiveByte(UARTConfig *config, u8 *ptr_u8Data);




#endif
