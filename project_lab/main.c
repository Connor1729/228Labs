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


#include "scan.h"

 //   scan_read(180); // check point one


int main(void) {
    //resetSimulationBoard();
    scan_read(180);

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    char stringToSend[100];
    int j;
    int smallestobjidx = 0;
            int curWid = 1000;
            sendString("\r \n \n Object# \t Angle \t Distance \t Width \r \n");
            for(j = 0; j < objCount; j++)
            {
                if(curWid > scanObjs[j].width)
                {
                    curWid = scanObjs[j].width;
                    smallestobjidx = j;
                }
                sprintf(stringToSend, "%d \t %d \t %d \t %d", j, scanObjs[j].angle, scanObjs[j].curpdistance, scanObjs[j].width);
                sendString(stringToSend);
            }//%2.2f

            timer_waitMillis(100);

            turn_cclockwise(sensor_data, 180-scanObjs[smallestobjidx].angle);
            timer_waitMillis(100);
            int distanceToMove = scanObjs[smallestobjidx].curpdistance - 10; //so dont bump and cause move things
            Move_Forward(sensor_data, distanceToMove, 0);












}




