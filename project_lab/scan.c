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
void scan_read(int angle){
    curWidth = 0;
    adc_init();
    ping_init();
    lcd_init();
    timer_init();
    cyBot_uart_init();
    objCount = 0;
    char curdata[100];
     degrees = 0;

    servo_init();

        while(degrees<=angle){
          servo_move(degrees);


        int rawvalue = adc_read();//if the IR sensor reads less than 200 we assume an object is present and use ping
        if(rawvalue >= 200){
            ping_read();

        }
        else if(rawvalue< 200){
            lcd_printf("No object detected");
            curWidth = 0;
            //sendString(curdata);
            if(scanObjs[objCount].width > 0)
            {
                objCount++;
                curWidth = 0;
            }
        }



        timer_waitMillis(250);
        degrees = degrees + 2;
        curWidth = curWidth + 2;

        }



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



