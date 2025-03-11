/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*
This is my attempt at converting the Adafruit_SH1106.h file obtained from:
into an equivelent header file for C purposes
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

/*
* SH1106 Display settings
* I am only using a 128x64 display for now
*/
#define SH1106_128_64

#if defined SH1106_128_64
  #define SH1106_LCDWIDTH                  128
  #define SH1106_LCDHEIGHT                 64
#endif

// SPI Configuration for Raspberry Pi RP2350
#define PICO    PICO_DEFAULT_SPI_TX_PIN
#define CS      PICO_DEFAULT_SPI_CSN_PIN
#define CLK     PICO_DEFAULT_SPI_SCK_PIN
#define POCI    PICO_DEFAULT_SPI_RX_PIN // DC pin on SH1106
#define RST     20 // GPIO20 on RP2350

#define SPI_PORT spi0
#define BAUD    (1 * (10^6))

/*
* @enum 
* @brief Enum to represent the initialization state of the SH1106 object.
*
*/
typedef enum 
{
    UNINIT = 0,     /**< object has passed through parameter initialzation */
    INIT = 1,       /**< object has setup SPI comm */
    CONFIGED = 2,   /**<  */
}SH1106_state;

/*
* Object that will hold configuration info for an SH1106 OLED 
*/
typedef struct Adafruit_SH1106_t
{
    uint8_t dc; /**< Data/Command: set 0: commands, set 1: data */
    uint8_t rst;
    uint8_t cs;
    uint8_t pico;
    uint8_t clk;
    SH1106_state init; // used to determine if ada struct initialized
}Adafruit_SH1106;

/*
* @brief Initializer function to create and initalize
* an Adafruit_SH1106 object
*
* @param dc, GPIO pin for Direct Comand
* @param rst, GPIO pin for SPI Reset
* @param cs, GPIO pin for 
* @param pico, GPIO pin for Controller Out Peripheral In
* @param clk, GPIO pin for clock
*
* @return Adafruit_SH1106*, pointer to object
*/
void init_Adafruit_SH1106(
    Adafruit_SH1106* ada,
    uint8_t dc, 
    uint8_t rst, 
    uint8_t cs,
    uint8_t pico,
    uint8_t clk
);

/*
* @brief Function used to initalize & configure SPI
*
* Configures SPI and utilizes the Adafruit_SH1106 object
* to initialize and configure the GPIO pins on the Pico2
*
* @param Adafruit_SH1106* ada, pointer to object that is initialized
*
* @return void
*/
void initialize_spi(Adafruit_SH1106* ada);

/*
* @brief Runs the power-up sequence for the SH1106.
*
* Following the power-up sequence from the Adafruit SH1106 documentation
* and code found on their github. This function should run after
* setting up SPI communication.
*
* @param ada, pointer to Adafruit_SH1106 that is already initialized 
*/
void begin_Adafruit_SH1106(Adafruit_SH1106* ada);

/*
* @brief Executes the powerup & setup sequence for the SH1106.
*
* These steps are taken from the Adafruit SH1106 doc & code
* examples.
*
* Pre-reqs: initialized SPI communication
*
* @param ada, Pointing to object that has been initialized.
*/
void configure_sh1106(Adafruit_SH1106* ada);
