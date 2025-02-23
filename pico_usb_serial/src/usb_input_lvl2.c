/*
* Objective: Expanded on the initial usb_input.c program and modified it
* so that 2 LEDs are connected and can be controlled via Serial
*
*/

#include <stdio.h>
#include "pico/stdlib.h"

#define ON 1
#define OFF 0

typedef struct pin_t
{
    int pin_number;
    int pin_state;
}pin;

int main()
{
    sleep_ms(1000);
    stdio_init_all();

    // create the pin structs
    pin pin1 = {.pin_number = 21, .pin_state = OFF};
    pin pin2 = {.pin_number = 22, .pin_state = OFF};

    gpio_init(pin1.pin_number);
    gpio_init(pin2.pin_number);

    gpio_set_dir(pin1.pin_number, GPIO_OUT);
    gpio_set_dir(pin2.pin_number, GPIO_OUT);

    while(1)
    {
        pin* p_pin;
        char buffer[3];

        printf("\nCommand structure = \"(led)(off|on)\"\n");
        printf("Example: 10, selects LED1 -> OFF\n");
        printf("Enter: ");
        
        fgets(buffer, 3, stdin);

        if(buffer[0] == '1')
        {
            p_pin = &pin1; 
            if(buffer[1] == '1')
            { gpio_put(p_pin->pin_number, ON); }
            else if(buffer[1] == '0')
            { gpio_put(p_pin->pin_number, OFF); }
        }
        else if(buffer[0] == '2')
        {
            p_pin = &pin2; 
            if(buffer[1] == '1')
            { gpio_put(p_pin->pin_number, ON); }
            else if(buffer[1] == '0')
            { gpio_put(p_pin->pin_number, OFF); }
        }
        else
        {
            printf("whut are you trying to do?\n");
        }
    }

}
