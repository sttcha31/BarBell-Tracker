#include "BarbellExercise.h"
#include <MadgwickAHRS.h>
#include "vector_math.h"
BarbellExercise::BarbellExercise(float weight, Unit unit) : weight_(weight) { 
  if (unit == Unit::lb){
    weight*= 0.45359237;
  }
};

void BarbellExercise::start(){

  float x, y, z;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    gravity = {-x/get_magnitude({x,y,z}), -y/get_magnitude({x,y,z}), -z/get_magnitude({x,y,z})};
  }
  while(true){

  }
}
