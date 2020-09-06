/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Describtion: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int main (void) {

    char message[] = "Microcontrollers are lots of fun!";
    char messageToPrint[19];
    int i;

    for(i = 0; i < 20; i++)
    {
        messageToPrint[i] = " ";
    }


    lcd_init();
    timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called
	              // and enables time functions (e.g. timer_waitMillis)
    int msgIdx = 0;


    //lcd_puts("Hello, world");

    //lcd_init();

    while(1)
    {
        if(msgIdx == strlen(message))
        {
            msgIdx = 0;
        }
        for(i = 1; i < 20; i++)
        {
            messageToPrint[i-1] = messageToPrint[i];
        }
        messageToPrint[19] = message[msgIdx];
        lcd_init();
        lcd_printf(messageToPrint);
        timer_waitMicros(300);
        msgIdx++;
    }




	   // Initialize the the LCD screen.  This also clears the screen.

	// Clear the LCD screen and print "Hello, world" on the LCD


	 //lcd_puts("Hello, world");// Replace lcd_printf with lcd_puts
                                 // step through in debug mode
                                 // and explain to TA how it
                                 // works


    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
    // NOTE: For time fuctions see Timer.h

	return 0;
}
