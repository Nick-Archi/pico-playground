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

// print out some info from the structs passed in to see if anything is being done...
{
    printf("u8g2.tile_buf_height = %d\n", u8g2.tile_buf_height);
    printf("u8g2.u8x8.display_info->tile_width = %d\n", u8g2.u8x8.display_info->tile_width);
    printf("address of u8g2 buffer = %p\n", u8g2.tile_buf_ptr);
    printf("printing contents of the buffer\n");
    u8g2.tile_buf_ptr[0] = 0xDE;
    u8g2.tile_buf_ptr[1023] = 0xAD;
    /*for(int i = 0; i < u8g2.tile_buf_height; i++)
    {
        printf("Row %d: ", i);
        for(int j = 0; j < (u8g2.u8x8.display_info->tile_width * 8); j++)
        {
            printf("%d, ", *(u8g2.tile_buf_ptr + (i * u8g2.pixel_buf_width) + j));
        }
        printf("\n");
    }*/
}
    u8g2_ClearBuffer(&u8g2);
    u8g2_DrawStr(&u8g2, 0, 20, "HELLO\n");
    u8g2_SendBuffer(&u8g2);
dbg();

    return 0;
}
