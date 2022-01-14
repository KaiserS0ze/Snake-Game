/*
 * snake_methods.c
 *
 *  Created on: Jan 7, 2022
 *      Author: abhijeet
 */

#include "snake_methods.h"

extern block_t snake_head;
extern block_t *snake_tail;

uint8_t snake_block_add(){

    block_t *new_block = (block_t*)malloc(sizeof(block_t));

    if(new_block == NULL){
        return 1;
    }

    new_block->block_direction = snake_tail->block_direction;
    new_block->block_x = snake_tail->block_x;
    new_block->block_y = snake_tail->block_y;
    new_block->next_block = NULL;

    snake_tail->next_block = new_block; // previously added node now points to new node
    snake_tail = new_block; // the new node is now the snake_tail

    return 0;
}

uint8_t move_snake_block(uint16_t *x,uint16_t *y, directions direction)
{
    uint8_t pattern = 0x0F; // check this
    static uint8_t virtual_y = 0;

    bool vertical;

    // X and Y have to stay within LCD limits
    *y = *y % Y_MAX_BYTES;
    virtual_y = virtual_y % (Y_MAX_BYTES * (8/SNAKE_SIZE));
    *x = *x%81;

    set_x(*x);
    set_y(*y);

    delay(EYE_DELAY);
//    clear_screen(); // TODO: This is okay for 1 block but, it won't work with multiple blocks
    create_block(pattern);

    switch(direction){
        case up:
                if(*y){
                    *y = *y -1;
                    virtual_y = virtual_y - 1;
                }
                else{
                    *y = Y_MAX_BYTES -1;
                }
                if(!virtual_y) virtual_y = (Y_MAX_BYTES * (8/SNAKE_SIZE)) - 1;
                vertical = true;
            break;
        case down:
                *y = *y + 1;
                virtual_y = virtual_y + 1;
                vertical = true;
            break;
        case right:
                *x = *x + 4;
                vertical = false;
            break;
        case left:
                if(*x){
                    *x = *x - 4;
                }
                else{
                    *x = 80;
                }
                vertical = false;
            break;
    }

    if(vertical == true) { // While going up/down X needs to remain constant
        if(virtual_y%2 == 0){
            pattern = 0x0F;
        }
        else{
            pattern = 0xF0;
        }

        set_x(*x);
        if(direction == up) set_y(*y); // need to switch Y to move pattern upwards
        create_block(pattern); // We switch from 0xF0 to 0x0F
        if(direction == down) virtual_y = virtual_y + 1;
        if(direction == up) virtual_y = virtual_y - 1;
    }

    return 0;
}
