#include "pico/stdlib.h"

int main()
{
    // init GPIO 25 (Green LED)
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while(1)
    {
        gpio_put(25,1);
        sleep_ms(500);
        gpio_put(25,0);
        sleep_ms(2000);
    }     

    return 0;
}
