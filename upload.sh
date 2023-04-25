#!/bin/bash

# Set the path to your compiled binary file
BINARY_FILE="ams-function-generator.hex"

# Set the path to avrdude.conf file
AVRDUDE_CONF="avrdude-v7.1-windows-x64/avrdude.conf"

# Set the serial port for your Arduino
SERIAL_PORT="COM3"

# Set the baud rate for your Arduino
BAUD_RATE="115200"

# Set the programmer for your Arduino
PROGRAMMER="arduino"

# Set the part number for your Arduino
PART_NUMBER="m2560"

# Use avrdude to upload the compiled binary to your Arduino
# avrdude -p m2560 -c stk500v2 -P /path/to/serial -b 115200 -F -U flash:w:/path/to/image.hex
#avrdude-v7.1-windows-x64/avrdude -C"$AVRDUDE_CONF" -v -p"$PART_NUMBER" -cstk500v2 -P"$SERIAL_PORT" -b"$BAUD_RATE" -F -Uflash:w:"$BINARY_FILE":i

avrdude-v7.1-windows-x64/avrdude -C"$AVRDUDE_CONF" -v -patmega2560 -cwiring -PCOM3 -b115200 -D -Uflash:w:"$BINARY_FILE":i