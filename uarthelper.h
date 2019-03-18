/*
 * uarthelper.h
 *
 *  Created on: Mar 17, 2019
 *      Author: James Roan
 */

#ifndef UARTHELPER_H_
#define UARTHELPER_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"

void uartPrint(char message []);
void uartPrintln(char message []);
void uartSendData(char data []);
bool uartDataReady(void);


#endif /* UARTHELPER_H_ */
