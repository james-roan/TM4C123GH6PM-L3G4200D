/*
 *  tivahelper.h
 *
 *  Created on:   Feb 6, 2019
 *  Last updated: Mar 7, 2019
 *  Author:       James Roan
 */

#ifndef TIVAHELPER_H_
#define TIVAHELPER_H_

#include "inc/tm4c123gh6pm.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
//#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "driverlib/comp.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"

#define RED           GPIO_PIN_1
#define BLU           GPIO_PIN_2
#define GRN           GPIO_PIN_3
#define OFF           0
#define SW1           GPIO_PIN_4
#define SW2           GPIO_PIN_0
#define DEBOUNCE_TIME 100
#define MS_PER_SEC    1000
#define MS_PER_MIN    60000

void initClock   (void);
void initGPIO    (void);
void initMSTimer (void (*funct)());
void initSWInt   (void (*funct)());
void initADCInt  (void (*funct)());
//void initComp    (void (*funct)());
void setLED      (unsigned int color);


#endif /* TIVAHELPER_H_ */
