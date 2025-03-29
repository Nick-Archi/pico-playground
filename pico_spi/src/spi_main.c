/*
* Objective:
* [] 
*
* Hardware Used:
*
*
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define PICO    PICO_DEFAULT_SPI_TX_PIN
#define CS      PICO_DEFAULT_SPI_CSN_PIN
#define CLK     PICO_DEFAULT_SPI_SCK_PIN
#define POCI    PICO_DEFAULT_SPI_RX_PIN

#define BAUD    (1 * (10^6))

#define SPI_PORT spi0

int main()
{
    stdio_init_all(); // print to serial
    spi_init(SPI_PORT, BAUD);

    // initialize & config gpio pins 
    gpio_set_function(POCI, GPIO_FUNC_SPI);
    gpio_set_function(CLK, GPIO_FUNC_SPI);
    gpio_set_function(PICO, GPIO_FUNC_SPI);

    // initialize the CS pin & set pin dir
    gpio_init(CS)
    gpio_set_dir(CS, GPIO_OUT);
    gpio_put(CS, 1) // CS -> high, no communication yet

    

    return 0;
}
