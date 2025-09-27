/*
* Objective:
* [] 
*
* Hardware Used:
* [] SH1106 OLED
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "display.h"
#include "sh1106_driver.h"
#include "driver.h"
#include "spi_transport.h"
#include "transport.h"
//#include "SH1106_Interactions.h"
//#include "lame_bitmap.h"


void static inline dbg()
{
    printf("ENTERING DEBUG\n");
    while(1){sleep_ms(1000);}
}

static void testCase1();
static void testCase2(Display* display);
static void testCase3(Display* display);
static void testCase4(Display* display);

int main()
{
    stdio_init_all(); // print to serial
    sleep_ms(2000);

    printf("Dbg: Beginning Setup\n");

    Display sh1106_display;
    //sh1106_display.width = 128U;
    //sh1106_display.height = 64U;
    uint8_t sh1106_buffer[(SH1106_WIDTH * SH1106_HEIGHT) / 8];
    
    SpiTransportConfig sh1106_ctx = 
    {
        .spi = SPI_PORT,
        .cs = OLED_CS,
        .clk = OLED_CLK,
        .dc = OLED_POCI,
        .pico = OLED_PICO,
        .rst = OLED_RST,
        .baud = BAUD
    };
    
    // setup sh1106 object
    DisplayPages sh1106_pgs[SH1106_PAGES];
    sh1106_display.pg_buf = sh1106_pgs;
    
    DisplayPageInfo sh1106_info[SH1106_PAGES];

    setup_display_sh1106(&sh1106_display, sh1106_pgs, sh1106_info, SH1106_WIDTH, SH1106_HEIGHT, SH1106_PAGES, sh1106_buffer);
      
    
    sh1106_display.ctx = (void*)&sh1106_ctx;    
    
    spi_transport_init((SpiTransportConfig*)sh1106_display.ctx);
    
    display_init(&sh1106_display);
    
    display_clear(&sh1106_display);
    //display_update(&sh1106_display);

    while(1)
    {
//        testCase1();
//        testCase2();
//        testCase3();
        testCase4(&sh1106_display);
    }

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
            insert_char(lowercase[i], 3);
            update_sh1106();
        }
        for(int i = 0; i < sizeof(uppercase); ++i)
        {
            insert_char(uppercase[i], 4);
            update_sh1106();
        }
        for(int i = 0; i < sizeof(digits); ++i)
        {
            insert_char(digits[i], 5);
            update_sh1106();
        }
 
}

static void testCase2(Display* display)
{
    display_write_string(display, "Simple Bitmap", 3, 0, (8 * 13));
    display_write_string(display, "SBM 4 Lyfe", 4, 0, (8 * 10));    

//    write_string("Test 1", 3, 0, (8 * 6));
//    write_string("Test 2", 4, 0, (8 * 6));
//    write_string("Test 3", 5, 0, (8 * 6));
//    write_string("Test 4", 6, 0, (8 * 6));
    display_update(display);
}

static void testCase3(Display* display)
{
    display_write_string(display, "0123456789", 3, 0, (8 * 13));
    display_write_string(display, "abcdefghijklmnop", 7, 0, (8*16));
    display_write_string(display, "qrstuvwxyz", 8, 0, (8*10));
    display_update(display);
}

/*
* Test writing integer value incrementing up into different decimal places
*/ 
static void testCase4(Display* display)
{
    int i = 0;
    int val = 0;
    char buffer[] = {1,1,1,1,0};
    while(1)
    {
        itoa(val++,buffer,10);
        display_write_string(display, buffer, 4, 0, sizeof(buffer) * 8);
        display_update(display);               
    }
}
