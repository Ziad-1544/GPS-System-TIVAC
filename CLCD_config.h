/*
----->Layer:  HAL
----->SWC:    LCD
----->DATE:   12-4-200
----->VERSION:V1.0.0
----->AUTHOR: Randa Ayman    
*/

#ifndef CLCD_CONFIG_h_
#define CLCD_CONFIG_h_

#include "CLCD_private.h"

//Options: PortA PortB PortC PortD PortE PortF
#define DATA_PORT   PortC
#define CTRL_PORT   PortD
//Options: PIN0 PIN1 PIN2 PIN3 PIN4 PIN5 PIN6 PIN7
#define RS          PIN2
#define RW          PIN1
#define ENA         PIN0
//options: CURSOR_OFF  CURSOR_ON
#define CURSOR_MODE CURSOR_OFF


//#define RS  0x01  
//#define EN  0x04 

#endif
