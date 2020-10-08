/**
 * lab5_template_extra_help.c
 *
 * Description: This is file is meant for those that would like a little
 *              extra help with formatting their code.
 *
 */

#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include "resetSimulation.h"
//"Simulation_User Files_resetSimulation.h"


// Adding global volatile varibles for communcating between 
// your Interupt Service Routine, and your non-interupt code.

//volatile  char uart_data;  // Your UART interupt code can place read data here
//volatile  char flag;       // Your UART interupt can update this flag
                           // to indicate that it has placed new data
                           // in uart_data                     


void main()
{
    //resetSimulationBoard();
    int b = 115200;
	uart_init(b);
	timer_init();
    lcd_init();
    uart_interrupt_init();

    //int count = 0;
    //char stringToSend[21];
    //volatile char curData = 0;

    while(1)
    {
        /*curData = uart_receive();
        uart_sendChar(curData);

        if((curData == '\r' || (strlen(stringToSend) == 20)))
        {
            //uart_sendChar('\r');
            //uart_sendChar('\n');
            lcd_printf("%s", stringToSend);
            memset(stringToSend, 0, 20);
            count = 0;
        }
        else if(curData != 0)
        {
            stringToSend[count] = curData;
            count++;
        }*/

    }

}

