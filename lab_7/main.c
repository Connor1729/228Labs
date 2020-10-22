#include "lcd.h"
#include "adc.h"
#include "Timer.h"
#include "cyBot_uart.h"
#include "Math.h"

/**
 * main.c
 */
/*int main(void)
{
    adc_init();
    lcd_init();
    timer_init();
    cyBot_uart_init();
    char *curdata;

    while(1)
    {
       // lcd_putc(adc_read());
        //timer_waitMillis(250);

        int rawvalue = adc_read();
        float y = 103130;
        float cent = y*pow((float)rawvalue, -1.148);
        lcd_printf("raw %d, \n centimeters %f \r \n", rawvalue, cent);
        sprintf(curdata, "raw %d, \n centimeters %f \r \n", rawvalue, cent);
        sendString(curdata);
        timer_waitMillis(250);

    }

    //while loop
        //get char
        //print
    //wait 1/2 sec

}

void sendString(char *str)
{
    int i;
    for(i = 0; i < strlen(str); i++)\
    {
        cyBot_sendByte(str[i]);
    }

    cyBot_sendByte('\n');
    cyBot_sendByte('\r');

}*/

int main(void)
{

    printf("hey");
  int i;
  char results[100];  // Array to place ADC results
  // Sample Sequencer Input Multiplexer Select (SSMUX0)
  ADC0_SSMUX0_R = 0x710B9453;

  // Sample Sequencer Control (SSCTL0)
  ADC0_SSCTL0_R = 0x44040600;

  // Start ADC conversion
  ADC0_PSSI_R = 0x00000001;

  // Wait for the ADC to complete all of its conversions

  while( (ADC0_RIS_R & 0x00000001) == 0)
  {
  }
  ADC0_ISC_R = 0x00000001;

  // Place the converted values into the results array
  for(i=0;  i <  0x44040600; i++)
  {

       // Place code in for body

  }

  // Print the results
  for(i=0;  i <  0x44040600; i++)
  {
      printf("%d",results[i]);
    //printf(“%d ”, results[i]);
  }
}


