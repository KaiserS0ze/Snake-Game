/*
 * snake_methods.c
 *
 *  Created on: Jan 7, 2022
 *      Author: abhijeet
 */

#include "snake_methods.h"

uint8_t add_snake_block(uint16_t *x,uint16_t *y, directions direction)
{
    static uint8_t pattern = 0x0F; // check this
    bool vertical;

    // X and Y have to stay within LCD limits
    *y = *y % Y_MAX_BYTES;

//    *x = *x%81 + ((*y)*LENGTH); // 81 because the block is 4 pixels wide + X changes according to the vertical bank it is in
    *x = *x%81;

    set_x(*x);
    set_y(*y);

    delay(EYE_DELAY);
    clear_screen(); // TODO: This is okay for 1 block but, it won't work with multiple blocks
    create_block(pattern);

    switch(direction){
        case up:

                if(*y){
                    *y = *y -1;
                }
                else{
                    *y = Y_MAX_BYTES -1;
                }
                pattern = pattern ^ 0xFF;
                vertical = true;
            break;
        case down:
                *y = *y + 1;
                pattern = pattern ^ 0xFF;
                vertical = true;
            break;
        case right:
                *x = *x + 1;
                vertical = false;
            break;
        case left:
                if(*x){
                    *x = *x - 1;
                }
                else{
                    *x = 80;
                }
                vertical = false;
            break;
    }

    if(vertical == true) { // While going up/down X needs to remain constant
        set_x(*x);
        create_block(pattern); // We switch from 0xF0 to 0x0F
        pattern = pattern ^ 0xFF;
    }

    return 0;
}
