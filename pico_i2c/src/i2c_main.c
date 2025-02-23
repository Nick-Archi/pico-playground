/*
* Objective:
* [] Create a source file that will utilize an accelerometer to output the
* data on the x, y, & z axis
*
* Hardware Used:
* Sparkfun ADXL345 (https://www.analog.com/en/products/adxl345.html)
*
* i2c Documentation on ADXL345 (https://cdn.sparkfun.com/assets/9/1/8/9/9/ADXL345.pdf)
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define BAUD_RATE ((400) * (1000))
#define GPIO_I2C0_SDA_PIN 4
#define GPIO_I2C0_SCL_PIN 5

// address of where adxl345 connected on i2c line
// obtained from ADXL345.pdf Register Definitions Table 16
static int i2c_dev_addr = 0x53; 

/*
* @brief Initialize the i2c communication on the pico2
*/
void init_i2c_pico(void)
{
    // configure i2c communication
    printf("Baud Rate Set to: %d\n", i2c_init(I2C_PORT, BAUD_RATE));

    // configure GPIO Pins for I2C communication
    gpio_set_function(GPIO_I2C0_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(GPIO_I2C0_SCL_PIN, GPIO_FUNC_I2C);

    // enable GPIO pull-ups
    gpio_pull_up(GPIO_I2C0_SDA_PIN);
    gpio_pull_up(GPIO_I2C0_SCL_PIN);
}

/*
* @brief Perform an i2c write-read operation to obtain the 8 bit
* value of the register.
*
* @param reg, pointer to interested register
* @param data, dump contents read here
* @param bytes, number of bytes to read
*
*/
void i2c_read_address(uint8_t* reg, uint8_t* data, size_t bytes)
{
    i2c_write_blocking(I2C_PORT, i2c_dev_addr, reg, 1, true);
    i2c_read_blocking(I2C_PORT, i2c_dev_addr, data, bytes, false);
}

/*
* @brief Perform an i2c write-write operation to modify the 8 bit
* value of the register.
*
* @param data, pointer to array containing input data
* @param bytes, number of bytes to write from data input
*
*/
void i2c_write_address(uint8_t* data, size_t bytes)
{
   i2c_write_blocking(I2C_PORT, i2c_dev_addr, data, bytes, false); 
}

/*
* @brief Function used to ensure that ADXL345 is connected
*/
void accel_init(void)
{
    // check if the connection is valid
    sleep_ms(1000); // allow the accelerometer to configure itself

    uint8_t reg = 0x00; // devID for accelerometer
    uint8_t chipID; // hold data for receiving

    i2c_read_address(&reg, &chipID, 1);

    if(chipID != 0xE5)
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
    init_i2c_pico();
    accel_init();

    // rate bits are: 0 -> 3 (mask of 0x0F)
    // rate bits initially set to 0x0A according to datasheet
    uint8_t reg_value = 0x00;
    uint8_t bw_rate_reg = 0x2C;
    i2c_read_address(&bw_rate_reg, &reg_value, 1);
    printf("DEBUG: rate bits PRIOR = 0x%X\n", reg_value & 0x0F);

    // modify rate bits to select output rate of 400Hz
    reg_value = (reg_value & 0xF0) | 0x0C; // this is 1100 according to table 6 in datasheet
    uint8_t data[2];
    data[0] = bw_rate_reg;
    data[1] = reg_value;

    i2c_write_address(data, 2);

    i2c_read_address(&bw_rate_reg, &reg_value, 1);
    printf("DEBUG: rate bits AFTER = 0x%X\n", reg_value & 0x0F);

    // accelerometer setup required
    // set measure bit in POWER_CTL register (0x2D)
    uint8_t power_reg = 0x2D;
    i2c_read_address(&power_reg, &reg_value, 1);
    printf("DEBUG: power_reg contents PRIOR = 0x%X\n", reg_value);

    // modify the value in 0x2D now
    data[0] = power_reg;
    data[1] = reg_value | (1 << 3);
    i2c_write_address(data, 2);
    i2c_read_address(&power_reg, &reg_value, 1);
    printf("DEBUG: power_reg contents AFTER = 0x%X\n", reg_value);

    // read the x,y,z axis
    uint8_t store[6]; // storage for x1,x0,y1,y0,z1,z0 axis reads
    int16_t accel_x, accel_y, accel_z;
    float f_accel_x, f_accel_y, f_accel_z;
    uint8_t datax0_addr = 0x32; // start of DATAX0

    while(1)
    {
        i2c_read_address(&datax0_addr, store, 6);

        // shift contents to produce 16bit value 
        // shifting MSB correctly, ORing with LSB
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
