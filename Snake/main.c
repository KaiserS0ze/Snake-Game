/*
* Author: Abhijeet
* Date:   12/08/2021
******************************************************************************/
/* DriverLib Includes */

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include "controls.h"
#include "lcd.h"
#include "snake_methods.h"

/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
        EUSCI_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
        4000000,                                   // SMCLK = 4MHz
        4000000,                                    // SPICLK = 4MHz --> 3MHz Output
        EUSCI_B_SPI_MSB_FIRST,                     // MSB First
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
        EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};

//uint8_t write = 0;

// Extern variables
uint8_t press_right = STEADY; // button pressed variable
block_t snake_head;
block_t *snake_tail;

// Global variables
directions direction;
uint16_t x = 0;
uint16_t y = 0;


int main(void)
{
//    /* Halting the Watchdog */
      MAP_WDT_A_holdTimer();

      buttons_init(); // Initialise pins for switches

      // Configure pins for SPI
      GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

      /* Configuring SPI in 3wire master mode */
      SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);

      /* Enable SPI module */
      SPI_enableModule(EUSCI_B0_BASE);

      /* Enabling SRAM Bank Retention */
      MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1);

      /* Enabling MASTER interrupts */
      MAP_Interrupt_enableMaster();

      lcd_init();
      /*
       * Start by entering from left to right of screen
       * This is needed to set a reference direction
       * for what is left and right from the snake's POV
      */

      //TODO: Make Snake Initialisation Function
      direction = up;
      snake_head.block_x = 0;
      snake_head.block_y = 0;
      snake_head.subblock_y = 0;
      snake_head.block_direction = direction;
      snake_head.next_block = NULL;
      snake_tail = &snake_head;

      uint8_t i = 0;
      while (1)
      {
          switch(direction){
              case up:
                  //Y--
                  if(press_right == 1){
                      direction = right;
                  }
                  else if (press_right == 0){
                      direction = left;
                  }
                  press_right = STEADY;
                  break;
              case down:
                  // Y++
                  if(press_right == 1){
                      direction = left;
                  }
                  else if (press_right == 0){
                      direction = right;
                  }
                  press_right = STEADY;
                  break;
              case right:
                  // X++
                  if(press_right == 1){
                      direction = down;
                  }
                  else if (press_right == 0){
                      direction = up;
                  }
                  press_right = STEADY;
                  break;
              case left:
                  // X--
                  if(press_right == 1){
                      direction = up;
                  }
                  else if (press_right == 0){
                      direction = down;
                  }
                  press_right = STEADY;
                  break;
          }

            slither(direction);
            if(i<8) snake_block_add();
            i++;
      }
}

void SysTick_Handler(void)
{

}
