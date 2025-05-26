#ifndef BARBELLEXERCISE_H
#define BARBELLEXERCISE_H
#include "Arduino_BMI270_BMM150.h"

struct Direction { // Always Normalize to be 1
  float x;
  float y;
  float z;
};

struct Vector {
  Direction direction;
  float maginture;
};


class BarbellExercise {
    public: 
        BarbellExercise();
        void start();
        float get_magnitude(float, float, float);
        void insert(float x, float y, float z);
    protected:
        bool WaitSart = true; // waiting for user to start exersise.
        Vector DownDirection = {0, 0, -1};
};

#endif