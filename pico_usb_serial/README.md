# Output via USB Raspberry Pi Pico Program

Project Objectives:
- Blink an LED and output to USB
- Connect to Pico2 via serial connection

Steps are from: [Link](https://github.com/raspberrypi/pico-sdk/tree/master)

# Quick Steps

## Following on a Linux Command Line
1. Assuming all packages & libraries installed properly, if not then follow main pico-sdk link to get setup.

    * Ensure that tinyUSB has been initialized in sdk path
    ```
        $ cd $PICO_SDK_PATH/lib/tinyusb
        git submodule update --init
    ```

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

6. Find out where the board connected to
    ```
    $ watch -n 2 "dmesg|tail"
    ```

7. Connect via minicom
    * You may have to use sudo in front of minicom if permission error happens
    ```
    $ minicom -D <location-board-connected>, ex) minicom -D /dev/ttyACM0 
    ```

    * May have to change the BAUD rate to 115200
    ```
    - Open minicom
    - Press ctrl-A, then Z
    - Enter O
    - Select Serial Port Setup  
    ```
