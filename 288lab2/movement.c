
#include "movement.h"

void Move_Forward(oi_t *sensor, int centimeters, double sum){

 bool dir;
 int distanceToTravel = centimeters * 10;
 oi_setWheels(500, 500); // move forward; full speed
 while (sum < distanceToTravel) {
     oi_update(sensor);
     if(sensor->bumpLeft)
     {
        dir = false;
        move_back(sensor, dir, sum, centimeters);
     }
     else if(sensor->bumpRight)
     {
         dir = true;
         move_back(sensor, dir, sum, centimeters);
     }
     sum += sensor->distance;
 }
 oi_setWheels(0, 0); // stop


 }

void turn_clockwise(oi_t *sensor, int degrees){


     double sum = 0;
     oi_setWheels(25, -25); // move forward; full speed
    while (sum < degrees) {
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop

}

void turn_cclockwise(oi_t *sensor, int degrees){


     double sum = 0;
     oi_setWheels(-25, 25); // move forward; full speed
    while (sum > degrees) {
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop

}



void move_back(oi_t *sensor, bool direction, double curSum, int curCent){ //false is left, true is right
    int i;
    oi_update(sensor);

    oi_setWheels(-500, -500);
    for( i = 0; i <15; i++){
        oi_update(sensor);
    }
    oi_setWheels(0, 0);

    if(direction == false){
         turn_clockwise(sensor, 90);
    }

    if(direction == true){
             turn_cclockwise(sensor, -90);
        }

    oi_setWheels(500, 500);
      for(i=0;i<25;i++){
           oi_update(sensor);
       }
      oi_setWheels(0, 0);

    if(direction == false){
       turn_cclockwise(sensor, -90);
    }
    if(direction == true){
        turn_clockwise(sensor, 90);
     }

    double sumToReturn = curSum - 150;

    Move_Forward(sensor, curCent, sumToReturn);
}

