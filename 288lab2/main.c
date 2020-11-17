#include "movement.h"
#include "open_interface.h"
#include "resetSimulation.h"


int main(void) {

    //resetSimulationBoard();
    double s1 = 0;

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    Move_Forward(sensor_data, 100, s1);
    Move_Forward(sensor_data, 50, s1);
    Move_Forward(sensor_data, 50, s1);

/*
     Move_Forward(sensor_data, 50, s1);
     turn_clockwise(sensor_data, 90);
     Move_Forward(sensor_data, 50, s1);
     turn_clockwise(sensor_data, 90);
     Move_Forward(sensor_data, 50, s1);
     turn_clockwise(sensor_data, 90);
     Move_Forward(sensor_data, 50, s1);
     turn_clockwise(sensor_data, 90);
*/

    oi_free(sensor_data);




}
