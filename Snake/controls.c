/*
 * controls.c
 *
 *  Created on: Dec 8, 2021
 *      Author: abhijeet
 */

#include "controls.h"

extern uint8_t press_right; // button pressed variable

void buttons_init(){
    /* Configuring P1.0 and P2.1 as output and P1.1 and P1.4 (switch) as input */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // Red Led
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1); // Green Led

    /* Configuring P1.1 and P1.4 as an input and enabling interrupts */
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);

    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    MAP_Interrupt_enableInterrupt(INT_PORT1);
}

/* GPIO ISR */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    /* Toggling the output on the LED */
    if(status & GPIO_PIN1)
    {
        // Turn left
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        press_right = 0;
    }
    if(status & GPIO_PIN4)
    {
        // Turn Right
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1);
        press_right = 1;
    }
}
