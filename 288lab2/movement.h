#include <stdio.h>
#include "open_interface.h"
#include "lcd.h"
#include "resetSimulation.h"

void Move_Forward(oi_t *sensor, int centimeters, double sum);
void turn_clockwise(oi_t *sensor, int degrees);
void move_back(oi_t *sensor, bool direction, double curSum, int curCent);







