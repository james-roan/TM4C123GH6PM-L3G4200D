/*
 * uarthelper.c
 *
 *  Created on: Mar 17, 2019
 *      Author: James Roan
 */

#include "uarthelper.h"

void uartPrint(char message []) {
    int length = strlen(message);
    int i;
    for (i = 0; i < length; i++) {
        UARTCharPut(UART0_BASE, message[i]);
    }
}

void uartPrintln(char message []) {
    uartPrint(message);
    UARTCharPut(UART0_BASE, '\r');
    UARTCharPut(UART0_BASE, '\n');
}

