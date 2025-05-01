#include "pico/stdlib.h"

#define PICO_USER_LED_PIN 21

#ifndef PICO_USER_LED_PIN
#define PIN PICO_DEFAULT_LED_PIN
#else
#define PIN PICO_USER_LED_PIN
#endif

int main()
{
    // init GPIO 25 (Green LED)
    gpio_init(PIN);
    gpio_set_dir(PIN, GPIO_OUT);

    while(1)
    {
        gpio_put(PIN,1);
        sleep_ms(500);
        gpio_put(PIN,0);
        sleep_ms(2000);
    }     

    return 0;
}
