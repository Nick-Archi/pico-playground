# Blinky Raspberry Pi Pico Program

This is just an introductory program to get me familiar with the basics of:
- creating a CMakeLists.txt to build a raspberry pi program
- creating a main.cpp to utilize the RP SDK to blink an LED
- calling cmake from within a build/ with appropriate arguments

Steps are from: [Link](https://github.com/raspberrypi/pico-sdk/tree/master)

# Quick Steps

## Following on a Linux Command Line
1. Assuming all packages & libraries installed properly, if not then follow main pico-sdk link to get setup.

2. Setup project to point to Raspberry Pi Pico SDK
    * Creating a ~/.bashrc and entering the path
    ```
    export PICO_SDK_PATH=<USER-DEFINED-PATH>
    ```

3. Setup & call cmake targeting ARM core
    ```
    $ mkdir build
    $ cd build
    $ cmake -DPICO_PLATFORM=rp2350-arm-s ..
    ```

4. Call make to create the target
    ```
    $ make
    ```

5. Drag and drop <project_name>.uf2 file onto pico board via connected USB.
