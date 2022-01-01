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

// LCD DATA/COMMAND modes
#define LCD_COMMAND 0
#define LCD_DATA 1

// LCD Dimensions
#define LENGTH 84
#define WIDTH 48

// Time
#define DELAY 700000
#define EYE_DELAY 300000
#define BLOCK_DELAY 200000

// Assigning pins
#define PIN_LCD_RESET GPIO_PIN0
#define PIN_LCD_MODE GPIO_PIN4
#define PIN_LCD_SCE GPIO_PIN2

void lcd_init();
uint8_t add_snake_block(int16_t x,int16_t y);
void test_write();

#endif /* LCD_H_ */
