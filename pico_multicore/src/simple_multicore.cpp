#include "pico/stdlib.h"
#include "pico/multicore.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define GPIO_PIN 22

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

    gpio_init(GPIO_PIN);
    gpio_set_dir(GPIO_PIN, GPIO_OUT);
    
    while(true)
    {
        uint32_t cmd = multicore_fifo_pop_blocking();
        gpio_put(GPIO_PIN, cmd);
    }
}

