/*
 * lcd.h
 *
 *  Created on: Dec 28, 2021
 *      Author: abhijeet
 */

#ifndef LCD_H_
#define LCD_H_


#include <stdint.h>
#include <stdbool.h>
#include "driverlib.h"
#include "helper_functions.h"
#include <stdio.h>

// LCD DATA/COMMAND modes
#define LCD_COMMAND 0
#define LCD_DATA 1

// LCD Dimensions
#define LENGTH 84
#define WIDTH 48
#define Y_MAX_BYTES 6

// Time
#define DELAY 700000
#define EYE_DELAY 70000
#define BLOCK_DELAY 12000

// Assigning pins
#define PIN_LCD_RESET GPIO_PIN0
#define PIN_LCD_MODE GPIO_PIN4
#define PIN_LCD_SCE GPIO_PIN2

void lcd_init();
void create_block(uint8_t pattern);
void delete_block();
void clear_screen();
void set_x(uint16_t cood);
void set_y(uint16_t cood);
void test_write();

#endif /* LCD_H_ */
