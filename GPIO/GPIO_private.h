////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                GPIO              /////////
////                Version:2.0       /////////
///         DATE:   4-25-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_
#include"GPIO_interface.h"

#define GPIO_PORTA_BASE_ADDRESS 0x40004000
#define GPIO_PORTB_BASE_ADDRESS 0x40005000
#define GPIO_PORTC_BASE_ADDRESS 0x40006000
#define GPIO_PORTD_BASE_ADDRESS 0x40007000
#define GPIO_PORTE_BASE_ADDRESS 0x40024000
#define GPIO_PORTF_BASE_ADDRESS 0x40025000
#define GPIO_RCC_ENABLE_BASE_ADDRESS (0x400FE608)
#define GPIO_RCC_READY_FOR_ACCESS_ADDRESS (0x400FEA08)
#define GPIO_PORTF_DATA_R (*((volatile u32 *)0x400253FC))

#define LOCK_VALUE 0x4C4F434BU



#define GPIO_PORTA ((volatile GPIO_PORT_t *)(GPIO_PORTA_BASE_ADDRESS))
#define GPIO_PORTB ((volatile GPIO_PORT_t *)(GPIO_PORTB_BASE_ADDRESS))
#define GPIO_PORTC ((volatile GPIO_PORT_t *)(GPIO_PORTC_BASE_ADDRESS))
#define GPIO_PORTD ((volatile GPIO_PORT_t *)(GPIO_PORTD_BASE_ADDRESS))
#define GPIO_PORTE ((volatile GPIO_PORT_t *)(GPIO_PORTE_BASE_ADDRESS))
#define GPIO_PORTF ((volatile GPIO_PORT_t *)(GPIO_PORTF_BASE_ADDRESS))
#define GPIO_ENABLE (*((volatile u32 *)(GPIO_RCC_ENABLE_BASE_ADDRESS))) 
#define GPIO_WAIT (*((volatile u32 *)(GPIO_RCC_READY_FOR_ACCESS_ADDRESS)))


static STD_ERROR GPIO_StdErrorPortUnlock(u32 Copy_u32Port, u8 Copy_u8PortValue);
static STD_ERROR GPIO_StdErrorPortCommit(u32 Copy_u32Port, u8 Copy_u8PortValue);
static STD_ERROR GPIO_StdErrorPortDigitalEnable(u32 Copy_u32Port, u8 Copy_u8PortValue);
#endif 
