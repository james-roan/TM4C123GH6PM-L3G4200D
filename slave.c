/*
 * slave.c - flash this file to the slave TM4C123GH6PM which connects to the
 *           master TM4C123GH6PM over UART
 *
 *  Created on: Mar 17, 2019
 *      Author: James Roan
 */

#include "tivahelper.c"

void initUART(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    char msg [] = {"UART Port Initialized..."};
    uartPrintln(msg);
}

int main (void) {
    initClock();
    initUART();

    while(1){

    }
    return 0;
}


