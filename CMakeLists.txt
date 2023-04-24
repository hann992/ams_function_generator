cmake_minimum_required(VERSION 2.8)

project(function-generator C)

set(CMAKE_C_STANDARD 99)

# Set the path to the AVR toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/AVR-Toolchain/avr-toolchain.cmake)

# Set the MCU type and clock speed
set(MCU atmega328p)
set(CPU_SPEED 16000000UL)

# Set the path to avrdude and the programming parameters
set(AVRDUDE avrdude)
set(AVRDUDE_PORT /dev/ttyACM0)
set(AVRDUDE_PROGRAMMER arduino)
set(AVRDUDE_MCU m328p)

# Find all source files in the source directory
file(GLOB_RECURSE SOURCES "source/*.c")

# Compile the binary
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -mmcu=${MCU} -DF_CPU=${CPU_SPEED})
target_link_options(${PROJECT_NAME} PRIVATE -mmcu=${MCU})

# Set the avrdude command to upload the binary to the device
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${AVRDUDE} -v -p ${AVRDUDE_MCU} -c ${AVRDUDE_PROGRAMMER} -P ${AVRDUDE_PORT} -U flash:w:${PROJECT_NAME}.hex:i
    COMMENT "Uploading ${PROJECT_NAME}.hex to ${AVRDUDE_PORT} using ${AVRDUDE_PROGRAMMER}"
)
