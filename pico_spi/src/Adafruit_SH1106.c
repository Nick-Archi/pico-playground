/*
* Objective: This file ultimately configures the SH1106 OLED.
*
* I'm trying to follow the steps found in the Adafruit_GrayOLED.cpp
*/

#include "c_Adafruit_SH1106.h"

void init_Adafruit_SH1106(
    Adafruit_SH1106* ada,
    uint8_t dc, 
    uint8_t rst, 
    uint8_t cs,
    uint8_t pico,
    uint8_t clk
)
{
    ada->dc = dc;
    ada->rst = rst;
    ada->cs = cs;
    ada->pico = pico;
    ada->clk = clk;
    ada->cs = cs;
}

void initalize_spi(Adafruit_SH1106* ada)
{
    ada->init = 0;
 
    // Reset the SH1106.
    gpio_init(ada->res);
    gpio_set_dir(ada->res, GPIO_OUT);
    sleep_ms(10); // delay for Vdd to stabilize 
    gpio_put(ada->res, 1);
    sleep_ms(10); // delay 
    gpio_put(ada->res, 0); 

    spi_init(SPI_PORT, BAUD);
    
    // initialize & config gpio pins 
    gpio_set_function(ada->pico, GPIO_FUNC_SPI);
    gpio_set_function(ada->clk, GPIO_FUNC_SPI);

    // initialize the CS pin & set pin dir
    gpio_init(ada->cs);
    gpio_set_dir(ada->cs, GPIO_OUT);
    gpio_put(ada->cs, 1); // CS -> high, no communication yet

    // initialize the DC pin & set pin dir
    gpio_init(ada->dc);
    gpio_set_dir(ada->dc, GPIO_OUT);
    gpio_put(ada->dc, 0);

    ada->init = 1; 
}

void configure_Adafruit_SH1106(Adafruit_SH1106* ada)
{
    if(!ada->init)
    {
        printf("Ada struct not initialized\n");
        return;
    }

    // bring SH1106 out of Reset

    // send SPI cmd to set display off 
}

void begin_Adafruit_SH1106(Adafruit_SH1106* ada)
{
    // initialize the SPI pins on pico2
    initialize_spi(ada);
    printf("SPI Initialized\n");

    // execute the Vdd/Vcc off state -> initial settings configuration steps
    configure_Adafruit_SH1106(ada);   
}

int main()
{
    return 0;
}
