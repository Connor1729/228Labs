/*
 * adc.c
 *
 *  Created on: Oct 8, 2020
 *      Author: cml
 */
#include "adc.h"
#include "timer.h"



void adc_init(void)
{ //pg 816
    SYSCTL_RCGCADC_R |= 0x01; //pg 352
    SYSCTL_RCGCGPIO_R |= 0b00000010; //pg 340 & 801
    GPIO_PORTB_AFSEL_R |= 0b00010000; //pg 1344
    GPIO_PORTB_DEN_R |= 0b00010000; //pg 682
    GPIO_PORTB_AMSEL_R |= 0b00010000; //pg 687
    ADC0_ACTSS_R |= 0b11111110;
    ADC0_SSCTL0_R  &= 0xFFF0;
    ADC0_SSMUX0_R |= 0xA;
    ADC0_SSCTL0_R |= 0b0110;
    ADC0_ACTSS_R |= 0b00000001;
}



int adc_read(void)
{
    ADC0_PSSI_R=ADC_PSSI_SS0;
    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){
    //wait
    }
    ADC0_ISC_R=ADC_ISC_IN0; //clear interrupt
    return ADC0_SSFIFO0_R;


}
