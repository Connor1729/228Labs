/*
 * scan.h
 *
 *  Created on: Oct 29, 2020
 *      Author: cluedtke
 */

#ifndef SCAN_H_
#define SCAN_H_
#include "lcd.h"
#include "adc.h"
#include "Timer.h"
#include "cyBot_uart.h"
#include "Math.h"
#include "resetSimulation.h"
#include "servo.h"
#include "ping.h"
extern int callCount;
void scan_read(int angle);

void sendString(char str[]);

struct cybotObject
{
        int angle;
        int curpdistance;
        int width;
};

struct cybotObject scanObjs[10];
int objCount;
int curWidth;



#endif /* SCAN_H_ */
