/////////////////////////////////////////////////////
////////      Ain Shams University         /////////
///////     Intro To Embedded Project     /////////
//////           Layer:  LIB             /////////
/////        Bit Manipulation (BIT)     /////////
////         DATE:   10-5-2025         /////////
///         version:   1.3            /////////
//         AUTHOR: Jessica Samuel    /////////
/////////////////////////////////////////////  
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg, bit)    reg |= (1 << bit)
#define CLR_BIT(reg, bit)    reg &= ~(1 << bit)
#define TOG_BIT(reg, bit)    reg ^= (1 << bit)
#define GET_BIT(reg, bit)    ((reg & (1 << bit)) >> bit)
#define IS_BIT_SET(reg, bit) ((reg & (1 << bit)) != 0)  
#define IS_BIT_CLR(reg, bit) ((reg & (1 << bit)) == 0)

#endif
