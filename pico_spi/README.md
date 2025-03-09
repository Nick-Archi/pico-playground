# I2C Pico Program

## Table of Content
[Overview](#overview)<br>
[Objective](#objective)<br>
[Setup](#setup)<br>
[Building](#building)<br>
[Executing](#executing)<br>
[Learnings](#learnings)<br>
[Useful](#useful)<br>
[Resources](#resources)<br>

## Overview

An introductory project to get familiar with the basics of:
- utilizing the i2c functionality of the RP2350
- interacting with an ADXL345 accelerometer that's connected to the RP2350 

## Objective

[] Read the x, y, & z axis from the ADXL345 accelerometer

## Setup

Here's how I setup the GPIO Ports on the Pico2

On ADXL345 Connection:
SCL -> GP4(pin6)<br>
SDA -> GP5(pin7)<br>
VCC -> 3V3(OUT, pin 36)<br>
GND -> GND(pin 38)<br>
CS -> 3V3(OUT, pin 36)<br>
SD0 -> GND(pin 38)<br>

Picture:
![ADXL345 connected to RP2350](images/ADXL345_connect_2_pico2.jpg)

## Building 
1. Setup & call cmake
    ```
    $ mkdir build
    $ cd build
    $ cmake ..
    ```

    - PICO_PLATFORM moved to CMakeLists.txt, otherwise call cmake -DPICO_PLATFORM=rp2350-arm-s ..

2. Call make to create the target
    ```
    $ make
    ```

3. Move <project_name>.uf2 onto the pico board connected via USB
   - Drag and drop the uf2 file OR

    ```
    $ cp ./build/<project_name>.uf2 /media/<user>/RP2350
    ```
## Learnings

1. Debug I2C connection
- Added a small check to ensure that I could talk to the ADXL345. Within the datasheet, it explains how to check the DevID.

2. Single i2c_write_blocking for multiple writes 
- initially, I was unable to modify targeted registers. I was performing i2c writes using separate i2c_write_blocking calls but I decided to combine them into 1 and instead change the parameter regarding the number of bytes being sent.

## Useful

- View logs from the kernel to see USB connections
    ```
    $ watch -n 1 "sudo dmesg | tail -n 20"
    ```

## Resources

[I2C Sparkfun Documentation](https://learn.sparkfun.com/tutorials/i2c#i2c-at-the-hardware-level)<br>
[ADXL345 DataSheet](https://cdn.sparkfun.com/assets/9/1/8/9/9/ADXL345.pdf)<br>
[ADXL345 Hookup Guide](https://learn.sparkfun.com/tutorials/adxl345-hookup-guide/all)<br>
