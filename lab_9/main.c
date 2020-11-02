

/**
 * main.c
 */

#include "servo.h"
#include "lcd.h"
#include "Timer.h"
#include "button.h"
#include <math.h>
#include "resetSimulation.h"
#include "open_interface.h"

unsigned int matchValue = 299500; //90 degrees
int mode = 0; // 0 = clockwise 1 = counter clockwise
unsigned int maxValue = 311000; //0 degrees
unsigned int minValue = 288000; //180 degrees
int degrees = 0;

int main(void)
{
    //Q: How does the servo motor work?
    //For example, what are the pulse widths necessary for full clockwise, center,
    //and full counter-clockwise positions?

    //A: Rotates based on a pulse train with a defined period of 20 milliseconds and a variable pulse width that determines the direction and degree of rotation.
    //Full-Clockwise: 2 milliseconds
    //Center: 1.5 Milliseconds
    //Full Counter: 1 Millisecond


    //Q:What Timer1 registers are relevant to this lab?

    //A: TIMER1_CTL_R
    // TIMER1_CFG_R
    // TIMER1_TBMR_R
    // TIMER1_TBILR_R
    // TIMER1_TBPR_R
    // TIMER1_TBPMR_R
    // TIMER1_TBMATCHR_R


    //Q: With a Timer running at the 16 MHz system clock, how many timer ticks are there in 20ms duration?

    //A: 1 second/ 16,000,000 Hz = 1 tick every 0.0000000625 seconds
    //0.02 seconds / 0.0000000625 = 320,000 ticks


    //Q: Describe timer programming for the PWM signal in terms of the high pulse and the low pulse. When is the output pin set? When is the output pin cleared?

    //A: Pulse width pulse period.  When the output pin is set the signal is high(Rising-edge) when the output pin is cleared it is low (Falling edge).
    //resetSimulationBoard();
    servo_init();
    lcd_init();
    button_init();
    timer_init();

    while(1)
    {
        degrees = (int) round((maxValue - matchValue)/127.77);


        if(mode == 0)
        {
            lcd_printf("Match value: %d\nDegrees: %d\nMode: CW", matchValue, degrees);
        }
        else
        {
            lcd_printf("Match value: %d\nDegrees: %d\nMode: CCW", matchValue, degrees);
        }

        if(button_getButton() == '1')
        {
            if(mode == 0)
            {
                matchValue = servo_move(1);
            }
            else
            {
                matchValue = servo_move(-1);
            }
        }
        else if(button_getButton() == '2')
        {
            if(mode == 0)
            {
                matchValue = servo_move(5);
            }
            else
            {
                matchValue = servo_move(-5);
            }
        }
        else if(button_getButton() == '3')
        {
            if(mode == 0)
            {
                mode = 1;
            }
            else
            {
                mode = 0;
            }
        }
        else if(button_getButton() == '4')
        {
            if(mode == 0)
            {
                matchValue = servo_move(-(int)(maxValue - matchValue)/127.77);
            }
            else
            {
                matchValue = servo_move((int)(matchValue - minValue)/127.77);
            }
        }
        else
        {

        }
        timer_waitMillis(50);
    }

    return 0;
}
