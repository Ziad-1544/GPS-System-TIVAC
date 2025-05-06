//////////////////////////////////////////////////////////////////
////////        Ain Shams University                    /////////
///////       Intro To Embedded Project                /////////
//////            Layer:  MCAL                        /////////
/////                UART                            /////////
////            Version: 2                         /////////
///          DATE:   4-30-2025                     /////////
//        AUTHOR: Ahmad Ayman , Hussein Bahaa     /////////
//////////////////////////////////////////////////////////

#ifndef UART_PRVT_H
#define UART_PRVT_H
#include "../../LIB/STD/STD_TYPES.h"
#include "UART_interface.h"



#define UARTSystemClock 48000000.0

#define UART_LCRH_PENBIT 1 // Bit n1 in LCRH register is the PEN (Parity Enable) bit
#define UART_LCRH_EVENORODDBIT 2 // Bit n2 chooses between even or odd parity (EPS)
#define UART_LCRH_STPBIT 3 // Bit n3 chooses between one or two stop bits (STP)
#define UART_LCRH_FENBIT 4 // FIFO Enable bit

#define UART_CTL_ENABLEBIT 0 // bit 0 of CTL register is the enable bit
#define UART_CTL_TXEBIT 8 // bit 8 of CTL register is the transmission enable bit (TXE)
#define UART_CTL_RXEBIT 9 // bit 9 of CTL register is the receive enable bit (RXE)

#define UART_FR_TXFFBIT 5 // Transmission FIFO is full bit
#define UART_FR_RXFEBIT 4 // Receive FIFO is empty

#define UART_PR_UART0 0
#define UART_PR_UART1 1
#define UART_PR_UART2 2
#define UART_PR_UART3 3
#define UART_PR_UART4 4
#define UART_PR_UART5 5
#define UART_PR_UART6 6
#define UART_PR_UART7 7






#define UART_RCC_ENABLE_BASE_ADDRESS       0x400FE618 //UART clock enable register
#define UART_PRUART_BASE_ADDRESS           0x400FEA18


#define UART0_BASE_ADDRESS                      0x4000C000
#define UART1_BASE_ADDRESS                      0x4000D000
#define UART2_BASE_ADDRESS                      0x4000E000
#define UART3_BASE_ADDRESS                      0x4000F000
#define UART4_BASE_ADDRESS                      0x40010000
#define UART5_BASE_ADDRESS                      0x40011000
#define UART6_BASE_ADDRESS                      0x40012000
#define UART7_BASE_ADDRESS                      0x40013000

#define UART_LCRH_WLEN_5        0x00000000  //  5 bits (default)
#define UART_LCRH_WLEN_6        0x00000020  // 6 bits
#define UART_LCRH_WLEN_7        0x00000040  // 7 bits
#define UART_LCRH_WLEN_8        0x00000060  // 8 bits


#define UART0 ((UART_TYPE_t *) UART0_BASE_ADDRESS)
#define UART1 ((UART_TYPE_t *) UART1_BASE_ADDRESS)
#define UART2 ((UART_TYPE_t *) UART2_BASE_ADDRESS)
#define UART3 ((UART_TYPE_t *) UART3_BASE_ADDRESS)
#define UART4 ((UART_TYPE_t *) UART4_BASE_ADDRESS)
#define UART5 ((UART_TYPE_t *) UART5_BASE_ADDRESS)
#define UART6 ((UART_TYPE_t *) UART6_BASE_ADDRESS)
#define UART7 ((UART_TYPE_t *) UART7_BASE_ADDRESS)
#define UARTEnable (*((volatile u32 *) (UART_RCC_ENABLE_BASE_ADDRESS)))
#define UARTReady (*((volatile u32 *) UART_PRUART_BASE_ADDRESS))

//static STD_ERROR UART_StdRcc( UART_CONFIG_t *Copy_ptrConfig); // No need for declaring the prototype first in private, just defining the function in .c is enough.


#endif


