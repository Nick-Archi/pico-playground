cmake_minimum_required(VERSION 3.22)

set(PICO_PLATFORM "rp2350-arm-s" CACHE STRING "Targeting pico 2350 specifically the arm core")

set(SOURCE_DIR "src/")
set(EXEC1_NAME "usb_input") 
set(EXEC2_NAME "usb_input_lvl2") 

# initialize the SDK based on PICO_SDK_PATH
# note: this happens before the project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of proj

add_executable(${EXEC1_NAME} 
    ${SOURCE_DIR}usb_input.c
)

add_executable(${EXEC2_NAME} 
    ${SOURCE_DIR}usb_input_lvl2.c
)
# add pico_stdlib library which aggregates commonly used features
target_link_libraries(${EXEC1_NAME} 
    pico_stdlib 
)

target_link_libraries(${EXEC2_NAME} 
    pico_stdlib 
)

# tell compiler to use the USB output and disable UART output
pico_enable_stdio_usb(${EXEC1_NAME} 1)
pico_enable_stdio_uart(${EXEC1_NAME} 0)

pico_enable_stdio_usb(${EXEC2_NAME} 1)
pico_enable_stdio_uart(${EXEC2_NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${EXEC1_NAME})
pico_add_extra_outputs(${EXEC2_NAME})
