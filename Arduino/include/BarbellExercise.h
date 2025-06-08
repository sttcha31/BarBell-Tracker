#ifndef BARBELLEXERCISE_H
#define BARBELLEXERCISE_H
#include "Arduino_BMI270_BMM150.h"

#include "CircularBuffer.h"
#include "Set.h"

enum Unit {
  kg,
  lb
};


class BarbellExercise {
    public: 
        BarbellExercise(float weight, Unit unit);
        void start();
        float get_magnitude(float, float, float);
        void update_position();
        void insert(float x, float y, float z);
    protected:
        bool waitSart = true; // waiting for user to start exersise.
        Vector downDirection = {0, 0, -1};
        Vector position = {0,0,0};
        Vector velocity = {0,0,0};
        float weight_;
        Set set_;

};

#endif