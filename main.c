#include <string.h> // for string functions
#include <float.h> // For max value of f64
#include "COTS/LIB/STD/STD_TYPES.h"
#include "COTS/MCAL/GPIO/GPIO_interface.h"  
#include "COTS/MCAL/UART/UART_interface.h"
#include "COTS/HAL/CLCD/CLCD_interface.h"
#include "COTS/HAL/SW/SW_interface.h"
#include "COTS/HAL/LED/LED_interface.h"
#include "COTS/MCAL/EEPROM/EEPROM_interface.h"
#include "COTS/MCAL/GPIO_INT/INT_interface.h"
#include "APP.h"

//Global Variables:
SavedLocations_t Database[14]={
    {"GATE_6", 30.064906, 31.280339},
    {"MOSQUE", 30.064526, 31.280305},
    {"HALLA&B", 30.064190, 31.280488},
    {"HALLC&D", 30.063835, 31.280481},
    {"LUPAN", 30.063349, 31.279324},
    {"CREDIT", 30.063974, 31.278607},
    {"GATE3", 30.063871, 31.277879},
    {"Civil_Bldng", 30.064411, 31.277856},
    {"Fountain", 30.065529, 31.278456},
    {"SAWTIAT", 30.065780, 31.279853},
    {"Library", 30.065296, 31.280117},
    {"GYM", 30.064474, 31.278700},
    {"MODRAGAT", 30.064172, 31.279108},
    {"Football_Field", 30.063810, 31.279489}
};
ClosestPlace_t CurrentLoc, NearestLoc;
f64 Global_f64GPSLat,Global_f64GPSLong;
u32 Global_u32EEPROM_Addresses;
u32 Global_u32TimesVisited;
f64 Global_f64TimeUTC;
u8  Global_u8TimeNow[8];
u32 Global_u32location; // LOOP ITERATOR
UART_CONFIG_t Global_uart2configuration;

//Time visited Report Variables:
u32 Global_u32visits;
u8  i; // LOOP ITERATOR

//Slide Show Variables:
u8 Global_u8SlideElement;
f64 Global_f64SlideShowDistance;
        

//Functions Prototypes
void TimeVisitedReport(void);

int main (){   

    Global_uart2configuration.Module = UART2;
    Global_uart2configuration.DataBits = DataBits8;
    Global_uart2configuration.StopBits = OneStopBit;
    Global_uart2configuration.ParOnOff = ParityDisable;
    Global_uart2configuration.Parity = OddParity; // doesnt matter already disabled
    Global_uart2configuration.BaudRate = 9600; 

    PeripheralsInit();
    GPIO_StdErrorWritePin(PortF, PIN2,PIN_LOW);
    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1,0);
    CLCD_VoidDataSendString("Welcome Back..");
    CLCD_VoidDataSetCursor(LINE_2,0);
    CLCD_VoidDataSendString("Press To start");
    Systick_StdErrorDelayIn_ms(2000);
    
    INT_voidFunc(PortE,PIN3,&TimeVisitedReport);     

    while(1){
        //Main Functionality 
        if(SW_u8ExternalSWIsPressed(PortC,PIN6)){
            //Intializing Variables:
           strcpy(NearestLoc.name, "ZIAD");
           NearestLoc.name[sizeof(NearestLoc.name)-1] = '\0'; // Ensure null termination
           NearestLoc.distance=DBL_MAX;

   
           TurnOffAllLeds();
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString("Please Wait...");
   
   
           GPS_stdStatusWaitForValidData(&Global_uart2configuration,&Global_f64GPSLat,&Global_f64GPSLong,&Global_f64TimeUTC, 10);
   
            for(Global_u32location = 0; Global_u32location < 14; Global_u32location++){
   
               CurrentLoc.distance=GPS_f64GetDistance_ArgInDegrees(Global_f64GPSLat,Global_f64GPSLong,Database[Global_u32location].Lat,Database[Global_u32location].Long);
               StringCopy(CurrentLoc.name, Database[Global_u32location].name, sizeof(CurrentLoc.name) - 1);
   
               if ((CurrentLoc.distance < NearestLoc.distance) /*&& (CurrentLoc.distance < MAX_DISTANCE_THRESHOLD)*/) {
                   NearestLoc.distance = CurrentLoc.distance;
                   StringCopy(NearestLoc.name, Database[Global_u32location].name, sizeof(NearestLoc.name) - 1);
                   Global_u32EEPROM_Addresses = Global_u32location;
               }
           }

           ConvertUTCtoLocalTime(Global_f64TimeUTC,Global_u8TimeNow);
           EEPROM_TimesVisitedIncrement(Global_u32EEPROM_Addresses);

           // CLCD Prints Current Time
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString("Current Time: ");
           CLCD_VoidDataSetCursor(LINE_2, 0);
           CLCD_VoidDataSendString(Global_u8TimeNow);
           Systick_StdErrorDelayIn_ms(4000);

           // CLCD Prints Nearest loc & Distance in between 
           BuzzerTrigger();
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString(NearestLoc.name);
           CLCD_VoidDataSetCursor(LINE_2, 0);
           CLCD_VoidSendNum(NearestLoc.distance);
           CLCD_VoidDataSendString(" meters");
           Systick_StdErrorDelayIn_ms(4000);
   
           // CLCD Prints How many times did i visit this place before
           Global_u32TimesVisited = EEPROM_u32ReadData(Global_u32EEPROM_Addresses);
           CLCD_VoidClearDisplay();
           CLCD_VoidDataSetCursor(LINE_1, 0);
           CLCD_VoidDataSendString("Times Visited: ");
           CLCD_VoidSendNum(Global_u32TimesVisited);
           if (Global_u32TimesVisited > 0){
                CLCD_VoidDataSetCursor(LINE_2, 0);
                CLCD_VoidDataSendString("Missed You..");
           }else
           {
                CLCD_VoidDataSetCursor(LINE_2, 0);
                CLCD_VoidDataSendString("New Place..Nice");
           }
           
           
   
           //LED Handling For Distance Ranges
           if (NearestLoc.distance < GREEN_LED_THRESHOLD){ LED_voidTurnOnLed(PortA, PIN7); }
           else if (NearestLoc.distance < YELLOW_LED_THRESHOLD){LED_voidTurnOnLed(PortA, PIN6);}
           else{ LED_voidTurnOnLed(PortA, PIN5); }
        }
        
        //Slide Show Functionality 
        #if(SLIDE_SHOW_MODE == TURNED_ON)

            if(SW_u8ExternalSWIsPressed(PortC,PIN7)){
                Global_u8SlideElement=0;
                while (1)
                {
                    if(SW_u8ExternalSWIsPressed(PortC,PIN7)){
                        Global_u8SlideElement = (Global_u8SlideElement + 1) % 14;
                        CLCD_VoidClearDisplay();
                        CLCD_VoidDataSetCursor(LINE_1,0);
                        CLCD_VoidDataSendString("Choose a Place:");
                        CLCD_VoidDataSetCursor(LINE_2,0);
                        CLCD_VoidDataSendString(Database[Global_u8SlideElement].name);
                    }
                    if (SW_u8ExternalSWIsPressed(PortC,PIN5))
                    {
                       while(1){
                            GPS_stdStatusWaitForValidData(&Global_uart2configuration,&Global_f64GPSLat,&Global_f64GPSLong,&Global_f64TimeUTC, 10);
                            Global_f64SlideShowDistance=GPS_f64GetDistance_ArgInDegrees(Global_f64GPSLat,Global_f64GPSLong,Database[Global_u8SlideElement].Lat,Database[Global_u8SlideElement].Long);
                            CLCD_VoidClearDisplay();
                            CLCD_VoidDataSetCursor(LINE_1,0);
                            CLCD_VoidDataSendString(Database[Global_u8SlideElement].name);
                            CLCD_VoidDataSetCursor(LINE_2,0);
                            CLCD_VoidSendNum(Global_f64SlideShowDistance);
                            CLCD_VoidDataSendString(" meters");
                            Systick_StdErrorDelayIn_ms(500);
                            if (SW_u8ExternalSWIsPressed(PortC,PIN4)){
                                Global_u8SlideElement=0;
                                CLCD_VoidClearDisplay();
                                CLCD_VoidDataSetCursor(LINE_1,0);
                                CLCD_VoidDataSendString("Choose Another");
                                CLCD_VoidDataSetCursor(LINE_2,0);
                                CLCD_VoidDataSendString("Place");
                                break;
                            }
                       }
                    }
                
                    if (SW_u8ExternalSWIsPressed(PortC,PIN4)){
                        CLCD_VoidClearDisplay();
                        CLCD_VoidDataSetCursor(LINE_1,0);
                        CLCD_VoidDataSendString("Welcome Back..");
                        CLCD_VoidDataSetCursor(LINE_2,0);
                        CLCD_VoidDataSendString("Press To start");
                        break;
                    }
                }
            
            }
        #endif  
    }
}

void TimeVisitedReport(void){
    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1, 0);
    CLCD_VoidDataSendString("Times Visited:");

    for(i = 0; i < 14; i++) {
        // Get visit count for this Global_u32location from EEPROM
        Global_u32visits = EEPROM_u32ReadData(i);

        CLCD_VoidClearDisplay();
        CLCD_VoidDataSetCursor(LINE_1, 0);
        CLCD_VoidDataSendString(Database[i].name);
        CLCD_VoidDataSetCursor(LINE_2, 0);
        CLCD_VoidDataSendString("Visits: ");
        CLCD_VoidSendNum(Global_u32visits);

        // Wait for user to read before showing next Global_u32location
        Systick_StdErrorDelayIn_ms(2000);
    }

    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1, 0);
    CLCD_VoidDataSendString("Report Done");
    Systick_StdErrorDelayIn_ms(3000);
    CLCD_VoidClearDisplay();
    CLCD_VoidDataSetCursor(LINE_1,0);
    CLCD_VoidDataSendString("Press To start..");
}