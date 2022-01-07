/*
 * lcd.c
 *
 *  Created on: Dec 28, 2021
 *      Author: abhijeet
 */
#include "lcd.h"

static void init_lcdpins(){
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, PIN_LCD_MODE); // LCD Data/Command pin
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, PIN_LCD_MODE); // Setting it high because it goes LOW on its own for some reason
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P5, PIN_LCD_SCE); // LCD Chip select pin /SCE
}

static void lcd_command(uint8_t lcd_mode, uint8_t command){
    if(lcd_mode == LCD_COMMAND)
    {
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, PIN_LCD_MODE);
    }
    else if(lcd_mode == LCD_DATA)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, PIN_LCD_MODE);
    }

    GPIO_setOutputLowOnPin(GPIO_PORT_P5, PIN_LCD_SCE); // SPI transactions are read only when SCE is low

    while (!(SPI_getInterruptStatus(EUSCI_B0_BASE,EUSCI_B_SPI_TRANSMIT_INTERRUPT)));
    SPI_transmitData(EUSCI_B0_BASE, command); /* Transmitting data to slave */

    GPIO_setOutputHighOnPin(GPIO_PORT_P5, PIN_LCD_SCE); // If not set high LCD waits for more bytes
}

static void reset_lcd(){
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P5, PIN_LCD_RESET); // LCD reset pin
    // pull reset pin low
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, PIN_LCD_RESET);
    /*
     * It takes 6ns for the reset pin to go low then high
     * According to datasheet min time required for reset is 100us and max 100ms
     */
    // push reset pin high
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, PIN_LCD_RESET);
}

// Set contrast can set the LCD Vop to a value between 0 and 127.
// 40-60 is usually a pretty good range.
static void set_contrast(uint8_t contrast)
{
    lcd_command(LCD_COMMAND,0x21); //Tell LCD that extended commands follow
    lcd_command(LCD_COMMAND,0x80 | contrast); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
    lcd_command(LCD_COMMAND,0x20); //Set display mode
}

void set_x(uint16_t cood){
    lcd_command(LCD_COMMAND, cood | 0x80);
}

void set_y(uint16_t cood){
    lcd_command(LCD_COMMAND, cood | 0x40);
}

void lcd_init(){
    reset_lcd();

    //TODO: add timer delay
    uint8_t i = 0;
    for(i=0;i<20;i++);

    init_lcdpins();

    lcd_command(LCD_COMMAND,0x21); // function set
    lcd_command(LCD_COMMAND,0xB0); // Set contrast LCD Vop
    lcd_command(LCD_COMMAND,0x04); // Set temp coeff
    lcd_command(LCD_COMMAND,0x14); // LCD bias mode 1:48 (try 0x13)
    lcd_command(LCD_COMMAND,0x20); // We must send 0x20 before modifying the display control mode
    lcd_command(LCD_COMMAND,0x0C); // Set display control, normal mode
//    lcd_command(LCD_COMMAND,0x09); // Turn the whole display on
    set_contrast(60);
    set_x(0); // set X to 0
    set_y(0); // set Y to 0
}

void clear_screen(){
    uint16_t i;

    for(i = 0; i < (LENGTH * WIDTH)/8; i++)
    {
        lcd_command(LCD_DATA, 0x0);
    }
}

void create_block(uint8_t pattern)
{
    uint8_t x = 0;

    // using horizontal addressing
    for(x = 0; x < 4; x++){
       delay(BLOCK_DELAY);
       lcd_command(LCD_DATA, pattern);
    }
}

// Function to make a weird test figure
void test_write(){
    delay(DELAY);
    clear_screen();
    delay(DELAY);
    lcd_command(LCD_DATA, 0xFF);
    lcd_command(LCD_DATA, 0x05);
    lcd_command(LCD_DATA, 0xFF);
}

