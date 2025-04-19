////////////////////////////////////////////////////
///////      Ain Shams University         /////////
//////     Intro To Embedded Project     /////////
/////           Layer:  MCAL            /////////
////                GPIO               /////////
///         DATE:   16-3-2025         /////////
//         AUTHOR: Hussein Bahaa     /////////
/////////////////////////////////////////////   


#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_
#include "BIT_MATH_V1.0.h"
#include "STD_TYPES_V1.0.h"


#define GPIO_LOCK_VALUE 0x4C4F434B

typedef struct {
    u32 GPIODATA;
    u32 Non_Usable_Space[254] ;
    u32 GPIO_WRITE_DATA;
    u32 GPIODIR;
    u32 Non_Usable_Space2[7] ;
    u32 GPIOAFSEL;
    u32 Non_Usable_Space3[59] ;
    u32 GPIOPUR;
    u32 GPIOPDR;
    u32 GPIOSLR;
    u32 GPIODEN;
    u32 GPIOLOCK;
    u32 GPIOCR;
    u32 GPIOAMSEL;
    u32 GPIOPCTL;
}GPIO_REGISTERES;

 
 
#define GPIO_LOW 0  /**< GPIO Low value */
#define GPIO_HIGH 1 /**< GPIO High value */

 
#define GPIO_PIN_INPUT 0  /**< GPIO INPUT value */
#define GPIO_PIN_OUTPUT 1 /**< GPIO OUTPUT value */


typedef enum {PortA,PortB,PortC,PortD,PortE,PortF}
        Port;

#define GPIO_PIN0 0   /**< GPIO Pin 0 */
#define GPIO_PIN1 1   /**< GPIO Pin 1 */
#define GPIO_PIN2 2   /**< GPIO Pin 2 */
#define GPIO_PIN3 3   /**< GPIO Pin 3 */
#define GPIO_PIN4 4   /**< GPIO Pin 4 */
#define GPIO_PIN5 5   /**< GPIO Pin 5 */
#define GPIO_PIN6 6   /**< GPIO Pin 6 */
#define GPIO_PIN7 7   /**< GPIO Pin 7 */
#define GPIO_PIN8 8   /**< GPIO Pin 8 */
#define GPIO_PIN9 9   /**< GPIO Pin 9 */
#define GPIO_PIN10 10 /**< GPIO Pin 10 */
#define GPIO_PIN11 11 /**< GPIO Pin 11 */
#define GPIO_PIN12 12 /**< GPIO Pin 12 */
#define GPIO_PIN13 13 /**< GPIO Pin 13 */
#define GPIO_PIN14 14 /**< GPIO Pin 14 */
#define GPIO_PIN15 15 /**< GPIO Pin 15 */


#define GPIO_INPUT_PULL_DOWN_MOD 0 /**< GPIO Input Pull down Mode */
#define GPIO_INPUT_PULL_UP_MOD 1   /**< GPIO Input Pull up Mode */


/**
 * @defgroup GPIO_Functions GPIO Functions
 * @brief GPIO functions for controlling GPIO pins.
 * @{
 */

/**
 * @brief Sets the mode of a GPIO pin.
 *
 * This function sets the mode of a specified GPIO pin.
 *
 * @param[in] Copy_PortId The ID of the GPIO port (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @param[in] Copy_PinId The ID of the GPIO pin (e.g., GPIO_PIN0, GPIO_PIN1, etc.).
 * @param[in] Copy_PinDir The Direct'ion of pin either it is  input or output
 * @param[in] Copy_PinMode The desired mode for the GPIO pin like pull up or pull down for inputs.
 * @return Std_ReturnType Returns E_OK if the operation was successful, or E_NOT_OK if an error occurred.
 */
Std_ReturnType MCAL_GPIO_SetPinMode( GPIO_REGISTERES* Copy_PortId, u8 Copy_PinId, u8 Copy_PinDir,u8 Copy_PinMode) ;


Std_ReturnType MCAL_GPIO_SetPinValue(GPIO_REGISTERES* Copy_PortId, u8 Copy_PinId, u8 Copy_PinValue);


Std_ReturnType MCAL_GPIO_GetPinValue(GPIO_REGISTERES* Copy_PortId, u8 Copy_PinId, u8 *Copy_PinReturnValue);


Std_ReturnType MCAL_GPIO_INIT(u32 Port,GPIO_REGISTERES* Copy_PortId) ;




#endif /**< GPIO_INTERFACE_H_ */