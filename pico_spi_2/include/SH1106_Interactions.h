/*
* Description:
* Header file for SH1106 initialization and usage.
* 
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include <u8g2/u8g2.h>

/*
* SH1106 Display settings
* I am only using a 128x64 display for now
*/
#define SH1106_128_64

#if defined SH1106_128_64
  #define WIDTH                  128
  #define HEIGHT                 64
#endif

// SPI Configuration for Raspberry Pi RP2350
#define PICO    PICO_DEFAULT_SPI_TX_PIN
#define CS      PICO_DEFAULT_SPI_CSN_PIN
#define CLK     PICO_DEFAULT_SPI_SCK_PIN
#define POCI    PICO_DEFAULT_SPI_RX_PIN // DC pin on SH1106
#define RST     20 // GPIO20 on RP2350

#define SPI_PORT    spi0
#define BAUD        (1000 * 1000)

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
typedef struct SH1106_t
{
    uint8_t dc; /**< Data/Command: set 0: commands, set 1: data */
    uint8_t rst;
    uint8_t cs;
    uint8_t pico;
    uint8_t clk;
    SH1106_state init; // used to determine if oled struct initialized
}SH1106;

/*
* @brief Initializer function to create and initalize
* an SH1106 object
*
* @param dc, GPIO pin for Direct Comand
* @param rst, GPIO pin for SPI Reset
* @param cs, GPIO pin for 
* @param pico, GPIO pin for Controller Out Peripheral In
* @param clk, GPIO pin for clock
*
* @return SH1106*, pointer to object
*/
void init_SH1106(
    uint8_t dc, 
    uint8_t rst, 
    uint8_t cs,
    uint8_t pico,
    uint8_t clk
);

/*
* @brief Function used to initalize & configure SPI
*
* Configures SPI and utilizes the SH1106 object
* to initialize and configure the GPIO pins on the Pico2
*
* @return void
*/
void initialize_spi();

/*
* @brief Runs the power-up sequence for the SH1106.
*
* Following the power-up sequence from the Adafruit SH1106 documentation
* and code found on their github. This function should run after
* setting up SPI communication.
*
* @param oled, pointer to SH1106 that is already initialized 
*/
void begin_sh1106(SH1106* oled);

/*
* @brief Executes reset steps for the SH1106.
*
*/
void reset_sh1106();

/*
* @brief Executes the powerup & setup sequence for the SH1106.
*
* These steps are taken from the Adafruit SH1106 doc & code
* examples.
*
* Pre-reqs: initialized SPI communication
*
*/
void configure_sh1106();

/*
* @brief Sends a command to the SH1106 via SPI.
*
* Pre-reqs: initialized SPI communication
*
* @param oled, Pointing to object that has been initialized.
* @param cmd, byte to be sent to OLED as command.
*/
void send_command_sh1106(SH1106* oled, uint8_t cmd);

/*
* @brief Sends a byte of data to the SH1106 via SPI.
*
* Pre-reqs: initialized SPI communication
*
* @param oled, Pointing to object that has been initialized.
* @param data, byte to be sent to OLED as data.
*/
void send_data_sh1106(SH1106* oled, uint8_t data);

/*
* @brief Send buffer data to OLED to update the display 
*
* Pre-reqs: initialized SPI communication
*
* @param oled, Pointing to object that has been initialized.
*/
void update_sh1106(SH1106* oled, uint8_t* buffer);

/*
* @brief Set the lower & upper column addresses 
*
* For more information, read the section on The Column Address pg 15
* in the Sino Wealth SH1106 pdf
*
* @param col, Column between (0 - 127).
*/
void set_column_address(SH1106* oled, uint8_t col);

uint8_t u8x8_gpio_n_delay(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int, void* arg_ptr);

uint8_t u8x8_spi_send_data(u8x8_t* u8x8, uint8_t msg, uint8_t arg_int, void* arg_ptr);
