/*
* Objective: This file ultimately configures the SH1106 OLED.
*
* I'm trying to follow the steps found in the Adafruit_GrayOLED.cpp
*/

#include "c_Adafruit_SH1106.h"
#include "SH1106_Commands.h"

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
    ada->init = UNINIT;

/*    while(1)
    {
        printf("DEBUG0\n");
        printf("ada->dc = %d\nada->rst = %d\nada->cs = %d\nada->pico = %d\n \
                ada->clk = %d\nada->cs = %d\nada->init = %d\n",\
ada->dc, ada->rst, ada->cs, ada->pico, ada->clk, ada->cs, ada->init);
        sleep_ms(1000);
    }
*/
}

void initialize_spi(Adafruit_SH1106* ada)
{
    if(ada->init != UNINIT)
    {
        printf("Issue During Initialization\n");
        while(1);
    } 
 
    // Reset the SH1106.
    gpio_init(ada->rst);
    gpio_set_dir(ada->rst, GPIO_OUT);
    sleep_ms(10); // delay for Vdd to stabilize 
    gpio_put(ada->rst, 1);
    sleep_ms(10); // delay 
    gpio_put(ada->rst, 0); 

    // initialize the CS pin & set pin dir
    gpio_init(ada->cs);
    gpio_set_dir(ada->cs, GPIO_OUT);
    gpio_put(ada->cs, 1); // CS -> high, no communication yet
    
    spi_init(SPI_PORT, BAUD);
    
    // initialize & config gpio pins 
    gpio_set_function(ada->pico, GPIO_FUNC_SPI);
    gpio_set_function(ada->clk, GPIO_FUNC_SPI);

    // initialize the DC pin & set pin dir
    gpio_init(ada->dc);
    gpio_set_dir(ada->dc, GPIO_OUT);
    gpio_put(ada->dc, 0);

    ada->init = INIT; 
//    while(1){printf("DEBUG0\n");sleep_ms(1000);}
}

void configure_Adafruit_SH1106(Adafruit_SH1106* ada)
{
    if(ada->init != INIT)
    {
        printf("Ada struct not initialized\n");
        while(1);
    }

    // bring SH1106 out of Reset
    gpio_put(ada->rst, 1);
    sleep_ms(10); 

    // send SPI cmd to set display off
    gpio_put(ada->dc, 0);
    sleep_ms(10);

    printf("DEBUG: Sending over %d bytes of data via SPI\n",
        sizeof(init_config_steps)/sizeof(uint8_t));
    sleep_ms(10000);
while(1){static int num = 0;printf("DEBUG%d\n",num++);sleep_ms(1000);}
    // send data over from array
    for(int i = 0; i < sizeof(init_config_steps)/sizeof(uint8_t); i++)
    {
        printf("DEBUG: Sending over %X\n", init_config_steps[i]);
        spi_write_blocking(SPI_PORT, &init_config_steps[i], 1);
    }

    // send over SET_DISPLAY_OFF & delay
    uint8_t data = SH1106_DISPLAYON; 
    printf("DEBUG: Sending over %X\n", data);
    spi_write_blocking(SPI_PORT, &data, 1);
    sleep_ms(100);
     
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
    // initialize I/O (UART, USB, etc.)
    stdio_init_all();
sleep_ms(4000);
    Adafruit_SH1106 obj;
    init_Adafruit_SH1106(
        &obj,
        POCI,
        RST,
        CS,
        PICO,
        CLK    
    );

    begin_Adafruit_SH1106(&obj);

    return 0;
}
