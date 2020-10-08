/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
                         // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1
#include <inttypes.h>
#include "open_interface.h"
#include "resetSimulation.h"
#include "movement.h"


//#warning "Possible unimplemented functions"
#define REPLACEME 0



int main(void) {
	//button_init();
	//lcd_init();
	//int toPrint = -1;
	            // Don't forget to initialze the cyBot UART before trying to use it
	
	// YOUR CODE HERE
	//lcd_printf("Ready");
	
	//while(1)
	//{
	   // toPrint = button_getButton(); //"" + button_getButton();
	    //if(toPrint != 0)
	    //{
	        //lcd_printf(toPrint);
	   // lcd_printf("%" PRIu8 "\n",toPrint);
	   // }
	
      // YOUR CODE HERE
    // Initialize the UART to communciate between CyBot and PuTTy
    //void cyBot_uart_init(void);

    // Send a byte over the UART from CyBot and PuTTy (Buad Rate 115200, No Parity, No Flow Control)
    //void cyBot_sendByte(char data);

    // Cybot WAITs to recive a byte from PuTTy (Buad Rate 115200, No Parity, No Flow Control).
    // In other words, this is a blocking fucntion.
    //int cyBot_getByte(void);
    lcd_init();
    cyBot_uart_init();
    double s1 = 0;
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    while(true)
    {
        int curChar = cyBot_getByte();
       // char curChar = i;//cyBot_getByte();
        //int curChar = cyBot_getByte();
        if(curChar == 'w')
        {
            Move_Forward(sensor_data, 100, s1);
        }
        //else if(strcmp(curChar, "a") == 1)
        else if(curChar == 'a')
        {
           turn_cclockwise(sensor_data, 90);
           Move_Forward(sensor_data, 100, s1);
        }
        //else if(strcmp(curChar, "s") == 1)
        else if(curChar == 's')
        {
            Move_Backward(sensor_data, 100, s1);
        }
        //else if(strcmp(cyBot_getByte(), "d") == 1)
        else if(curChar == 'd')
        {
            turn_clockwise(sensor_data, 90);
            Move_Forward(sensor_data, 100, s1);
        }
        else
        {
            lcd_printf("%c", cyBot_getByte());
        }





    }

    //oi_free(sensor_data);



	
	//}
	
}
