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
    adc_init();
    ping_init();
    lcd_init();
    timer_init();
    cyBot_uart_init();
    char curdata[100];
     degrees = 0;
    servo_init();
    while(1)
    {
        while(degrees<=angle){
          servo_move(degrees);

       // lcd_putc(adc_read());
        //timer_waitMillis(250);

        int rawvalue = adc_read();//if the IR sensor reads less than 200 we assume an object is present and use ping
        if(rawvalue >= 200){
            ping_read();

        }
        else if(rawvalue< 200){
            lcd_printf("No object detected");
           // curdata = "No object detected";
            sendString(curdata);
        }
       /* float y = 103130;
        float cent = y*pow((float)rawvalue, -1.148);
        lcd_printf("raw %d, \n centimeters %f \r \n", rawvalue, cent);
        sprintf(curdata, "raw %d, \n centimeters %f \r \n", rawvalue, cent);
        sendString(curdata);*/


        timer_waitMillis(250);
        degrees++;

        }
    }
}
    void sendString(char str[])
    {
        int i;
        for(i = 0; i < strlen(str); i++)
        {
            cyBot_sendByte(str[i]);
        }

        cyBot_sendByte('\n');
        cyBot_sendByte('\r');

    }



