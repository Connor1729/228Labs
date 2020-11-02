/*
 * servo.h
 *
 *  Created on: Oct 22, 2020
 *      Author: kaseyk
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "lcd.h"
#include "Timer.h"
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

void servo_init(void);
int servo_move(float degrees);



#endif /* SERVO_H_ */
