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

#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
                         // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1

#include "cyBot_Scan.h"  // For scan sensors 


//#warning "Possible unimplemented functions"
#define REPLACEME 0


// Defined in button.c : Used to communicate information between the
// the interupt handeler and main.
extern volatile int button_event;
extern volatile int button_num;


int main(void) {
    //resetSimulationBoard();
	button_init();
	lcd_init();
	            // Don't forget to initialze the cyBot UART before trying to use it
	//init_button_interrupts();

    // (Uncomment ME for PuTTy to CyBot UART init part of lab) cyBot_uart_init_clean();  // Clean UART initialization, before running your UART GPIO init code
	cyBot_uart_init_clean();


	// Complete this code for configuring the  (GPIO) part of UART initialization
      SYSCTL_RCGCGPIO_R |= 0b000010;

      timer_waitMillis(1);            // Small delay before accessing device after turning on clock

      GPIO_PORTB_AFSEL_R |= 0b00000011;
      GPIO_PORTB_PCTL_R &= 0xFFFFFF11;     // Force 0's in the disired locations
      GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the disired locations

      GPIO_PORTB_DEN_R |= 0b00000011;

      GPIO_PORTB_DIR_R &= 0b11111110;      // Force 0's in the disired locations
      GPIO_PORTB_DIR_R |= 0b00000001;      // Force 1's in the disired locataions
    
    // (Uncomment ME for UART init part of lab) cyBot_uart_init_last_half();  // Complete the UART device initialization part of configuration
      cyBot_uart_init_last_half();

	// Initialze scan sensors
      cyBOT_init_Scan();



	// YOUR CODE HERE
	char c;
	int my_angle = 180;
	int i;
	cyBOT_Scan_t x;
	//stringToSend = "Angle" + '\t' + "PING distance" + '\t' + "IR Raw Value";
	char stringToSend[100];

	while(1)
	{
	    c = cyBot_getByte_blocking();
	    if(c == 'm')
	    {
	        sendString("Angle \t PING distance \t IR Raw value \n");
	        for(i = 0; i <= my_angle; i = i +5)
	        {
	            cyBOT_Scan(my_angle, &x);
	            //stringToSend = "" + i + '\t' + x.sound_dist + '\t' + x.IR_raw_val;
	            sprintf(stringToSend, "%d \t %2.2f \t %d", i, x.sound_dist, x.IR_raw_val);
	            //char newT = stringToSend.replace('&', "\t");'
	            sendString(stringToSend);
	        }
	    }




	    //lcd_printf("%c", cyBot_getByte_blocking());

	    //button_event = 0;
	
      // YOUR CODE HERE
	    //sprintf
	    //send string function
  


	
	}
	
}


void sendString(char str[])
{
    char *ptr;
    ptr = str;
    while(*ptr != '\0')
    {
        cyBot_sendByte(*ptr++);
    }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');

}
