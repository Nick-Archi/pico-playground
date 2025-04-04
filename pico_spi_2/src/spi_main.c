/*
* Objective:
* [] 
*
* Hardware Used:
*
*
*/

#include <stdio.h>
#include <string.h>

#include "SH1106_Interactions.h"
#include <u8g2/u8g2.h>

uint8_t g_buffer[WIDTH * HEIGHT / 8]; // divide by 8 b/c accounting for byte per pixel

SH1106 oled;

u8g2_t u8g2;

void static inline dbg()
{
    printf("ENTERING DEBUG\n");
    while(1){sleep_ms(1000);}
}

int main()
{
    // initialize I/O (UART, USB, etc.)
    stdio_init_all();
sleep_ms(2000);

    printf("DEBUG: Beginning setup\n");

    extern SH1106 oled;

    init_SH1106(
        POCI,
        RST,
        CS,
        PICO,
        CLK    
    );

    initialize_spi();
    configure_sh1106();

    u8g2_Setup_sh1106_128x64_noname_f(
        &u8g2,
        U8G2_R0,
        u8x8_spi_send_data,
        u8x8_gpio_n_delay); 

dbg();
    return 0;
}
