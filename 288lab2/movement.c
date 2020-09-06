
#include <stdio.h>;


#include "open_interface.h";







void Move_Forward(oi_t *sensor, int centimeters){


int i;
 double sum = 0;
 oi_setWheels(500, 500); // move forward; full speed
 while (sum < centimeters) {

 oi_update(sensor);




 sum += sensor->distance;
 }
 oi_setWheels(0, 0); // stop


 }

void turn_clockwise(oi_t *sensor, int degrees){


     double sum = 0;
     oi_setWheels(200, -200); // move forward; full speed
    while (sum < degrees) {
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop

}

void move_back(oi_t *sensor){
    int i;
    bool direction;
     double sum = 0;
     oi_setWheels(500, 500); // move forward; full speed
     while (sum < centimeters) {

     oi_update(sensor);

     if(sensor_data->bumpLeft || senser_data->bumpRight){
          oi_setWheels(-500, -500);
       for( i = 0; i <15; i++){
           oi_update(sensor);
           sum -= sensor->distance;
           if(sensor_data->bumpLeft){
               turn_clockwise(sensor_data, 90);
               direction = true;
           }
           if(sensor_data->bumpRight){
                    turn_clockwise(sensor_data, -90);
                    direction = false;
                }
       for(i=0;i<25;i++){
           oi_update(sensor);
              sum -= sensor->distance;


       }
       if(sensor_data->bumpLeft){
               turn_clockwise(sensor_data, -90);
           }
           if(sensor_data->bumpRight){
                    turn_clockwise(sensor_data, 90);
                }
       }

     }
     sum += sensor->distance;
     }
     oi_setWheels(0, 0); // stop
}

