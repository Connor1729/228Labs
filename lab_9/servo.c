/*
 * servo.c
 *
 *  Created on: Oct 22, 2020
 *      Author: cml
 */
#include "servo.h"
#include "Timer.h"
#include "stdint.h"
#include "lcd.h"

void servo_init(void)
{
    GPIO_PORTB_AFSEL_R |= 0b00010000; //pg 1344
    GPIO_PORTB_DEN_R |= 0b00010000; //pg 682

    //SYS CTL R
    RCC = (SYSCTL_RCC_XTAL_16MHZ|SYSCTL_RCC_PWRDN|SYSCTL_RCC_BYPASS|SYSCTL_RCC_PWMDIV_16);
    SYSCTL_RCC_R = RCC;
    SYSCTL_RCGCWTIMER_R |= 0x04;
    SYSCTL_RCGCGPIO_R |= 0x28;

    //GPIO_PORTB_PCTL_R |= 0x7000;

    TIMER1_TBPR_R = 15;
    TIMER1_TBMATCHR_R = 0;
    TIMER1_TBILR_R =65535;
    TIMER1_CFG_R |= 0x00000004;

   // TIMER1_TAMR_R = 0x07;
   // TIMER1_IMR_R |= 0x01;

    TIMER1_CTL_R |= 0b10000000;
}

int servo_move(float degrees)
{
    float i;
    for(i = 0; i < degrees; i++)
    {
        TIMER1_TAMATCHR_R = i;
        high += 5;
        lcd_puts((char)degrees);
        timer_waitMillis(1);
        if(high >= 39600)
        {
            high = 1;
        }
    }
    return 1;


}

