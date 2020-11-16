    /**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "resetSimulation.h"
#include "adc.h"
#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
#include "ping.h"                        // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1

#include "cyBot_Scan.h"  // For scan sensors
#include "open_interface.h"
#include "movement.h"
#include <math.h>
#include <stdio.h>

#include "scan.h"


int main(void) {
    //resetSimulationBoard();

    adc_init();
    ping_init();
    lcd_init();
    timer_init();
    cyBot_uart_init();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);


    bool delievedPackage = false;
    /*
    double distTraveled = 0;


    while(delievedPackage == false)
    {
        Move_Forward(sensor_data, 30, distTraveled);
        distTraveled = distTraveled + 30;
        if(distTraveled > 100)
        {
            delievedPackage = true;
        }

    }*/


    scan_read(360);

    char stringToSend[100];
    int j;
    volatile int smallestobjidx = 0;
    volatile int smallestobjidx2 = 0;
    int distanceToMove = 0;
            int curWid = 1000;
            int secWidth = 1000;
            sendString("\r \n \n Object# \t Angle \t Distance \t Width \t Linear Width \r \n");
            for(j = 0; j < objCount; j++)
            {

                sprintf(stringToSend, "%d \t %d \t %d \t %d \t %f", j, scanObjs[j].angle, scanObjs[j].curpdistance, scanObjs[j].width, sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)) ));
                sendString(stringToSend);
                if(curWid > sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958))))
                {
                    curWid = sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)));
                    smallestobjidx2 = smallestobjidx;
                    smallestobjidx = j;
                    if(smallestobjidx != smallestobjidx2)
                    {
                        secWidth = sqrt((2*pow(scanObjs[smallestobjidx2].curpdistance, 2)) - (2*scanObjs[smallestobjidx2].curpdistance*scanObjs[smallestobjidx2].curpdistance*cos(scanObjs[smallestobjidx2].width/57.2958)));
                    }
                }
                else
                {
                    if(smallestobjidx == smallestobjidx2)
                    {
                        smallestobjidx2 = j;
                        secWidth = sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)));
                    }
                    else if(secWidth > sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958))))
                    {
                        secWidth = sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)));
                        smallestobjidx2 = j;
                    }
                }

            }
            timer_waitMillis(100);

            int firstAngle = scanObjs[smallestobjidx].angle;
            int secondAngle = scanObjs[smallestobjidx2].angle;

            int firstWidth = sqrt((2*pow(scanObjs[smallestobjidx].curpdistance, 2)) - (2*scanObjs[smallestobjidx].curpdistance*scanObjs[smallestobjidx].curpdistance*cos(scanObjs[smallestobjidx].width/57.2958)));
            int secondWidth = sqrt((2*pow(scanObjs[smallestobjidx2].curpdistance, 2)) - (2*scanObjs[smallestobjidx2].curpdistance*scanObjs[smallestobjidx2].curpdistance*cos(scanObjs[smallestobjidx2].width/57.2958)));

            int angleToTurn;

            if(firstWidth < 6.7 && secondWidth < 6.7)
            {

                sprintf(stringToSend, "The First Angle Is: %d at index: %d", firstAngle, smallestobjidx);
                sendString(stringToSend);

                sprintf(stringToSend, "The Second Angle Is: %d at index: %d", secondAngle, smallestobjidx2);
                sendString(stringToSend);

                if(secondAngle - firstAngle <= 180)
                {
                    angleToTurn = abs(((secondAngle - firstAngle)/2)+firstAngle);
                }
                else
                {
                    angleToTurn = abs((((360 - secondAngle) + firstAngle)/2) + secondAngle);
                }
                sprintf(stringToSend, "The Angle To Turn is: %d", angleToTurn);
                sendString(stringToSend);

                if(angleToTurn >= 270)
                {
                    turn_clockwise(sensor_data, angleToTurn - 270);
                }
                else if(angleToTurn <= 90)
                {
                    turn_clockwise(sensor_data, angleToTurn + 90);
                }
                else
                {
                    turn_cclockwise(sensor_data, -(270 - angleToTurn));
                }

                timer_waitMillis(100);
                distanceToMove = (scanObjs[smallestobjidx].curpdistance + scanObjs[smallestobjidx2].curpdistance)/2; //so dont bump and cause move things

                Move_Forward(sensor_data, distanceToMove - 10, 0);

                if(scanObjs[smallestobjidx].curpdistance > scanObjs[smallestobjidx2].curpdistance)
                {
                    if(angleToTurn >= 270)
                    {
                        turn_cclockwise(sensor_data, angleToTurn - 270);
                    }
                    else if(angleToTurn <= 90)
                    {
                         turn_cclockwise(sensor_data, angleToTurn + 90);
                    }
                    else
                    {
                         turn_clockwise(sensor_data, -(270 - angleToTurn));
                    }
                    turn_clockwise(sensor_data, 90);
                    Move_Forward(sensor_data, 15, 0);
                }
                else if(scanObjs[smallestobjidx].curpdistance < scanObjs[smallestobjidx2].curpdistance)
                {
                    if(angleToTurn >= 270)
                    {
                        turn_cclockwise(sensor_data, angleToTurn - 270);
                    }
                    else if(angleToTurn <= 90)
                    {
                         turn_cclockwise(sensor_data, angleToTurn + 90);
                    }
                    else
                    {
                         turn_clockwise(sensor_data, -(270 - angleToTurn));
                    }
                    turn_cclockwise(sensor_data, 90);
                    Move_Forward(sensor_data, 15, 0);
                }

            }












}




