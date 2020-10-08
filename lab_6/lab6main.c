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
#include "open_interface.h"
#include "movement.h"


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

      cyBot_uart_init();
      double s1 = 0;
      oi_t *sensor_data = oi_alloc();
      oi_init(sensor_data);



	// YOUR CODE HERE
	char c;
	int my_angle = 180;
	int i;
	cyBOT_Scan_t x;
	//stringToSend = "Angle" + '\t' + "PING distance" + '\t' + "IR Raw Value";
	char stringToSend[100];

	float curDist = 0;

	struct cybotObject
	{
	    int angle;
	    int curpdistance;
	    int width;
	};


	struct cybotObject scanObjs[10];
	int objCount = 0;
	int cwidth = 0;
	int ccurpdistance = 0;
	int cangle = 0;

	//int curWidth = 0;

	while(1)
	{
	    c = cyBot_getByte_blocking();
	    if(c == 'm')
	    {
	        sendString("\r \n Degrees \t Distance (cm) \t \n");
	        for(i = 0; i <= my_angle; i = i + 2)
	        {
	            cyBOT_Scan(i, &x);
	            if(curDist - 1 < x.sound_dist < curDist + 1)
	            {
	                cwidth = cwidth + 2;
	                ccurpdistance = curDist;
	                cangle = i;

	            }
	            else if (x.sound_dist < 300)
	            {
	                scanObjs[objCount].width = cwidth;
	                cwidth = 0;
	                scanObjs[objCount].curpdistance = ccurpdistance;
	                ccurpdistance = 0;
	                scanObjs[objCount].angle = cangle;
	                cangle = 0;
	                objCount++;
	                //my_angle = 0;
	            }
	            else if (x.sound_dist > 300)
	            {
	                cwidth = 0;
	                ccurpdistance = 0;
	                cangle = 0;
	            }
	            //else if(x.sound_dist == curDist && )
	            sprintf(stringToSend, "%d \t %2.2f \t %d", i, x.sound_dist);
	                //increment 'width'
	                //record its distance and its angle

	            curDist = x.sound_dist;
	            //stringToSend = "" + i + '\t' + x.sound_dist + '\t' + x.IR_raw_val;
	            //sprintf(stringToSend, "%d \t %2.2f \t %d", i, x.sound_dist);
	            //char newT = stringToSend.replace('&', "\t");'
	            sendString(stringToSend);
	        }

	        if(ccurpdistance < 300)
	        {

	        }

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



	        turn_cclockwise(sensor_data, 180-scanObjs[smallestobjidx].angle);




	      }
	   }




	    //lcd_printf("%c", cyBot_getByte_blocking());

	    //button_event = 0;
	
      // YOUR CODE HERE
	    //sprintf
	    //send string function
  



	
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
