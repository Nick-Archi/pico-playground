#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    // initialize I/O
    stdio_init_all();

    // init GPIO 25 (Green LED)
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while(1)
    {
        gpio_put(25,1);
        printf("LED_ON\n");
        sleep_ms(500);

        gpio_put(25,0);
        printf("LED_OFF\n");
        sleep_ms(2000);
    }     

    return 0;
}
