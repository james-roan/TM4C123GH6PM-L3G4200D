/*
 * gyro.c - a way to interface with the PModGYRO
 *
 *  Created on: Mar 16, 2019
 *      Author: James Roan
 */

#include "gyro.h"
uint32_t check;

void initGyro(uint32_t port_base) {
    // initialize the gyroscope
    uint32_t message = 0x00BC;
    SSIDataPut(port_base, message);
    while(SSIBusy(port_base)){
        // hang
    }
    SSIDataGet(port_base, &check);
    SSIDataPut(port_base, 0x00BC);
    while(SSIBusy(port_base)){
        // hang
        }
    SSIDataGet(port_base, &check);
}

uint32_t composeRegWrite(uint32_t address, uint32_t data){
    address = address << 8;
    uint32_t ret = address | data;
    return ret;
}

uint32_t composeRegRead(uint32_t address){
    uint32_t readBit = 0x1;
    address = address << 8;
    uint32_t ret = readBit | address;
    return ret;
}

// Bit-wise reverses a number.
uint16_t
reverse(uint16_t ui16Number)
{
    uint16_t ui16Index;
    uint16_t ui16ReversedNumber = 0;
    for(ui16Index=0; ui16Index<16; ui16Index++)
    {
        ui16ReversedNumber = ui16ReversedNumber << 1;
        ui16ReversedNumber |= ((1 << ui16Index) & ui16Number) >> ui16Index;
    }
    return ui16ReversedNumber;
}
