/*
 * ping.h
 *
 *  Created on: Oct 15, 2020
 *      Author: benbrown
 */

#ifndef PING_H_
#define PING_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "lcd.h"

void ping_init(void);
void ping_read(void);
void TIMER3B_Handler(void);
void sendString(char str[]);
int degrees;

#endif /* PING_H_ */
