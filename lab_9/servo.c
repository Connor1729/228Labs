/*
 * servo.c
 *
 *  Created on: Oct 22, 2020
 *      Author: kaseyk
 */
#include "servo.h"
#include "lcd.h"
#include "Timer.h"
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

void servo_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x00000002;

    GPIO_PORTB_AFSEL_R |= 0x00000020;
    GPIO_PORTB_PCTL_R |= 0x00700000;
    GPIO_PORTB_DEN_R |= 0x00000020;
    GPIO_PORTB_DIR_R |= 0x00000020;

    SYSCTL_RCGCTIMER_R |= 0x00000002;

    TIMER1_CTL_R &= 0xFFFFFEFF;
    TIMER1_CFG_R |= 0x00000004;
    TIMER1_TBMR_R |= 0x0000000A;
    //320,000 for period
    TIMER1_TBPR_R = 0x04;
    TIMER1_TBILR_R = 0xE200;
    unsigned int initDegree = 299500; //0 degrees = 311,000. 180 degrees = 288,000
    TIMER1_TBPMR_R = initDegree >> 16;
    TIMER1_TBMATCHR_R = initDegree;
    //296,000
    //TIMER1_TBPMR_R = 0x04;
    //TIMER1_TBMATCHR_R = 0x8440;
    TIMER1_CTL_R |= 0x00000100;

}

int servo_move(float degrees)
{
    unsigned int newPosition = 0;
    newPosition = (int) (TIMER1_TBPMR_R << 16) + TIMER1_TBMATCHR_R - (127.77 * degrees);

    if(newPosition > 311000){
        newPosition = 311000;
    }

    if(newPosition < 288000){
            newPosition = 288000;
    }
    TIMER1_TBPMR_R = newPosition >> 16;
    TIMER1_TBMATCHR_R = newPosition;
    return newPosition;
}



