/*
* Objective: Project that will toggle an LED via commands sent through
* Serial. 
*
*/

#include <stdio.h>
#include "pico/stdlib.h"

#define LED1_PIN 21 
#define LED2_PIN 22 

#define ON 1
#define OFF 0

int main()
{
    stdio_init_all();

    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);

    while(1)
    {
        printf("Command (1 = on or 0 = off):\n");

        char input = getchar();

        if(input == '1')
        {
            gpio_put(LED1_PIN, ON);
        }
        else if(input == '0')
        {
            gpio_put(LED1_PIN, OFF);
        }
        else
        {
            printf("invalid input\n");
        }
    }

}
