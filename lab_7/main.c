#include "lcd.h"
#include "adc.h"
#include "Timer.h"

/**
 * main.c
 */
int main(void)
{
    adc_init();
    lcd_init();
    timer_init();

    while(1)
    {
        lcd_putc(adc_read());
        timer_waitMillis(250);
    }

    //while loop
        //get char
        //print
    //wait 1/2 sec

}
