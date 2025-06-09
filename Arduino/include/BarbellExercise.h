#ifndef BARBELLEXERCISE_H
#define BARBELLEXERCISE_H
#include "Arduino_BMI270_BMM150.h"

#include "CircularBuffer.h"
#include "Set.h"
#include "vector_math.h"

enum Unit {
  kg,
  lb
};


class BarbellExercise {
    public: 
        BarbellExercise(float weight, Unit unit);
        void start();
        void update_position();
    protected:
        bool waitSart = true; // waiting for user to start exersise.
        Vector gravity = {0, 0, -1};
        Vector position = {0,0,0};
        Vector velocity = {0,0,0};
        CircularBuffer<float, 15> workBuffer;
        float weight_;
        Set set_;

};

#endif