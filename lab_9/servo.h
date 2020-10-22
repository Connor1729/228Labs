/*
 * servo.h
 *
 *  Created on: Oct 22, 2020
 *      Author: cml
 */
#include "stdint.h"


void servo_init(void);
int servo_move(float degrees);
uint32_t RCC, high = 1;

