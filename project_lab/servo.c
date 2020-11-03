/*
 * servo.c
 *
 *  Created on: Oct 22, 2020
 *      Author: cml
 */
#include <stdio.h>
#include <stdlib.h>
#include "servo.h"
#include "Timer.h"
#include "stdint.h"
#include "lcd.h"

void servo_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x2;
    GPIO_PORTB_AFSEL_R |= 0b00100000; //pg 1344
    GPIO_PORTB_DEN_R |= 0b00100000; //pg 682
    GPIO_PORTB_DIR_R |= 0b0010000;

    GPIO_PORTB_PCTL_R |= 0x700000;
    SYSCTL_RCGCTIMER_R |= 0x02;
    timer_waitMillis(1);
    TIMER1_CTL_R &= ~0b100000000;
    TIMER1_TBPR_R = 0x4;

    TIMER1_TBILR_R =0xE200;
    TIMER1_CFG_R |= 0x00000004;
    TIMER1_TBMR_R |= 0x0000000A;

    TIMER1_TBPMR_R = 0b00000100;
    TIMER1_TBMATCHR_R = 0xDA30;
   // TIMER1_IMR_R |= 0x01;

    TIMER1_CTL_R |= 0b100000000;
}

int servo_move(float degrees)
{
     int degrees2 = degrees;

 //int  miliseconds = (.0056*degrees)+1;
 int clockticks = (-128*degrees)+319000;
// 32000- clockcycles = prescale/match register
 int prescale = clockticks;
 prescale = prescale>>16;
 int match = clockticks;
 match = match & 0xFFFF;
 TIMER1_TBPMR_R = prescale;
 TIMER1_TBMATCHR_R = match;
 char toprint[100];
 snprintf(toprint,sizeof(toprint),"%.2f", degrees);
lcd_printf(toprint);


return 1;
}
