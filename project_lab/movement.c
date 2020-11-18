#include "movement.h"
#include "scan.h"

void Move_Forward(oi_t *sensor, int centimeters, double sum){

 bool dir;
 int distanceToTravel = centimeters * 10;
int i,j,k = 0;




if(deliveredPackage == false){
        scan_read(180);
        timer_waitMillis(100);
        for(i = 0; i < objCount; i++)
        {
            if(scanObjs[i].angle >= 50 && scanObjs[i].angle <= 90 && scanObjs[i].curpdistance < centimeters + 5)
            {
                turn_clockwise(sensor, 90);
                oi_setWheels(500, 500);
                for(j=0;j<10;j++)
                {
                    oi_update(sensor);
                }
                oi_setWheels(0, 0);
                turn_cclockwise(sensor, -90);
                break;
            }
            else if(scanObjs[i].angle <= 130 && scanObjs[i].angle > 90 && scanObjs[i].curpdistance < centimeters + 5)
            {
                turn_cclockwise(sensor, -90);
                oi_setWheels(500, 500);
                for(k=0;k<10;k++)
                {
                      oi_update(sensor);
                }
                oi_setWheels(0, 0);
                turn_clockwise(sensor, 90);
                break;
            }
            scanObjs[i].width = 0;
            scanObjs[i].curpdistance = 0;
            scanObjs[i].angle = 0;

        }

}
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
     else if(sensor->cliffLeftSignal > 2700) //detects wall on left
     {
         dir = false;
         move_back_wall(sensor);
         break;
     }
     else if(sensor->cliffRightSignal > 2700) //detects wall right
     {
         dir = true;
         move_back_wall(sensor);
         break;
     }
     else if(sensor->cliffFrontLeftSignal > 2700)// detects wall on front left
     {
         dir = false;
         move_back_wall(sensor);
         break;
     }
     else if(sensor->cliffFrontRightSignal > 2700)// detects wall on front right
     {
         dir = true;
         move_back_wall(sensor);
         break;
     }
     else if(sensor->cliffLeftSignal < 1000) //detects cliff on left
          {
              dir = false;
              move_back(sensor, dir, sum, centimeters);
              break;
          }
          else if(sensor->cliffRightSignal < 1000) //detects cliff on right
          {
              dir = true;
              move_back(sensor, dir, sum, centimeters);
              break;
          }
          else if(sensor->cliffFrontLeftSignal < 1000)// detects cliff front left
          {
              dir = false;
              move_back(sensor, dir, sum, centimeters);
              break;
          }
          else if(sensor->cliffFrontRightSignal < 1000)// detects cliff on front right
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
     oi_setWheels(50, -50); // rotate clockwise; reduced speed
    while (sum < degrees) { //rotates robot until degrees is met
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop once the degrees are met
     timer_waitMillis(50);

}

void turn_cclockwise(oi_t *sensor, int degrees){ //turn robot counter clockwise


     double sum = 0;
     oi_setWheels(-50, 50); //rotate counter clockwise; reduced speed
    while (sum > degrees) {//rotate robot till degrees is met
     oi_update(sensor);
     sum += sensor->angle;
     }
     oi_setWheels(0, 0); // stop
     timer_waitMillis(50);

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

    double sumToReturn = curSum - 50;

    Move_Forward(sensor, curCent, sumToReturn); //moves forward past object
}

void move_back_wall(oi_t *sensor){ //moves robot away from wall
    int i;
    oi_update(sensor);
    oi_setWheels(-500, -500); //moves robot backward
        for( i = 0; i <4; i++){
            oi_update(sensor);
        }
        oi_setWheels(0, 0); //stop
        turn_clockwise(sensor, 180);
        oi_setWheels(500, 500); //move forward
              for(i=0;i<4;i++){
                   oi_update(sensor);
               }
              oi_setWheels(0, 0); //stop
}

void Move_Backward(oi_t *sensor, int centimeters, double sum){ //just moves the robot backward

 bool dir;
 int distanceToTravel = centimeters * 10;
 oi_setWheels(-500, -500); // move backward; full speed
 while (sum < distanceToTravel) { //move backward till distanceToTravel is met
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
              else if(sensor->cliffLeftSignal > 2700) //detects wall on left
              {
                  dir = false;
                  move_back_wall(sensor);
                  break;
              }
              else if(sensor->cliffRightSignal > 2700) //detects wall right
              {
                  dir = true;
                  move_back_wall(sensor);
                  break;
              }
              else if(sensor->cliffFrontLeftSignal > 2700)// detects wall on front left
              {
                  dir = false;
                  move_back_wall(sensor);
                  break;
              }
              else if(sensor->cliffFrontRightSignal > 2700)// detects wall on front right
              {
                  dir = true;
                  move_back_wall(sensor);
                  break;
              }
              else if(sensor->cliffLeftSignal < 1000) //detects cliff on left
                   {
                       dir = false;
                       move_back(sensor, dir, sum, centimeters);
                       break;
                   }
                   else if(sensor->cliffRightSignal < 1000) //detects cliff on right
                   {
                       dir = true;
                       move_back(sensor, dir, sum, centimeters);
                       break;
                   }
                   else if(sensor->cliffFrontLeftSignal < 1000)// detects cliff front left
                   {
                       dir = false;
                       move_back(sensor, dir, sum, centimeters);
                       break;
                   }
                   else if(sensor->cliffFrontRightSignal < 1000)// detects cliff on front right
                   {
                       dir = true;
                       move_back(sensor, dir, sum, centimeters);
                       break;
                   }
              sum += sensor->distance;
 }
 oi_setWheels(0, 0); // stop


 }

