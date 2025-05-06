/*
* Objective:
* [] 
*
* Hardware Used:
* [] SH1106 OLED
*
*/

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "SH1106_Interactions.h"
#include "lame_bitmap.h"

SH1106 oled;

uint8_t buffer[WIDTH * HEIGHT / 8]; // divide by 8 b/c accounting for byte per pixel

void static inline dbg()
{
    printf("ENTERING DEBUG\n");
    while(1){sleep_ms(1000);}
}

int main()
{
    stdio_init_all(); // print to serial
    sleep_ms(2000);

    printf("Dbg: Beginning Setup\n");

    init_SH1106(
        POCI,
        RST,
        CS,
        PICO,
        CLK,
        buffer
    );

    begin_sh1106();

    // set buffer to all 0x00 (write black to screen)
    memset(buffer, 0x00, sizeof(buffer));

    update_sh1106();
    
    // set buffer to all 0xFF
    //memset(buffer, 0xFF, sizeof(buffer));
    memcpy(buffer+256, &bitmap[0][0], 8); 
    update_sh1106();
dbg();
    return 0;
}
