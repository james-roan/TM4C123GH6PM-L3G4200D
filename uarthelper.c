/*
 * uarthelper.c
 *
 *  Created on: Mar 17, 2019
 *      Author: James Roan
 *
 *  Notes: UART0_BASE is connected to the USB interface, so it cannot be used for UART between boards
 */



#include "uarthelper.h"

#define DELIM_LENGTH 9 // one more than the length of DATA_DELIMITER for the null terminator
const char DATA_DELIMITER [DELIM_LENGTH] = "DATA_RDY";

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

void uartSendData(char data []){

}

bool uartDataReady(void) {
    return UARTCharsAvail(UART7_BASE);
}

