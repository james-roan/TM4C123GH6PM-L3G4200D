/*
 * gyro.h
 *
 *  Created on: Mar 16, 2019
 *      Author: James Roan
 */

#ifndef GYRO_H_
#define GYRO_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/ssi.h"


// L3G4200D Gyro register addresses
// register name // address // read or write
#define WHO_AM_I      0x0F   // r
#define CTRL_REG1     0x20   // rw
#define CTRL_REG2     0x21   // rw
#define CTRL_REG3     0x22   // rw
#define CTRL_REG4     0x23   // rw
#define CTRL_REG5     0x24   // rw
#define REFERENCE     0x25   // r
#define OUT_TEMP      0x26   // r
#define STATUS_REG    0x27   // r
#define OUT_X_L       0x28   // r
#define OUT_X_H       0x29   // r
#define OUT_Y_L       0x2A   // r
#define OUT_Y_H       0x2B   // r
#define OUT_Z_L       0x2C   // r
#define OUT_Z_H       0x2D   // r
#define FIFO_CTRL_REG 0x2E   // rw
#define FIFO_SRC_REG  0x2F   // r
#define INT1_CFG      0x30   // rw
#define INT1_SRC      0x31   // rw
#define INT1_TSH_XH   0x32   // rw
#define INT1_TSH_XL   0x33   // rw
#define INT1_TSH_YH   0x34   // rw
#define INT1_TSH_YL   0x35   // rw
#define INT1_TSH_ZH   0x36   // rw
#define INT1_TSH_ZL   0x37   // rw
#define INT1_DURATION 0x38   // rw
///////////////////////////////////////////

void     initGyro        (uint32_t port_base);
uint32_t composeRegWrite (uint32_t address, uint32_t data);
uint32_t composeRegRead  (uint32_t address);
uint16_t reverse         (uint16_t ui16Number);

#endif /* GYRO_H_ */
