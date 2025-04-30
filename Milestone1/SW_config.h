////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                SW                /////////
////                Version:1.1       /////////
///         DATE:   20-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef SW_CONFIG_H
#define SW_CONFIG_H



// Internal switches (onboard)
#define SW_RES    GPIO_PULL_UP



// External switches (example on Port E)
#define EXT_SW1_PORT   PortD
#define EXT_SW1_PIN    PIN2
#define EXT_SW1_RES    GPIO_PULL_DOWN

#define EXT_SW2_PORT   PortD
#define EXT_SW2_PIN    PIN3
#define EXT_SW2_RES    GPIO_PULL_DOWN

#endif
