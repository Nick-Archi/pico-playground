# SPI Pico Program II

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

A project to integrate the U8g2 Libraries into a RP2350 project:
- utilizing the SPI functionality of the RP2350
- interacting with the SH1106 OLED from Inland via U8g2 calls

## Objective

[] Turn on the OLED
[] Write text to the screen
[] Possibly write an image to the screen? This may require learning how to create bitmaps...

## Setup

Here's how I setup the GPIO Ports on the Pico2

On SH1106 Connection:
GND -> GND(pin 28)<br>
VCC -> 3V3(OUT, pin 36)<br>
CLK -> GP18(pin24)<br>
MOSI -> GP19(pin25)<br>
RES -> GP20(pin26)<br>
DC -> GP16(pin21)<br>
CS -> GP17(pin22)<br>

Picture:
![SH1106 connected to RP2350](images/SH1106_with_RP2350.jpg)

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
   - Drag and drop the uf2 file OR execute below command

    ```
    $ cp ./build/<project_name>.uf2 /media/<user>/RP2350
    ```
## Learnings

1. Adafruit SH1106 Startup Commands
- Adafruit has an excellent diagram that showcases the commands to send to the SH1106 to turn on the display. Link below.

2. Skip electrical diagram
- I don't think I need to get to deep into the how everything is connected in the electrical diagram. I believe that since the OLED is already manufactured, this can mostly be skipped.

3. Sino Wealth SH1106 Command Listingn
- Sino Wealth's SH1106 pdf has a section dedicated to the commands you can send to the SH1106. Link below.

4. Adafruit has some code that I followed to get an idea of how to interact with the SH1106. Link below.

## Useful

- View logs from the kernel to see USB connections
    ```
    $ watch -n 1 "sudo dmesg | tail -n 20"
    ```

## Resources

[U8G2 Library Repo](https://github.com/olikraus/u8g2)
[SH1106 Adafruit Product Spec](https://cdn-shop.adafruit.com/product-files/5228/5223-ds.pdf)<br>
[Adafruit SH1106 Examples](https://github.com/adafruit/Adafruit_SH110x/blob/master/)<br>
[Micro Center OLED](https://www.microcenter.com/product/643965/inland-iic-spi-13-128x64-oled-v20-graphic-display-module-for-arduino-uno-r3)<br>
[Sino Wealth SH1106 PDF](https://www.pololu.com/file/0J1813/SH1106.pdf)<br>
