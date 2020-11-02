

/**
 * main.c
 */

#include "ping.h"
#include "Timer.h"
#include "resetSimulation.h"
#include "lcd.h"
void main(void) {
    resetSimulationBoard();
    ping_init();
    lcd_init();

    while(1){
        ping_read();
        timer_waitMillis(500);
    }

	return 0;
}
