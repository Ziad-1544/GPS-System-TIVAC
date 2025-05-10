//////////////////////////////////////////////////////////////////
////////        Ain Shams University                    /////////
///////       Intro To Embedded Project                /////////
//////            Layer:  MCAL                        /////////
/////                UART                            /////////
////            Version:3.0                         /////////
///          DATE:   5-10-2025                     /////////
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
} UART_DATABITS_t;

typedef enum{
    OneStopBit, // Only one stop bit
    TwoStopBit  // 2 stop bits
} UART_STOPBITS_t;

typedef enum{
    ParityDisable,
    ParityEnable

} UART_PARITYONOFF_t;

typedef enum{
    OddParity,
    EvenParity
} UART_PARITY_t;


typedef struct{
    volatile u32 DR;        // UART data register
    union {
        volatile u32  ECR;                    /*!< UART Receive Status/Error Clear                                       */
        volatile u32  RSR;                   /*!< UART Receive Status/Error Clear                                       */
    }STATUS_REG_t;
    volatile u32 reserve[4];
    volatile u32 FR;    // UART Flag Register
    volatile u32 reserve1;
    volatile u32 ILPR;  // IrDA Low Power Register
    volatile u32 IBRD;  // Integer Baud-Rate Register
    volatile u32 FBRD;  // Fraction Baud-Rate Register
    volatile u32 LCRH;  // Line Control Register
    volatile u32 CTL;   // Control Register
} UART_TYPE_t;

typedef struct{
    UART_TYPE_t *Module;            // UARTnum (e.g. UART0, UART1, UART2 -> UART7)
    UART_DATABITS_t DataBits;       // How many data bits we are using (Choose: 1) DataBits5 2) DataBits6 3) DataBits7 4) DataBits8 )
    UART_STOPBITS_t StopBits;       // How many stop bits (1 or 2)
    UART_PARITYONOFF_t ParOnOff;    // Disable or Enable Parity
    UART_PARITY_t Parity;           // Even or Odd Parity
    u32 BaudRate; 
    
} UART_CONFIG_t;


STD_ERROR UART_StdErrorInit(UART_CONFIG_t *Copy_ptrConfig); // Initialize and define the struct before calling the fn
STD_ERROR UART_StdErrorSendByte(UART_CONFIG_t *Copy_ptrConfig, u8 Copy_u8Data); 
STD_ERROR UART_StdErrorReceiveByte(UART_CONFIG_t *Copy_ptrConfig, u8 *Copy_ptru8Data);




#endif
