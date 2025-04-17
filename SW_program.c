#include "SW_interface.h"
#include "SW_private.h"
#include "SW_config.h"

void SW_Init(void)
{
    SYSCTL_RCGCGPIO_R |= (1 << 3);                   // Enable clock for Port D (bit 3)
    while ((SYSCTL_PRGPIO_R & (1 << 3)) == 0);       // Wait till Port D is ready

    // No unlock needed for PD0 or PD4
    GPIO_PORTD_DIR_R &= ~(SW1_BIT | SW2_BIT);        // Set PD4 and PD0 as inputs
    GPIO_PORTD_PUR_R |= (SW1_BIT | SW2_BIT);         // Enable internal pull-up resistors
    GPIO_PORTD_DEN_R |= (SW1_BIT | SW2_BIT);         // Enable digital function
}

// Read both switches and return their states (active-low logic)
u8 SW_input(void)
{
    return GPIO_PORTD_DATA_R & (SW1_BIT | SW2_BIT);  // Return 0x10, 0x01, or both 0x11
}
