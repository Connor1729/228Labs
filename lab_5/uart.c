/*
*
*   uart_extra_help.c
* Description: This is file is meant for those that would like a little
*              extra help with formatting their code, and followig the Datasheet.
*/

#include "uart.h"
#include "timer.h"

void uart_init(int baud)
{
    SYSCTL_RCGCGPIO_R |= 0b000010;
    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)

    GPIO_PORTB_AFSEL_R |= 0b00000011;
    GPIO_PORTB_PCTL_R &= 0xFFFFFF11;     // Force 0's in the disired locations
    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the disired locations

    GPIO_PORTB_DEN_R |= 0b00000011;

    GPIO_PORTB_DIR_R &= 0b11111110;      // Force 0's in the disired locations
    GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the disired locataions

    //double fbrd;
    //int    ibrd;

    //fbrd = 16000000/(16*baud);
    //ibrd = (int)((1/fbrd) * 64 + 0.5);

    UART1_CTL_R &= 0b11111110;      // disable UART1 (page 918)

    UART1_IBRD_R = 8;
    UART1_FBRD_R = 44; //8.68055555556

    UART1_LCRH_R |= 0b01100000;
    UART1_CC_R = 0b0000;
    UART1_CTL_R |= 0b1100000001;
}

void uart_sendChar(char data)
{

    //Flag register
    //FR on datasheet, 2 bits, 1 is send & 1 is recieve, mask & check 2 bit fifo
    // recieve wait while fifo is empty
    //When no longer empty read DR(data register)


    //When sending wait tell buffer is no longer full
    //

    while(UART1_FR_R & 0x20)
    {

    }
    UART1_DR_R = data;



}

int uart_receive(void)
{
    int data = 0;
    while(UART1_FR_R & UART_FR_RXFE)
    {

    }
    data = UART1_DR_R & 0xFF;

    return data;


}

void uart_sendStr(const char *data)
{
    int dlen = strlen(data);
    int i;
    for(i = 0; i < dlen; i++)
    {
        uart_sendChar(data[i]);
    }

}

// _PART3


void uart_interrupt_init()
{
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0b0010000; //enable interrupt on receive - page 924

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    //NVIC_EN0_R |= 0x00000058; //enable uart1 interrupts - page 104
    NVIC_EN0_R |= 0b01000000;

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number
}

void uart_interrupt_handler()
{

    if(UART1_MIS_R & UART_MIS_RXMIS) //Check the Masked Interrup Status, received a byte
    {
        //copy the data

        int receivedData = uart_receive();
        uart_sendChar(receivedData);
        UART1_ICR_R |= UART_ICR_RXIC; //Clear the interrup
    }
    /*else if(UART1_MIS_R & UART_MIS_TXMIS) //Check the Masked Interrup Status, sent a byte
    {
        //copy the data, sent so no data to copy, just clear
        UART1_ICR_R |= UART_ICR_TXIC; //Clear the interrup
    }*/

}
