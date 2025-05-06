////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                GPIO              /////////
////                Version:1.1       /////////
///         DATE:   4-7-2025         /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "../../LIB/STD/STD_TYPES.h"
#include "../../LIB/BITMATH/BIT_MATH.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"

typedef struct {
    u32 GPIODATA;
    u32 Non_Usable[254]; //for all combination of pins but nvm we will use only last one
    u32 GPIO_WRITE_DATA; //that is the last one 
    u32 GPIODIR;
    u32 Non_Usable2[7];  //interrupts 
    u32 GPIOAFSEL;
    u32 Non_Usable3[59]; 
    u32 GPIOPUR;  //pull up
    u32 GPIOPDR;  //pull down
    u32 GPIOSLR;  //slew rate 
    u32 GPIODEN;
    u32 GPIOLOCK;
    u32 GPIOCR;   //commit register
    u32 GPIOAMSEL;
    u32 GPIOPCTL; //port control
} GPIO_PORT_t;

typedef struct {
    // GPIO_CurrentVal_t currentVal;  // 2mA=0, 4mA=1, 8mA=2
    GPIO_ResType_t resType;     // Pull-down=0, Pull-up=1
    GPIO_LockFlag_t lockFlag;    // 0=unlocked, 1=locked
    GPIO_SlewRate_t slewRate;      // 0=disabled, 1=enabled
} GPIO_PadConfig_t;
// typedef enum {
//     GPIO_CURRENT_2MA = 0,
//     GPIO_CURRENT_4MA = 1,
//     GPIO_CURRENT_8MA = 2
// } GPIO_CurrentVal_t;

typedef enum {
    GPIO_PULL_DOWN = 0,
    GPIO_PULL_UP 
} GPIO_ResType_t;

typedef enum {
    GPIO_UNLOCKED = 0,
    GPIO_LOCKED = 1
} GPIO_LockFlag_t;

typedef enum {
    GPIO_SLEW_RATE_DISABLE = 0,
    GPIO_SLEW_RATE_ENABLE = 1
} GPIO_SlewRate_t;

//USED FOR BOTH LOCK & COMMIT PORT & ENABLE
#define PORT_OFF 0X00
#define PORT_ON 0XFF

#define PORT_INPUT 0X00
#define PORT_OUTPUT 0XFF
//USED FOR PIN COMMIT & ENABLE & AFSEL-PC & AMSEL
#define PIN_OFF 0
#define PIN_ON 1

#define PIN_LOW 0  
#define PIN_HIGH 1 

#define PIN_INPUT 0  
#define PIN_OUTPUT 1 

#define PortA 0
#define PortB 1
#define PortC 2
#define PortD 3
#define PortE 4
#define PortF 5

#define PIN0 0   
#define PIN1 1   
#define PIN2 2   
#define PIN3 3   
#define PIN4 4   
#define PIN5 5   
#define PIN6 6   
#define PIN7 7      

STD_ERROR GPIO_INIT(u32 Port);
STD_ERROR GPIO_SetPinDir(u32 Port, u8 Copy_PinId, u8 Copy_PinDir);
STD_ERROR GPIO_WritePin(u32 Port, u8 Copy_PinId, u8 Copy_PinValue);
STD_ERROR GPIO_ReadPin(u32 Port, u8 Copy_PinId, u8* Copy_PinReturnValue);
STD_ERROR GPIO_SetPortDir(u32 Port, u8 Copy_DirValue);
STD_ERROR GPIO_WritePort(u32 Port, u8 Copy_Value);
STD_ERROR GPIO_ReadPort(u32 Port, u8* Copy_ReturnValue);
STD_ERROR GPIO_SetPinAlternateFunction(u32 Port, u8 Copy_PinId, u8 Copy_Value, u8 Copy_AltFunc);
STD_ERROR GPIO_SetPinPadConfig(u32 Port, u8 Copy_PinId, GPIO_PadConfig_t* Copy_Config);
//STD_ERROR GPIO_PinCommit(u32 Port, u8 Copy_PinId, u8 Copy_Value);
//STD_ERROR GPIO_PinDigitalEnable(u32 Port, u8 Copy_PinId, u8 Copy_Value);
STD_ERROR GPIO_PinAnalogModeSelect(u32 Port, u8 Copy_PinId, u8 Copy_Value);

#endif







// STD_ERROR GPIO_WriteMaskedPins(u32 Port, u8 Copy_Value, u8 Copy_Mask);
// STD_ERROR GPIO_ReadMaskedPins(u32 Port, u8 Copy_Mask, u8* Copy_ReturnValue);
