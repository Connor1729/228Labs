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
void scan_read(int angle){
    int tempDegrees = 0;
    curWidth = 0;
    adc_init();
    ping_init();
    lcd_init();
    timer_init();
    cyBot_uart_init();
    objCount = 0;
    char curdata[100];
    degrees = 0;
    if(callCount != 0)
    {
        degrees = 180;
    }

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    servo_init();

        while(degrees<=angle){
          if(degrees < 180)
          {
              servo_move(degrees);
          }
          else if(degrees == 180)
          {
              turn_clockwise(sensor_data, 180);
          }
          else if(degrees > 180)
          {
              tempDegrees = degrees;
              servo_move(tempDegrees - 180);
          }

        int rawvalue = adc_read();//if the IR sensor reads less than 200 we assume an object is present and use ping
        if(rawvalue >= 550){ //was 200
            ping_read();

        }

        else if(rawvalue< 550){ //was 200
            lcd_printf("No object detected.");
            curWidth = 0;
            //sendString(curdata);
            if(scanObjs[objCount].width > 0)
            {
                objCount++;
                curWidth = 0;
            }
        }



        timer_waitMillis(250);
        degrees = degrees + 1;
        curWidth = curWidth + 1;

        }
servo_move(0);


}

void sendString(char *str)
{
    int i;
    for(i = 0; i < strlen(str); i++)\
    {
        cyBot_sendByte(str[i]);
    }
    /*char *ptr;
    ptr = str;
    while(*ptr != '\0')
    {
        cyBot_sendByte(*ptr++);
    }*/
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');

}



