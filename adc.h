/*
 * adc.h
 *
 *  Created on: Oct 8, 2020
 *      Author: kaseyk
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

void adc_init(void);
int adc_read(void);



#endif /* ADC_H_ */
