

Skip to content
Using Gmail with screen readers
Meet
New meeting
Join a meeting
Hangouts

Conversations
2.33 GB (15%) of 15 GB used
Manage
Terms · Privacy · Program Policies
Last account activity: 0 minutes ago
Open in 1 other location · Details

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

 //   scan_read(180); // check point one


int main(void) {
    resetSimulationBoard();

    adc_init();
    ping_init();
    lcd_init();
    timer_init();
    cyBot_uart_init();


    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    scan_read(360);




    char stringToSend[100];
    int j;
    int smallestobjidx = 0;
    int distanceToMove = 0;
            int curWid = 1000;
            sendString("\r \n \n Object# \t Angle \t Distance \t Width \t Linear Width \r \n");
            for(j = 0; j < objCount; j++)
            {
                //double h = scanObjs[j].curpdistance*cos((scanObjs[j].width/2.0)/57.2958);
                if(curWid > sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)) ))
                {
                    curWid = sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)) );
                    smallestobjidx = j;
                }
                //double h = scanObjs[j].curpdistance*cos((scanObjs[j].width/2.0)/57.2958);
                //2*(sqrt((pow(scanObjs[j].curpdistance/1.0, 2.0)- pow(h, 2.0))))
                sprintf(stringToSend, "%d \t %d \t %d \t %d \t %f", j, scanObjs[j].angle, scanObjs[j].curpdistance, scanObjs[j].width, sqrt((2*pow(scanObjs[j].curpdistance, 2)) - (2*scanObjs[j].curpdistance*scanObjs[j].curpdistance*cos(scanObjs[j].width/57.2958)) ));
                sendString(stringToSend);
            }//%2.2f

            timer_waitMillis(100);
            if(scanObjs[smallestobjidx].angle >= 270)
            {
                turn_clockwise(sensor_data, scanObjs[smallestobjidx].angle - 270);
            }
            if(scanObjs[smallestobjidx].angle <= 90)
            {
                turn_clockwise(sensor_data, scanObjs[smallestobjidx].angle + 90);
            }
            else
            {
                turn_cclockwise(sensor_data, -(270 - scanObjs[smallestobjidx].angle));
            }
            //turn_clockwise(sensor_data, 90);
            //turn_cclockwise(sensor_data, scanObjs[smallestobjidx].angle);
            timer_waitMillis(100);
            distanceToMove = scanObjs[smallestobjidx].curpdistance - 13; //so dont bump and cause move things


            Move_Forward(sensor_data, distanceToMove, 0);












}




main.txt
Displaying sacan.txt.
