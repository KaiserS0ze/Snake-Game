/*
 * helper_functions.c
 *
 *  Created on: Dec 30, 2021
 *      Author: abhijeet
 */

#include "helper_functions.h"

void delay(uint32_t time){
    MAP_SysTick_enableModule();
    MAP_SysTick_setPeriod(time); // Ticks needed for 2 seconds period
    while(SysTick_getValue() != (time - 1));
}
