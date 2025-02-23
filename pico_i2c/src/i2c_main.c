/*
* Objective:
* [] Create a source file that will utilize an accelerometer to output it's 3D information
*
* Hardware Used:
* Sparkfun ADXL345 (https://www.analog.com/en/products/adxl345.html)
* i2c Documentation on ADXL345 (https://cdn.sparkfun.com/assets/9/1/8/9/9/ADXL345.pdf)
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0

// address of where adxl345 connected on i2c line
// obtained from ADXL345.pdf Register Definitions Table 16
static int i2c_dev_addr = 0x53; 

/*
* @brief Function used to ensure that ADXL345 is connected
*/
void accel_init(void)
{
    // check if the connection is valid
    sleep_ms(1000); // allow the accelerometer to configure itself

    uint8_t reg = 0x00; // devID for accelerometer
    uint8_t chipID[1]; // hold data for receiving

    //  
    i2c_write_blocking(I2C_PORT, i2c_dev_addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, i2c_dev_addr, chipID, 1, false);

    if(chipID[0] != 0xE5)
    {
        while(1)
        {
            printf("Chip ID Not Correct - Check Connection\n");
            sleep_ms(5000);
        }
    }

    
    sleep_ms(3000);
    printf("Connected to Accelerometer\n");
}

int main(void)
{
    stdio_init_all();
    sleep_ms(2000);    
    
    // configure i2c communication
    printf("Baud Rate Set to: %d\n", i2c_init(I2C_PORT, 400 * 1000));

    // configure GPIO Pins for I2C communication
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);

    // enable GPIO pull-ups
    gpio_pull_up(4);
    gpio_pull_up(5);

    // call accelerometer init function
    accel_init();

    // accelerometer setup required?
    // set measure bit in POWER_CTL register (0x2D)
    uint8_t reg_value = 0x00;
    uint8_t power_reg = 0x2D;
//    i2c_write_blocking(I2C_PORT, i2c_dev_addr, &power_reg, 1, true);
//    i2c_read_blocking(I2C_PORT, i2c_dev_addr, &reg_value, 1, false);

    // modify the value in 0x2D now
    reg_value |= (1 << 3);
    i2c_write_blocking(I2C_PORT, i2c_dev_addr, &power_reg, 1, true);
    i2c_write_blocking(I2C_PORT, i2c_dev_addr, &reg_value, 1, false); 

    // read the x,y,z axis
    uint8_t store[6]; // storage for x1,x0,y1,y0,z1,z0 axis reads
    int16_t accel_x, accel_y, accel_z;
    float f_accel_x, f_accel_y, f_accel_z;
    uint8_t datax0_addr = 0x32; // start of DATAX0

    // continually read axis values
    while(1)
    {
        i2c_write_blocking(I2C_PORT, i2c_dev_addr, &datax0_addr, 1, true);
        i2c_read_blocking(I2C_PORT, i2c_dev_addr, store, 6, false);

        accel_x = ((store[1] << 8) | store[0]);
        accel_y = ((store[3] << 8) | store[2]);
        accel_z = ((store[5] << 8) | store[4]);

        f_accel_x = accel_x / 100.00;
        f_accel_y = accel_y / 100.00;
        f_accel_z = accel_z / 100.00;

        printf("X: %6.2f    Y: %6.2f    Z: %6.2f\n", f_accel_x, f_accel_y, f_accel_z);
        sleep_ms(500);
    }

}
