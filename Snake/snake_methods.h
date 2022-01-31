/*
 * snake_methods.h
 *
 *  Created on: Jan 7, 2022
 *      Author: abhijeet
 */

#ifndef SNAKE_METHODS_H_
#define SNAKE_METHODS_H_

#include "lcd.h"
#include "stdlib.h"

typedef enum {
    up,
    down,
    left,
    right
}directions;

// Snake block definition
typedef struct block_definition {
   uint16_t block_x;
   uint16_t block_y;
   directions block_direction;
   struct block_definition *next_block;
}block_t;

/* Adding Snake blocks
    * Add snake blocks, draw snake movement is in 1 direction
        * added blocks stay 1 coordinate behind previous one
    * add changing directions
        * on direction change in head block; direction change should happen in each block when they reach the axis where direction changed
*/

#define SNAKE_SIZE 4
uint8_t snake_block_add();
uint8_t move_snake_block(uint16_t *x,uint16_t *y, directions direction);
uint8_t slither(directions direction);
#define STEADY 255
#endif /* SNAKE_METHODS_H_ */
