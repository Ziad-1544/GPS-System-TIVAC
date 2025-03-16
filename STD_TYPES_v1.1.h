////////////////////////////////////////////////////
///////      Ain Shams University         /////////
//////     Intro To Embedded Project     /////////
/////           Layer:  LIB             /////////
////        Standard Types (STD)       /////////
///         DATE:   16-3-2025         /////////
//         AUTHOR: Jessica Samuel    /////////
/////////////////////////////////////////////   

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long int u64;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef signed long long int s64;

typedef float f32;
typedef double f64;

typedef enum {
    NOK = 0,
    OK  = 1
} STD_ERROR;

#define NULL ((void*)0)

#endif

