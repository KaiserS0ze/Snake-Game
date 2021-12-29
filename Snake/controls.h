/*
 * controls.h
 *
 *  Created on: Dec 8, 2021
 *      Author: abhijeet
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_


#include <stdint.h>
#include <stdbool.h>
#include "driverlib.h"

void buttons_init();
void PORT1_IRQHandler(void);

#endif /* CONTROLS_H_ */
