/*
 * uarthelper.c
 *
 *  Created on: Mar 17, 2019
 *      Author: James Roan
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
    if (!UARTCharsAvail(UART0_BASE)){
        // if there is no data ready whatsoever, return false
        return false;
    }
    else {
        // otherwise, check if this is the correct data
        char delim_check [DELIM_LENGTH];
        unsigned int i = 0;
        while(UARTCharsAvail(UART0_BASE)){
            delim_check[i] = UARTCharGet(UART0_BASE);
        }
        return strcmp(DATA_DELIMITER, delim_check)
    }
}

