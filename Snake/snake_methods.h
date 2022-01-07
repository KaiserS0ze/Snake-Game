/*
 * snake_methods.h
 *
 *  Created on: Jan 7, 2022
 *      Author: abhijeet
 */

#ifndef SNAKE_METHODS_H_
#define SNAKE_METHODS_H_

#include "lcd.h"

typedef enum {
    up,
    down,
    left,
    right
}directions;

uint8_t add_snake_block(uint16_t *x,uint16_t *y, directions direction);
#endif /* SNAKE_METHODS_H_ */
