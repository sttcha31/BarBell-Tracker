#ifndef BARBELLEXERCISE_H
#define BARBELLEXERCISE_H
#include "Arduino_BMI270_BMM150.h"
#include <MadgwickAHRS.h>
#include "CircularBuffer.h"
#include "Matrix.h"
#include "Set.h"
#include "vector_math.h"
#include "User.h"

enum Unit {
  kg,
  lb
};

enum State {
  not_started,
  starting, //lifting up the weight
  ready,   //weight is stationary, user ready to start
  eccentric,
  concentric,
};


class BarbellExercise {
    public: 
        BarbellExercise(float weight, Unit unit, User user);
        void calibrate();
        void start();
        void update_state();

        Matrix CreateRotationMatrix(const Vector g);
        void RotateVectorSpace();
    protected:
        //Vectors
        Vector gravity {0, 0, -1};
        Vector position {0,0,0};
        Vector velocity {0,0,0};

        //Orientation Tracking
        Madgwick filter;
        float q0, q1, q2, q3;

        //Sensor frequency
        static constexpr double dt {1.0 / 104}; //TODO(STEVE) Update this since we are now using the magnometer as well

        CircularBuffer<float, 15> velocity_buffer;
        State state = not_started;
        Vector top;
        Vector bottom;
        
        //rep tracking
        float vertical_displacement;
        
        float weight_;
        Set set_;
        User user_;

};

#endif