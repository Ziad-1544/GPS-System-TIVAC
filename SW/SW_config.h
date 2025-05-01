////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                SW                /////////
////                Version:2         /////////
///         DATE:   30-4-2025        /////////
//         AUTHOR: Randa Ayman      /////////
////////////////////////////////////////////

#ifndef SW_CONFIG_H
#define SW_CONFIG_H



// Internal switches (onboard)
//OPTIONS:GPIO_PULL_UP GPIO_PULL_DOWN
#define INTERNAL_SW_RES    GPIO_PULL_UP 



// External switches 
//OPTIONS:GPIO_PULL_UP GPIO_PULL_DOWN
#define EXTERNAL_SW_RES    GPIO_PULL_UP 

#endif
