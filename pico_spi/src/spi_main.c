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

static void clear_screen();
static void set_screen();
static void testCase1();
static void testCase2();
static void testCase3();

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
     
    // set buffer to all 0xFF (write white to screen)
    set_buffer();
    update_sh1106();

    // set buffer to all 0x00 (write black to screen)
    clear_buffer();
    update_sh1106();

//    testCase1();
    testCase2();
    testCase3();

dbg();
    return 0;
}

void static testCase1()
{
            // test all chars
        unsigned char lowercase[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p','q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        unsigned char uppercase[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 

        unsigned char digits[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

        for(int i = 0; i < sizeof(lowercase); ++i)
        {
            insert_char(lowercase[i]);
            update_sh1106();
        }
        for(int i = 0; i < sizeof(uppercase); ++i)
        {
            insert_char(uppercase[i]);
            update_sh1106();
        }
        for(int i = 0; i < sizeof(digits); ++i)
        {
            insert_char(digits[i]);
            update_sh1106();
        }
 
}

static void testCase2()
{
    write_string("Test 1", 3, 0, (8 * 6));
    write_string("Test 2", 4, 0, (8 * 6));
    write_string("Test 3", 5, 0, (8 * 6));
    update_sh1106();
}

static void testCase3()
{
    write_string("0123456789", 6, 0, (8*10));
    write_string("01234", 6, 5, (8*5));
//    write_string("0123456789", 6, 26, (8*10));
    write_string("abcdefghijklmnop", 7, 0, (8*16));
    write_string("qrstuvwxyz", 8, 0, (8*10));
    update_sh1106();
}
