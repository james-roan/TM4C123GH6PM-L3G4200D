/*
 * slave.c - flash this file to the slave TM4C123GH6PM which connects to the
 *           master TM4C123GH6PM over UART
 *
 *  Created on: Mar 17, 2019
 *      Author: James Roan
 */

#include "tivahelper.h"
#include "uarthelper.h"

void initUART(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); // for USB serial
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7); //Enable UART 7 in GPIO port E.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); //Enable port E.

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinConfigure(GPIO_PE0_U7RX); //Set port E pin 0 as UART 7 RX.
    GPIOPinConfigure(GPIO_PE1_U7TX); //Set port E pin 1 as UART 7 TX.

    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //Set UART 7 clock to system clock at 115200 baud with 8 bit data length, one stop bit and no parity bits.
    UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    char msg [] = {"UART Ports Initialized..."};
    uartPrintln(msg);
}

int main (void) {
    initClock();
    initUART();

    while(1){
        if(uartDataReady()){
            uartPrintln((char *)UARTCharGet(UART7_BASE));
        }
    }
    return 0;
}


