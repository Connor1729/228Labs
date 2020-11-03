/*
 * scan.h
 *
 *  Created on: Oct 29, 2020
 *      Author: cluedtke
 */

#ifndef SCAN_H_
#define SCAN_H_

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
