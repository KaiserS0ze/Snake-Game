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

#define LCD_COMMAND 0
#define LCD_DATA 1


// Assigning pins

#define PIN_LCD_RESET GPIO_PIN0
#define PIN_LCD_MODE GPIO_PIN4
#define PIN_LCD_SCE GPIO_PIN2

void lcd_init();
void test_write();

#endif /* LCD_H_ */
