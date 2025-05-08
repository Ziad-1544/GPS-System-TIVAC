////////////////////////////////////////////////////
////////      Ain Shams University        /////////
///////     Intro To Embedded Project    /////////
//////           Layer:  HAL            /////////
/////                GPS               /////////
////                Version:1.1       /////////
///         DATE:   4-30-2025        /////////
//         AUTHOR: Ziad Kassem      /////////
////////////////////////////////////////////
#ifndef GPS_PRIVATE_H_
#define GPS_PRIVATE_H_

#define PI 3.14159265358979323846
#define EARTH_RADIUS_M 6371000

//Size of arrays used 
#define MAX_SENTENCE_FIELDS 15
#define SENTENCE_SIZE 100

f64 GPS_CustomStringToFloat(u8 *str);

#endif 
