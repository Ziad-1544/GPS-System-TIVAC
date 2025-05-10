/////////////////////////////////////////////////
//////////   Author: Mustafa ElSherif ///////////
//////////   Date: 24/4/2025          ///////////
//////////   Version: 1.0             ///////////
//////////   Description: Interrupt   ///////////
//////////   Configuration file       ///////////
//////////   For TivaC "TM4C123"      ///////////
/////////////////////////////////////////////////

#ifndef INT_CONFIG_H_
#define INT_CONFIG_H_



/* if you want your interrupt_sense in your port in edge state          PORTX_SENCE   -> EDGE 
and if you want your interrupt_sense in your port in level state        PORTX_SENCE   -> LEVEL 
*/

#define PORTA_SENSE  EDGE
#define PORTB_SENSE  EDGE
#define PORTC_SENSE  EDGE
#define PORTD_SENSE  EDGE
#define PORTE_SENSE  EDGE
#define PORTF_SENSE  LEVEL

/* if you want your interrupt_event in your port in (high / rising) state          PORTX_EVENT  -> HIGH 
and if you want your interrupt_event in your port in (low / falling) state        PORTX_EVENT   -> LOW 
*/

#define PORTA_EVENT  HIGH
#define PORTB_EVENT  HIGH
#define PORTC_EVENT  HIGH
#define PORTD_EVENT  HIGH
#define PORTE_EVENT  HIGH
#define PORTF_EVENT  HIGH

#endif
