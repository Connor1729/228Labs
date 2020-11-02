/*
 * ping.c
 *
 *  Created on: Oct 15, 2020
 *      Author: benbrown
 */
#include "ping.h"
#include "Timer.h"
#include "driverlib/interrupt.h"
#include "lcd.h"

volatile int current_time = 0;
volatile int prev_time = 0;
volatile int edge_count = 0;


void ping_init(void) {

    //GPIO
    SYSCTL_RCGCGPIO_R |= 0x00000002;
    long delay = SYSCTL_RCGCGPIO_R;
    GPIO_PORTB_AFSEL_R |= 0x00000008;
    GPIO_PORTB_PCTL_R |= 0x00007000;
    GPIO_PORTB_DEN_R |= 0x00000008;
    GPIO_PORTB_DIR_R &= 0x000000F7;

    //11.4.4
    SYSCTL_RCGCTIMER_R |= 0x00000008;
    delay = SYSCTL_RCGCTIMER_R;
    TIMER3_CTL_R &= 0xFFFFFEFF;
    TIMER3_CFG_R |= 0x00000004;
    TIMER3_TBMR_R = 0x00000007;
    TIMER3_CTL_R |= 0x00000C00;
    TIMER3_TBPR_R |= 0x000000FF;
    TIMER3_TBILR_R |= 0x0000FFFF;
    TIMER3_ICR_R |= 0x000000400;
    TIMER3_IMR_R |= 0x0000400;
    TIMER3_CTL_R |= 0x00000100;
    NVIC_EN1_R |= 0x00000010;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable();
}

void ping_read(void) {
    GPIO_PORTB_AFSEL_R &= 0x000000F7;
    GPIO_PORTB_DIR_R |= 0x00000008;
    GPIO_PORTB_DATA_R &= 0x000000F7;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R |= 0x00000008;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= 0x000000F7;
    GPIO_PORTB_DIR_R &= 0x000000F7;
    GPIO_PORTB_AFSEL_R |= 0x00000008;
    //GPIO_PORTB_PCTL_R |= 0x00007000;

    double width, distance = 0;
    int overflow_count = 0;

    while(edge_count < 2);

    width = (double)prev_time - current_time;

    if(current_time > prev_time){
        overflow_count++;
        width = (double)(0xFFFFFF - current_time) + prev_time;
    }
    distance = (((width / 16) / 1000) / 2);
    //speed of sound 340m/s. multiply by 100 to get cm/s. divide by 1000 to get cm/ms.
    distance *= 34;

    char str[100];
    sprintf(str, "Width: %.0f\nDistance: %.0f\nOverflows: %d\n",width, distance, overflow_count);
    lcd_printf(str);
    edge_count = 0;
}

void TIMER3B_Handler(void) {

    if(edge_count == 0) {
        prev_time = current_time;
        current_time = TIMER3_TBV_R;
        edge_count = 1;
    }
    else if(edge_count == 1) {
        prev_time = current_time;
        current_time = TIMER3_TBV_R;
        edge_count = 2;
    }
    TIMER3_ICR_R |= 0x00000400;
}






