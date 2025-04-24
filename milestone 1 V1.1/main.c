
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "SYSTICK_interface.h"
#include "LED_interface.h"
#include "SW_interface.h"
#include "CLCD_interface.h"

u8 CurrentLED = 0;
u8 SW2Pressed;
void ClearAllLeds(void);
void PowerOnAllLeds(void);
//MODES
void ManualMode(void);
void AutoToggleMode(void);
void BlinkMode(void);
void CounterMode(void);

void main(void){
    CLCD_StdErrorDataPinsInit();

    LED_VoidInitInternalLeds();

    SW_StdErrorInitInternal(Internal_SW1); 
    SW_StdErrorInitInternal(Internal_SW2); 
    
    u8 SW1Pressed ;
    u8 CurrentMode = 0;

    while(1){
        SW1Pressed = SW_u8InternalSWIsPressed(Internal_SW1); //Where isSW1Pressed fetches the status of switch 1
        Systick_StdErrorDelayIn_ms(200);
        if(SW1Pressed ){ // Assume SW1 is an active-high button
             CurrentMode = (CurrentMode+1) % 4; // Common method of making sure a variable doesn't exceed a certain number.
             
        }
        // Create functions for each mode
        switch(CurrentMode){ 
            case 0:
                ManualMode(); break;
            case 1:
                AutoToggleMode(); break;
            case 2: 
                BlinkMode(); break;
            case 3:
                CounterMode(); break;
        }
    }

}

void ManualMode(void){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(0,0);
    CLCD_voidDataSendString("Manual Mode");
    //int PreviousLED = 2; UNUSED THEREFORE COMMENTED
    SW2Pressed = SW_u8InternalSWIsPressed(Internal_SW2); //Where isSW2Pressed fetches the status of switch 2
    Systick_StdErrorDelayIn_ms(200);

    if(SW2Pressed == 1){

        switch(CurrentLED){ //ACCORDING TO CURRENTLED VALUE, TURN ON LED(VALUE) AND TURN OFF ALL OTHERS
            case 0: LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_ON); LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_OFF); LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_OFF);CLCD_voidDataSetCursor(1,0);CLCD_voidDataSendString("LED: 0");break;
            case 1: LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_OFF); LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_ON); LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_OFF);CLCD_voidDataSetCursor(1,0);CLCD_voidDataSendString("LED: 1");break;
            case 2: LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_OFF); LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_OFF); LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_ON);CLCD_voidDataSetCursor(1,0);CLCD_voidDataSendString("LED: 2");break;

        }

       // PreviousLED = CurrentLED; UNUSED THEREFORE COMMENTED

        CurrentLED = (CurrentLED+1) % 3; // Makes sure CurrentLed doesn't exceed 2 as we only have leds 0-2

        /* LCD UPDATING: SEND THRU CurrentMode VARIABLE WHICH SHOULD POINT TO ManualMode AND PASS CurrentLed VALUE WHICH SHOULD POINT TO EL LEDAYA EL MENAWARA */ 
        Systick_StdErrorDelayIn_ms(1000);
    }
}

void AutoToggleMode(void){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(0,0);
    CLCD_voidDataSendString("Auto Toggle Mode");
    static u8 paused = 0; //paused flag
    SW2Pressed = SW_u8InternalSWIsPressed(Internal_SW2); 
    Systick_StdErrorDelayIn_ms(200);

    if(SW2Pressed ==1){
        paused = !paused; // Change the status of Pause flag for action button
    }
    if (paused){
        CLCD_voidDataSetCursor(1,0);
        CLCD_voidDataSendString("PAUSED");
        return;
    }else{
        CLCD_voidDataSetCursor(1,0);
        CLCD_voidDataSendString("RUNNING");
    }

    switch(CurrentLED){
        case 0: LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_ON);   break;
        case 1: LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_ON);  break;
        case 2: LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_ON); break;
        default: ClearAllLeds(); break;
    }
    CurrentLED = (CurrentLED +1) %4;
    Systick_StdErrorDelayIn_ms(1000);
}

void BlinkMode(void){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(0,0);
    CLCD_voidDataSendString("Blink Mode");
    static u32 BlinkSpeed = 0 ; // Initialize variable BlinkSpeed
    u32 BlinkDelay; 
    // BlinkSpeed possible values = 0(slow), 1(medium), 2(fast)
    switch (BlinkSpeed)
    {
    case 0: BlinkDelay = 5000;CLCD_voidDataSetCursor(1,0);CLCD_voidDataSendString("Speed: Slow"); break;
    case 1: BlinkDelay = 3000;CLCD_voidDataSetCursor(1,0);CLCD_voidDataSendString("Speed: Medium"); break;
    case 2: BlinkDelay = 1000;CLCD_voidDataSetCursor(1,0);CLCD_voidDataSendString("Speed: Fast"); break;
    default:
        break;
    }
    // SW2Pressed = isSW2pressed();
    SW2Pressed=SW_u8InternalSWIsPressed(Internal_SW2);
    Systick_StdErrorDelayIn_ms(200);
    if (SW2Pressed)
    {
        BlinkSpeed = (BlinkSpeed+1) % 3;
    }
    
    //Turn on all LEDs then delay(BlinkDelay) then turn off all LEDs then delay(BlinkDelay)
    PowerOnAllLeds();
    Systick_StdErrorDelayIn_ms(BlinkDelay);
    ClearAllLeds();
    Systick_StdErrorDelayIn_ms(BlinkDelay);

}

void CounterMode(void){
    CLCD_VoidClearDisplay();
    CLCD_voidDataSetCursor(0,0);
    CLCD_voidDataSendString("Counter Mode");
    SW2Pressed = SW_u8InternalSWIsPressed(Internal_SW2); 
    Systick_StdErrorDelayIn_ms(200);
    static u8 counter;
    static u8 led1_status = 0;
    static u8 led2_status = 0;
    static u8 led3_status = 0;
    counter =counter+1;
    if(SW2Pressed){
        counter = 0;
    }
    led1_status = counter & 1;
    if(led1_status){
        LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_ON);
    }
    else {
        LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_OFF);
    }
    led2_status=counter & 0b10;
    if(led2_status){
        LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_ON);
    }
    else {
        LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_OFF);
    }
    led3_status=counter & 0b100;
    if(led3_status){
        LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_ON);
    }
    else {
        LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_OFF);
    }
    
    Systick_StdErrorDelayIn_ms(1000);
}

void ClearAllLeds(void){
    LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_OFF); LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_OFF); LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_OFF);

}
void PowerOnAllLeds(void){
    LED_StdErrorSetInternalLedValue(RED_LED_PIN, LED_ON); LED_StdErrorSetInternalLedValue(BLUE_LED_PIN, LED_ON); LED_StdErrorSetInternalLedValue(GREEN_LED_PIN, LED_ON);

}
