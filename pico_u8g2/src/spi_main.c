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

    SH1106 obj;

    init_SH1106(
        &obj,
        POCI,
        RST,
        CS,
        PICO,
        CLK    
    );

    begin_sh1106(&obj);

    // set buffer to all 0xFF
    memset(g_buffer, 0x00, sizeof(g_buffer));

    update_sh1106(&obj, g_buffer);
    
    // set buffer to all 0xFF
    memset(g_buffer, 0xFF, sizeof(g_buffer));
    update_sh1106(&obj, g_buffer);
dbg();
    return 0;
}
