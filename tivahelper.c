/*
 *  tivahelper.c
 *
 *  Created on:   Feb 15, 2019
 *  Last updated: Feb 28, 2019
 *  Author:       James Roan
 *
 */
#include "tivahelper.h"

void initClock(void){
    // setup Clock
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}

void initGPIO (void)
{
    // setup GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; // Unlock port F
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    // setup sw1
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    // setup sw2
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void initMSTimer(void (*funct)()){
    SysTickPeriodSet( SysCtlClockGet() / 1000 - 1); //1000 Hz => 1 ms
    SysTickIntRegister(funct); //Register the Interrupt handler as SysTick_IntHandler().
    SysTickIntEnable(); //The SysTick timer auto calls its interrupt handler once it counts to its max value.
    IntMasterEnable();
    SysTickEnable();
}

void initSWInt(void (*funct)()){
    GPIOIntTypeSet(GPIO_PORTF_BASE, SW1 | SW2, GPIO_RISING_EDGE);
    GPIOIntRegister(GPIO_PORTF_BASE, funct);
    GPIOIntEnable(GPIO_PORTF_BASE, SW1 | SW2);
}

void initADCInt(void (*funct)()){
    // when there is data waiting in sequencer 3, an interrupt (funct) will be triggered
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //Enable ADC0.
    // Set the sequencer 3, with 1 sample storage capacity to be triggered by the processor with
    // highest priority.
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    // Set the sequencer 3's sample to be the final sample taken from ADC input pin 0 or PE3 and
    // generate an interrupt when sample is set.
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3); //Enable ADC0's sample sequencer 3.
    IntMasterEnable();
    ADCIntRegister(ADC0_BASE, 3, funct);
    ADCIntEnable(ADC0_BASE, 3);
}

//void initCompInt(void (*funct)()){
//    //Comparator 0 has +ve terminal on PC6 and -ve terminal on PC7 with output on PF0.
//    //comparator 1 has -ve terminal on PC4
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_COMP0);     // Enable comparator 0.
//    ComparatorRefSet(COMP_BASE, COMP_REF_2_371875V); // Set the internal reference voltage to the desired ~2.37v
//    ComparatorConfigure(COMP_BASE, 0,
//                       (COMP_TRIG_NONE |
//                        COMP_INT_BOTH  |
//                        COMP_ASRCP_REF |
//                        COMP_OUTPUT_INVERT));        // Configure to NOT trigger ADC whenever the comparison changes,
//                                                     // create interrupt on both 0 and 1 outputs,
//                                                     // compare the -ve terminal with the reference voltage inverted
//                                                     // because PC7 is the inverting terminal, the comparator output will
//                                                     // be low when PC7 is greater than ~2.34 volts, so we need to invert this.
//    ComparatorConfigure(COMP_BASE, 1,
//                       (COMP_TRIG_NONE |
//                        COMP_INT_BOTH  |
//                        COMP_ASRCP_REF |
//                        COMP_OUTPUT_INVERT));
//    ComparatorIntRegister(COMP_BASE, 0, funct);    // Configure interrupt
//    ComparatorIntRegister(COMP_BASE, 1, funct);    // Configure interrupt
//    ComparatorIntEnable(COMP_BASE, 0);               // Enable interrupt
//    ComparatorIntEnable(COMP_BASE, 1);               // Enable interrupt
//}

//void initADC(void){
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //Enable ADC0.
//    //Set the sequencer 3, with 1 sample storage capacity to be triggered by the analog comparator with highest priority.
//    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_COMP0, 0);
//    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
//    ADCSequenceEnable(ADC0_BASE, 3);
//    ADCIntRegister(ADC0_BASE, 3, ADCInt);
//    ADCIntEnable(ADC0_BASE, 3);
//}

void setLED(unsigned int color){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, color);
}
