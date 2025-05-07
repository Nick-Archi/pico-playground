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
        CLK
    );

    begin_sh1106();

    // set buffer to all 0x00 (write black to screen)
    write_to_page(0x00, 0, BYTES);
//    memset(buffer, 0x00, sizeof(buffer));

    update_sh1106();
    
    // set buffer to all 0xFF
    insert_char('a');
//    memcpy(buffer + (256 + 0), &char_bitmap[0][0], 8*26); 
//    memcpy(buffer + (256 + (8*26)), &digi_bitmap[0][0], 8*10); 
    update_sh1106();

//    memset(buffer, 0xFF, sizeof(buffer));
//    update_sh1106();
dbg();
    return 0;
}
