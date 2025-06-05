#include "BarbellExercise.h"
#include <MadgwickAHRS.h>
#include "math.h"

BarbellExercise::BarbellExercise(float weight, Unit unit) : weight_(weight) { 
  if (unit == Unit::lb){
    weight*= 0.45359237;
  }
};

float BarbellExercise::get_magnitude(float x, float y, float z){
  return sqrt(x*x + y*y + z*z);
}

void BarbellExercise::insert(float x, float y, float z){
    if(abs(get_magnitude(x,y,z)-1) < 0.2){
      downDirection = {-x/get_magnitude(x,y,z), -y/get_magnitude(x,y,z), -z/get_magnitude(x,y,z)};
    }
}