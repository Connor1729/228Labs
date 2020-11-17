#include "movement.h"

void Move_Forward(oi_t *sensor, int centimeters, double sum){

 bool dir;
 int distanceToTravel = centimeters * 10;
 oi_setWheels(500, 500); // move forward; full speed

 while ((int)sum < distanceToTravel) {
     oi_update(sensor);
     if(sensor->bumpLeft) //detects bump on left
     {
        dir = false; //false means it will go around it to the right
        move_back(sensor, dir, sum, centimeters); //moves robot back and goes around the object
        break;
     }
     else if(sensor->bumpRight) //detects bump on right
     {
         dir = true; //true means it will go around it to the left
         move_back(sensor, dir, sum, centimeters);
         break;
     }
     else if(sensor->cliffLeft) //detects cliff on left
     {
         dir = false;
         move_back(sensor, dir, sum, centimeters);
         break;
     }
     else if(sensor->cliffRight) //detects cliff on right
     {
         dir = true;
         move_back(sensor, dir, sum, centimeters);
         break;
     }
     else if(sensor->cliffFrontLeft)// detects cliff front left
     {
         dir = false;
         move_back(sensor, dir, sum, centimeters);
         break;
     }
     else if(sensor->cliffFrontRight)// detects cliff on front right
     {
         dir = true;
         move_back(sensor, dir, sum, centimeters);
         break;
     }
     sum += sensor->distance;
 }
 oi_setWheels(0, 0); // stop

 }




void turn_clockwise(oi_t *sensor, int degrees){



     double sum = 0;
     oi_setWheels(25, -25); // rotate clockwise; reduced speed
    while (sum < degrees) { //rotates robot until degrees is met
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop once the degrees are met

}

void turn_cclockwise(oi_t *sensor, int degrees){ //turn robot counter clockwise


     double sum = 0;
     oi_setWheels(-25, 25); //rotate counter clockwise; reduced speed
    while (sum > degrees) {//rotate robot till degrees is met
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop

}


//moves the robot back AND around objects
void move_back(oi_t *sensor, bool direction, double curSum, int curCent){ //false is left, true is right
    int i;
    oi_update(sensor);
    oi_setWheels(-500, -500);
    for( i = 0; i <5; i++){
        oi_update(sensor);
    }
    oi_setWheels(0, 0); //stop

    if(direction == false){  //when false turn to the right
         turn_clockwise(sensor, 90);
    }

    if(direction == true){ //when true turn to the left
             turn_cclockwise(sensor, -90);
        }

    oi_setWheels(500, 500);
      for(i=0;i<8;i++){

           oi_update(sensor);
       }
      oi_setWheels(0, 0); //stop

    if(direction == false){ //rotate cclockwise to point in original direction
       turn_cclockwise(sensor, -90);
    }
    if(direction == true){ //rotate clockwise to point in original direction
        turn_clockwise(sensor, 90);
     }

    double sumToReturn = curSum - 8;

    Move_Forward(sensor, curCent, sumToReturn); //moves forward past object
}


void Move_Backward(oi_t *sensor, int centimeters, double sum){ //just moves the robot backward

 bool dir;
 int distanceToTravel = centimeters * 10;
 oi_setWheels(-500, -500); // move backward; full speed
 while (sum < distanceToTravel) { //move backward till distanceToTravel is met
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
     /*else if(sensor->cliffLeft)
          {
              dir = false;
              move_back(sensor, dir, sum, centimeters);
          }
     else if(sensor->cliffRight)
          {
              dir = true;
              move_back(sensor, dir, sum, centimeters);
          }
     else if(sensor->cliffFrontLeft)
          {
              dir = false;
              move_back(sensor, dir, sum, centimeters);
          }
     else if(sensor->cliffFrontRight)
          {
              dir = true;
              move_back(sensor, dir, sum, centimeters);
          }*/
     sum += sensor->distance;
 }
 oi_setWheels(0, 0); // stop


 }

