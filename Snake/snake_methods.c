/*
 * snake_methods.c
 *
 *  Created on: Jan 7, 2022
 *      Author: abhijeet
 */

#include "snake_methods.h"

extern block_t snake_head;
extern block_t *snake_tail;
uint8_t num_nodes = 0;

uint8_t snake_block_add(){
    static uint16_t max_length = 0;

    if(max_length == ((LENGTH*WIDTH)/(1 << SNAKE_SIZE))){
        return 1;
    }

    block_t *new_block = (block_t*)malloc(sizeof(block_t));

    if(new_block == NULL){
        return 1;
    }

    new_block->block_direction = snake_tail->block_direction;
    new_block->block_x = snake_tail->block_x;
    new_block->block_y = snake_tail->block_y;
    new_block->subblock_y = snake_tail->subblock_y;
    new_block->next_block = NULL;

    snake_tail->next_block = new_block; // previously added node now points to new node
    snake_tail = new_block; // the new node is now the snake_tail
    max_length = max_length + 1;
    num_nodes = num_nodes + 1;
    return 0;
}

uint8_t move_snake_block(uint16_t *x, uint16_t *y, uint16_t *virtual_y, directions direction)
{
    uint8_t pattern = 0; // check this
//    static uint8_t virtual_y = 0;

    bool vertical;

    // X and Y have to stay within LCD limits
    *y = *y % Y_MAX_BYTES;
    *virtual_y = *virtual_y % (8/SNAKE_SIZE);

    *x = *x % (LENGTH - (SNAKE_SIZE - 1));

    if(*virtual_y%2 == 0){
        pattern = 0x0F;
    }
    else{
        pattern = 0xF0;
    }

    set_x(*x);
    set_y(*y);

    delay(EYE_DELAY);
    create_block(pattern);

    switch(direction){
        case up:

                if(*virtual_y) {
                    *virtual_y = *virtual_y - 1;
                }
                else{ // if virtual_y is 0
                    *virtual_y = ((8/SNAKE_SIZE) - 1);

                    if(*y){
                        *y = *y -1;
                    }
                    else{ // *y == 0
                        *y = Y_MAX_BYTES -1;
                    }
                }
                vertical = true;
            break;
        case down:
                if(*virtual_y == ((8/SNAKE_SIZE) - 1)) *y = *y + 1; // Only update real y after we have moved through all the sub-blocks
                *virtual_y = *virtual_y + 1;
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

    return 0;
}

uint8_t slither(directions direction){

    static uint8_t node_changed = 0;
    uint8_t counter = 0;

    block_t *traverse = &snake_head;

    do{ // Iterate through snake LL at least once

//        if(counter == node_changed){
//            traverse->block_direction = direction;
//        }

        traverse->block_direction = direction;

        move_snake_block(&traverse->block_x, &traverse->block_y, &traverse->subblock_y, traverse->block_direction);

        if(traverse == &snake_head && traverse->next_block == NULL) break; // if snake has only one block break the loop

        traverse = traverse->next_block;
        counter = counter + 1;


    }
    while(traverse->next_block != NULL); // keep iterating through the LL till we don't reach the tail

    clear_screen();

    traverse=&snake_head;
    node_changed = node_changed + 1;

    if(node_changed == num_nodes){
        node_changed = 0;
    }

    return 0;
}
