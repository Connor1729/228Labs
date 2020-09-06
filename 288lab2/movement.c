#include "movement.h";







void Move_Forward(oi_t *sensor, int centimeters){

 bool dir;
 double sum = 0;
 oi_setWheels(500, 500); // move forward; full speed
 while (sum < centimeters) {
     oi_update(sensor);
     if(sensor->bumpLeft)
     {
        dir = false;
        move_back(sensor, dir);
        sum -= 15;
     }
     else if(sensor->bumpRight)
     {
         dir = true;
         move_back(sensor, dir);
         sum -= 15;
     }
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

void move_back(oi_t *sensor, bool direction){ //false is left, true is right
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
             turn_clockwise(sensor, -90);
        }


      for(i=0;i<25;i++){
           oi_update(sensor);
       }
      oi_setWheels(0, 0);

       if(direction == false){
               turn_clockwise(sensor, -90);
           }
           if(direction == true){
                    turn_clockwise(sensor, 90);
                }
}

