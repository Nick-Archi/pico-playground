#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unordered_set>
#include "pico/multicore.h"
#include "pico/stdlib.h"

#define GPIO_ON 1
#define GPIO_OFF 0
#define LED_PIN 25
#define HASH_AMOUNT 20
#define SLEEP_AMOUNT 1000

/**
* @brief Set that will hold prime numbers between 1 & 20.
*/
std::unordered_set<int> prime{2,3,5,7,9,11,13,17,19};

/**
* @brief Hash computation
*
* @param value Integer value
*
* @return Hash value in range of 1 - HASH_AMOUNT
*/
inline int hash(int value)
{
    return (value % HASH_AMOUNT) + 1;
}

/**
* @brief Struct to abstract a GPIO Pin & state
*/
struct gpioState
{
    bool state; /**< On=true, Off=false. */
    int pin_number; /**< Pin number for targeted GPIO. */

    /**
    * @brief Constructor for initializing GPIO Pin to state=Off and pin#=0
    */
    gpioState() : state(false), pin_number(0) {}

    /**
    * @brief Constructor for initializing GPIO Pin to state=Off and pin#=init_pin.
    * 
    * @param init_pin GPIO Pin Number. 
    */
    gpioState(int init_pin) : state(false), pin_number(init_pin) {}
    
    /**
    * @brief Switch the state of GPIO struct from ON->OFF or OFF->ON 
    */
    inline void toggleState()
    {
        this->state = !this->state;
    }
}gpio1(LED_PIN);

/**
* @brief Context of execution for Core 1 on RP2350
*
* This function will compute a hash value based on the current time and push this into the shared FIFO between Core 0 & Core 1.
*/
void core1_entry()
{
    while(true)
    {
        sleep_ms(SLEEP_AMOUNT/2);
        srand((unsigned) time(NULL)); // seed random number gen
        int val = hash(rand());
        
        printf("HASH: %d\n", val);

        sleep_ms(SLEEP_AMOUNT * 2); // sleep for longer to view value
        multicore_fifo_push_blocking(val);
    }
}

int main()
{
    // initialize I/O (UART, USB, etc.)
    stdio_init_all();

    // start core1 execution
    multicore_launch_core1(core1_entry);

    /*
    * initialize gpio pins and set direction of gpio pins
    */
    gpio_init(gpio1.pin_number);
    gpio_set_dir(gpio1.pin_number, GPIO_OUT);
    gpio_put(gpio1.pin_number, gpio1.state);
   

    /*
    * This loop will: 
    * - pop the hash from the fifo 
    * - determine if the hash is a prime number
    * - toggle the led if it is a prime number
    */ 
    while(true)
    {
        int hash = multicore_fifo_pop_blocking();

        bool is_prime = (prime.find(hash) != prime.end()) ? true : false;

        if(is_prime)
        {
            gpio1.toggleState();
            gpio_put(gpio1.pin_number, gpio1.state);

            sleep_ms(SLEEP_AMOUNT/2);
 
            gpio1.toggleState();
            gpio_put(gpio1.pin_number, gpio1.state);
        }
    }
}

