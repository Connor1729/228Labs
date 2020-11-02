/*
 * adc.c
 *
 *  Created on: Oct 8, 2020
 *      Author: kaseyk
 */
#include "adc.h"
void adc_init(void)
{
    //module initialization
    SYSCTL_RCGCADC_R |= 0x00000001;
    SYSCTL_RCGCGPIO_R |= 0x00000002;
    GPIO_PORTB_AFSEL_R |= 0x00000010;
    GPIO_PORTB_AMSEL_R |= 0x00000010;
    GPIO_PORTB_DEN_R &= 0xFFFFFFFEF;
    GPIO_PORTB_DIR_R &= 0xFFFFFFFEF;

    //sample sequencer configuration
    ADC0_ACTSS_R &= 0xFFFFFFFE;
    ADC0_EMUX_R &= 0xFFFFFFF0;
    ADC0_SSMUX0_R |= 0x0000000A;
    ADC0_SSCTL0_R |= 0x00000006;
    ADC0_SAC_R |= 0x00000004; //averaging
    ADC0_ACTSS_R |= 0x00000001;

}

int adc_read(void)
{
    ADC0_PSSI_R |= 0x00000001;
    //wait for FIFO to fill
    while(ADC0_RIS_R & 0x00000001 == 0)
    {
    }
    ADC0_ISC_R |= 0x00000001;
    //return the value
    return ADC0_SSFIFO0_R; // & 0x00000FFF

}


