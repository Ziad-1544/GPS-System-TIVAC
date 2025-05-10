////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  MCAL           /////////
/////                GPIO              /////////
////                Version:3.0       /////////
///         DATE:   5-10-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_Private.h"
#include "GPIO_Config.h"

typedef struct {
    u32 GPIODATA;
    u32 Non_Usable[254];        //for all combination of pins but nvm we will use only last one
    u32 GPIO_WRITE_DATA;        //that is the last one 
    u32 GPIODIR;
    u32 GPIOIS;                 // Interrupt Sense
    u32 GPIOIBE;                // Interrupt Both Edges
    u32 GPIOIEV;                // Interrupt Event
    u32 GPIOIM;                 // Interrupt Mask
    u32 GPIORIS;                // Raw Interrupt Status
    u32 GPIOMIS;                // Masked Interrupt Status
    u32 GPIOICR;                // Interrupt Clear
    u32 GPIOAFSEL;
    u32 Non_Usable3[59]; 
    u32 GPIOPUR;                //pull up
    u32 GPIOPDR;                //pull down
    u32 GPIOSLR;                //slew rate 
    u32 GPIODEN;
    u32 GPIOLOCK;
    u32 GPIOCR;                 //commit register
    u32 GPIOAMSEL;
    u32 GPIOPCTL;               //port control
} GPIO_PORT_t;



typedef enum {
    GPIO_PULL_DOWN = 0,
    GPIO_PULL_UP 
} GPIO_RESTYPE_t;

typedef enum {
    GPIO_UNLOCKED = 0,
    GPIO_LOCKED 
} GPIO_LOCKFLAG_t;

typedef enum {
    GPIO_SLEW_RATE_DISABLE = 0,
    GPIO_SLEW_RATE_ENABLE 
} GPIO_SLEWRATE_t;

typedef enum {
    GPIO_CURRENT_2MA = 0,
    GPIO_CURRENT_4MA = 1,
    GPIO_CURRENT_8MA = 2
} GPIO_CURRENTVAL_t;

typedef struct {
    // GPIO_CURRENTVAL_t currentVal;    // 2mA=0, 4mA=1, 8mA=2
    GPIO_RESTYPE_t resType;             // Pull-down=0, Pull-up=1
    GPIO_LOCKFLAG_t lockFlag;           // 0=unlocked, 1=locked
    GPIO_SLEWRATE_t slewRate;           // 0=disabled, 1=enabled
} GPIO_PadConfig_t;

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

STD_ERROR GPIO_StdErrorInit(u32 Copy_u32Port);
STD_ERROR GPIO_StdErrorSetPinDir(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinDir);
STD_ERROR GPIO_StdErrorSetPortDir(u32 Copy_u32Port, u8 Copy_u8DirValue);
STD_ERROR GPIO_StdErrorWritePin(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinValue);
STD_ERROR GPIO_StdErrorReadPin(u32 Copy_u32Port, u8 Copy_u8PinId, u8* Copy_u8PinReturnValue);
STD_ERROR GPIO_StdErrorWritePort(u32 Copy_u32Port, u8 Copy_u8Copy_u8PortValue);
STD_ERROR GPIO_StdErrorReadPort(u32 Copy_u32Port, u8* Copy_ptru8ReturnValue);
STD_ERROR GPIO_StdErrorSetPinAlternateFunction(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinValue, u8 Copy_u8AltFunc);
STD_ERROR GPIO_StdErrorPinAnalogModeSelect(u32 Copy_u32Port, u8 Copy_u8PinId, u8 Copy_u8PinValue);
STD_ERROR GPIO_StdErrorSetPinPadConfig(u32 Copy_u32Port, u8 Copy_u8PinId, GPIO_PadConfig_t* Copy_PtrGPIO_PadConfig_tConfig);
STD_ERROR GPIO_stdErrorInterruptConfig(u32 Copy_u32Port, u8 Copy_u8PinId,u8 Copy_u8ICR,u8 Copy_u8IS,u8 Copy_u8MIS,u8 Copy_u8IBE,u8 Copy_u8IEV);

//STD_ERROR GPIO_PinCommit(u32 Port, u8 Copy_PinId, u8 Copy_Value);
//STD_ERROR GPIO_PinDigitalEnable(u32 Port, u8 Copy_PinId, u8 Copy_Value);

#endif







// STD_ERROR GPIO_WriteMaskedPins(u32 Port, u8 Copy_Value, u8 Copy_Mask);
// STD_ERROR GPIO_ReadMaskedPins(u32 Port, u8 Copy_Mask, u8* Copy_ReturnValue);
