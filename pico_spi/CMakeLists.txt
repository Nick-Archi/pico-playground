cmake_minimum_required(VERSION 3.22)

set(PICO_PLATFORM "rp2350-arm-s" CACHE STRING "Targeting pico 2350 specifically the arm core")

set(SOURCE_DIR "src/")
set(EXEC1_NAME "spi_stuff") 

# initialize the SDK based on PICO_SDK_PATH
# note: this happens before the project()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of proj

add_executable(${EXEC1_NAME} 
    ${SOURCE_DIR}spi_main.c
    ${SOURCE_DIR}SH1106_Interactions.c
)

target_include_directories(${EXEC1_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add pico_stdlib library which aggregates commonly used features
target_link_libraries(${EXEC1_NAME} 
    pico_stdlib 
    hardware_spi
)

# tell compiler to use the USB output and disable UART output
pico_enable_stdio_usb(${EXEC1_NAME} 1)
pico_enable_stdio_uart(${EXEC1_NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${EXEC1_NAME})
