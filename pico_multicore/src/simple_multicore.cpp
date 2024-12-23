#include "pico/stdlib.h"
#include "pico/multicore.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 25

void second_core_code()
{
    while(true)
    {
        sleep_ms(1000);
        multicore_fifo_push_blocking(GPIO_ON);
        sleep_ms(1000);
        multicore_fifo_push_blocking(GPIO_OFF);
    }
}

int main()
{
    multicore_launch_core1(second_core_code);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    while(true)
    {
        uint32_t cmd = multicore_fifo_pop_blocking();
        gpio_put(LED_PIN, cmd);
    }
}

