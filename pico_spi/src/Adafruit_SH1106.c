/*
* Objective: This file ultimately configures the SH1106 OLED.
*
* I analyzed the steps found in the Adafruit_SH110x project: https://github.com/adafruit/Adafruit_SH110x/tree/master
* 
*/

#include "c_Adafruit_SH1106.h"
#include "SH1106_Commands.h"

extern SH1106 oled;

void static inline dbg()
{
    printf("ENTERING DEBUG\n");
    while(1){sleep_ms(1000);}
}

void init_SH1106(
    uint8_t dc, 
    uint8_t rst, 
    uint8_t cs,
    uint8_t pico,
    uint8_t clk,
    uint8_t* buffer
)
{
    oled.dc = dc;
    oled.rst = rst;
    oled.cs = cs;
    oled.pico = pico;
    oled.clk = clk;
    oled.cs = cs;
    oled.buffer = buffer;
    oled.init = UNINIT;

    printf("DEBUG0\n");
    printf("oled.dc = %d\noled.rst = %d\noled.cs = %d\noled.pico = %d\n\
oled.clk = %d\noled.init = %d\n",\
oled.dc, oled.rst, oled.cs, oled.pico, oled.clk, oled.init);
}

void initialize_spi()
{
    if(oled.init != UNINIT)
    {
        printf("Issue During Initialization\n");
        while(1);
    } 
 
    // Reset the SH1106.
    gpio_init(oled.rst);
    gpio_set_dir(oled.rst, GPIO_OUT);
    sleep_ms(10); // delay for Vdd to stabilize 

    // initialize the CS pin & set pin dir
    gpio_init(oled.cs);
    gpio_set_dir(oled.cs, GPIO_OUT);
    gpio_put(oled.cs, 1); // CS -> high, no communication yet
    
    spi_init(SPI_PORT, BAUD);
    printf("DEBUG: BAUD rate configured to = %d\n", spi_get_baudrate(SPI_PORT)); 
    
    // initialize & config gpio pins 
    gpio_set_function(oled.pico, GPIO_FUNC_SPI);
    gpio_set_function(oled.clk, GPIO_FUNC_SPI);

    // initialize the DC pin & set pin dir
    gpio_init(oled.dc);
    gpio_set_dir(oled.dc, GPIO_OUT);
    gpio_put(oled.dc, 0);

    oled.init = INIT;
}

void configure_SH1106()
{
    if(oled.init != INIT)
    {
        printf("Ada struct not initialized\n");
        while(1);
    }

    // bring SH1106 out of Reset
    reset_sh1106();

    printf("DEBUG: Sending over %d bytes of data via SPI\n",
        sizeof(init_config_steps)/sizeof(uint8_t));
    sleep_ms(3000);
    // send data over from array
    for(int i = 0; i < sizeof(init_config_steps)/sizeof(uint8_t); i++)
    {
        printf("DEBUG: Sending over %X\n", init_config_steps[i]);
        send_command_sh1106(init_config_steps[i]);
    }

    // send over SET_DISPLAY_ON & delay
    uint8_t data = SH1106_DISPLAYON; 
    printf("DEBUG: Sending over %X\n", data);
    send_command_sh1106(data);
    sleep_ms(500);
}

void begin_sh1106()
{
    // initialize the SPI pins on pico2
    initialize_spi();
    printf("SPI Initialized\n");

    // execute the Vdd/Vcc off state -> initial settings configuration steps
    configure_SH1106();   
}

void reset_sh1106()
{
    if(oled.init != INIT)
    {
        printf("Issue w/ Initialization. Not resetting\n");
        while(1);
    }

    gpio_put(oled.rst, 0);
    sleep_ms(10);
    gpio_put(oled.rst, 1);
    sleep_ms(10);
}

void send_command_sh1106(uint8_t cmd)
{
    if(oled.init != INIT)
    {
        printf("Issue with Initialization. Not sending cmd data\n");
        while(1);
    }

    gpio_put(oled.dc, 0); // Cmd mode
    gpio_put(oled.cs, 0);
    sleep_ms(10);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(oled.cs, 1);
}

void send_data_sh1106(uint8_t data)
{
    if(oled.init != INIT)
    {
        printf("Issue with Initialization. Not sending data\n");
        while(1);
    }

    gpio_put(oled.dc, 1); // Data mode
    gpio_put(oled.cs, 0);
    sleep_ms(10);
    spi_write_blocking(SPI_PORT, &data, 1);
    gpio_put(oled.cs, 1);
}

void update_sh1106()
{
    if(oled.init != INIT)
    {
        printf("Ada struct not initialized\n");
        while(1);
    }

    // update each page
    for(uint8_t page = 0; page < 8; page++)
    {
        send_command_sh1106(SH1106_PAGE_OFFSET(page));
        set_column_address(0);

        // write each byte in that page to OLED
        for(uint8_t i = 0; i < WIDTH; i++)
        {
            /*
            * This is performing a type of offset. Think of it as
            * addressing a 2D array as a 1D vector.
            * ex) page = 1, i = 0, [1 * 128 + 0], access buffer[128] -
            * buffer[256], that's 128 bytes for page 1...
            */
            send_data_sh1106(oled.buffer[page * WIDTH + i]);
        }
    }
}

void set_column_address(uint8_t col)
{
    //[TODO] This part is absolute magic to me and I don't fully understand yet
    col += 2;
    send_command_sh1106((0x10 | (col >> 4)));     
    send_command_sh1106((0x00 | (col & 0x0F)));     
}
