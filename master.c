/*
 * master.c - flash this one to the master TM4C123GH6PM, which interfaces with the L3G4200D
 *
 *  Created on: Mar 16, 2019
 *      Author: James Roan
 */

#include "tivahelper.h"
#include "uarthelper.h"
#include "gyro.h"

char welcome [] = {"L3G4200D via SPI to UART: Master Loading..."};

void initSSI(void){
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * The L3G4200D's SPI interface requires the clock to be high normally because       *
     * it is triggered by a falling edge                                                 *
     * The CS pin must go low at the beginning of the transmission.                      *
     *                                                                                   *
     * The TM4C123GH6PM's SPI module is configured by the SPO Clock Polarity Bit and     *
     * the SPH Phase Control Bit in the SSICR0 register                                  *
     * when SPO is 0, a steady low signal is set on the SSInClk pin                      *
     * when SPO is 1, a steady state High value is placed on the SSInClk pin when data   *
     * is not being transferred                                                          *
     * when SPH is 0, data is captured on the first clock edge transition                *
     * when SPH is 1, data is captured on the second clock edge transition               *
     *                                                                                   *
     * This means we should set SPO to 1 and SPH to 0, this corresponds to               *
     * SSI_FRF_MOTO_MODE_2 in "driverlib/ssi.h"                                          *
     *                                                                                   *
     * The pins should be mapped as such:                                                *
     *     GPIO_PB4_SSI2CLK --> SPC --> SCLK (4)                                         *
     *     GPIO_PB5_SSI2FSS --> CS  --> ~CS  (1)                                         *
     *     GPIO_PB7_SSI2TX  --> SDI --> MOSI (2)                                         *
     *     GPIO_PB6_SSI2RX  --> SDO --> MISO (3)                                         *
     *                                                                                   *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    //Enable the peripheral port GPIOB and enable the SSI module at GPIOB i.e. SSI2.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //Configure the pins associated with SSI module 2 for clock, FSS, RX and TX.
    GPIOPinConfigure(GPIO_PB4_SSI2CLK);
    GPIOPinConfigure(GPIO_PB5_SSI2FSS);
    GPIOPinConfigure(GPIO_PB6_SSI2RX);
    GPIOPinConfigure(GPIO_PB7_SSI2TX);
    GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    //Set the SSI TX module to run from SSI2 with system clock frequency, in SPI 10 mode, as a master at 100 bps with 16 bit data width.
    SSIConfigSetExpClk(SSI2_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_2,SSI_MODE_MASTER,100,16);

    //Enable the SSI2 module.
    SSIEnable(SSI2_BASE);
    char msg [] = {"SSI Port Initialized..."};
    uartPrintln(msg);
}

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
    uartPrintln(welcome);
    initSSI();
//    char msg [10];
//    uint16_t num = 0x8000 | CTRL_REG2 << 8;
//        sprintf(msg, "%d", num);
//        uartPrint("Address: ");
//        uartPrintln(msg);
//        //uartPrint("Post reverse: ");
//        //num = reverse(num);
//        //sprintf(msg, "%d", num);
//        //uartPrintln(msg);
//
//    uartPrintln("attempting to read WHO_AM_I register");
//    SSIDataPut(SSI2_BASE, num);
//    //SSIDataPut(SSI2_BASE, 0x00);
//    uint32_t data = 0;
//    SSIDataGet(SSI2_BASE, &data);
//    uartPrint("WHO_AM_I returned ");
//    sprintf(msg, "%d", data);
//    uartPrintln(msg);
//
//    uartPrintln("");

    while(1){
        SysCtlDelay(20000000);
        UARTCharPut(UART7_BASE, 'A');
    }

    return 0;
}


