# Multicore Raspberry Pi Pico Program

This is just an introductory project to familiar with the basics of:
- utilizing the multicore functionality of the RP2350
- interacting with the shared FIFO on the RP2350

# Quick Steps

Steps are from: [Link](https://github.com/raspberrypi/pico-sdk/tree/master)

## Building via Linux Command Line
1. Assuming all packages & libraries installed properly, if not then follow main pico-sdk link to get setup.

2. Setup project to point to Raspberry Pi Pico SDK
    * Creating a ~/.bashrc and entering the path
    ```
    export PICO_SDK_PATH=<USER-DEFINED-PATH>
    ```

3. Setup & call cmake
    ```
    $ mkdir build
    $ cd build
    $ cmake ..
    ```

    # PICO_PLATFORM moved to CMakeLists.txt, otherwise call cmake -DPICO_PLATFORM=rp2350-arm-s ..

4. Call make to create the target
    ```
    $ make
    ```

5. Drag and drop <project_name>.uf2 file onto pico board via connected USB.

# Project Learnings

1. Debug USB connection

- Was unable to connect via USB after flashing. Realized the stdio_init_all() was missing. This is usd to initialize the I/O on the board after flashing (UART, USB, etc).

- View logs from the kernel to see USB connections
    ```
    $ watch -n 1 "sudo dmesg | tail -n 20"
    ```

