/*
 * scan.c
 *
 *  Created on: Oct 29, 2020
 *      Author: cluedtke
 */

#include "lcd.h"
#include "adc.h"
#include "Timer.h"
#include "cyBot_uart.h"
#include "Math.h"
#include "resetSimulation.h"
#include "servo.h"
#include "scan.h"
#include "ping.h"
#include "open_interface.h"
#include "movement.h"

int callCount;


void scan_read(int angle)
{
    int tempDegrees = 0;

    //initialize the various systems
    curWidth = 0;

    objCount = 0;
    degrees = 0;

    if(callCount != 0)
    {
        degrees = 180;
    }

    //init sensor
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    unsigned int initDegree = 311000; //0 degrees = 311,000. 180 degrees = 288,000
    TIMER1_TBPMR_R = initDegree >> 16;
    TIMER1_TBMATCHR_R = initDegree;

        while(degrees<=angle){ //moves servo angle degrees
          if(degrees <= 180) //rotates to 180 degrees
          {
              servo_move(degrees);
          }
          else if(degrees == 182) //at 181 it will rotate the bot to make a 360 scan
          {
              turn_clockwise(sensor_data, 180);
          }
          else if(degrees > 182) //scan the second 180 degrees
          {

              tempDegrees = degrees;
              servo_move(tempDegrees - 180);
          }

        int rawvalue = adc_read();//if the IR sensor reads greater than 550 we assume an object is present and use ping
        if(rawvalue >= 550){ //was 200 increased value to reduce range of sensor
            ping_read(); //use ping to get distance

        }

        else if(rawvalue< 550){ //was 200 increased value to reduce range. if its less than 550 we wont record the object
            lcd_printf("No object detected.");
            curWidth = 0;
            //sendString(curdata);
            if(scanObjs[objCount].width > 0)
            {
                objCount++;
                curWidth = 0;
            }
        }



        timer_waitMillis(150); //1/10 of a second
        degrees = degrees + 2; //increment degrees by 2
        curWidth = curWidth + 2; //increment width by 2

        }
}

void sendString(char *str) //send strings to putty
{
    int i;
    for(i = 0; i < strlen(str); i++)\
    {
        cyBot_sendByte(str[i]);
    }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}



