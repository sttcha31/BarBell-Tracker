#include <cmath>

#include "BarbellExercise.h"
#include "Matrix.h"
#include "User.h"
#include "vector_math.h"


BarbellExercise::BarbellExercise(float weight, Unit unit, User user) : weight_(weight), user_(user) { 
  if (unit == Unit::lb){
    const double lb_to_kg { 0.45359237 };
    weight*= lb_to_kg;
  }
};

void BarbellExercise::calibrate(){
  filter.begin(1.0/dt);
  unsigned long startTime = millis();
  float x, y, z;
  float gx, gy, gz;
  float mx, my, mz;
  while(millis() - startTime < 1000){
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) {
      IMU.readAcceleration(x, y, z);
      IMU.readGyroscope(gx, gy, gz);
      IMU.readMagneticField(mx, my, mz);
      filter.update(gx, gy, gz, x, y, z, mx, my, mz); // TODO(STEVE) check what units should be passed into this function
      
      float current_pitch = filter.getPitchRadians();
      float current_roll = filter.getRollRadians();

      gravity.x = sin(current_roll);             // Component along sensor's X axis
      gravity.y = -cos(current_roll) * sin(current_pitch); // Component along sensor's Y axis
      gravity.z = -cos(current_roll) * cos(current_pitch);

      normalize(gravity);
      gravity = scalar_mult(gravity, 9.81);
    }
  }
}

void BarbellExercise::start(){
  calibrate();
  //TODO(STEVE) make sure to read gravity in m/s^2 and not gs
  float ax, ay, az; // Accelerometer data
  float gx, gy, gz; // Gyroscope data
  float mx, my, mz; // Magnetometer data
  while(true){ // wait until bluetooth sends end signal
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) {
      IMU.readAcceleration(ax, ay, az);
      IMU.readGyroscope(gx, gy, gz);
      IMU.readMagneticField(mx, my, mz);
      filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

      float current_pitch = filter.getPitchRadians();
      float current_roll = filter.getRollRadians();

      gravity.x = sin(current_roll);
      gravity.y = -cos(current_roll) * sin(current_pitch);
      gravity.z = -cos(current_roll) * cos(current_pitch);

      normalize(gravity);
      gravity = scalar_mult(gravity, 9.81);

      Vector a = get_linear_acc({ax,ay,az}, gravity);

      update(a, velocity, position, dt);
      velocity_buffer.push(-project(velocity,gravity));
    }
  }
}

void BarbellExercise::update_state(){
  if(state == State::not_started){
    if(velocity_buffer.get_average() > 0){
      state = State::starting;
    }
  }
  else if(state == State::starting && velocity_buffer.get_average() < 0){
    state = State::eccentric;
  }
  else if (state == State::eccentric && velocity_buffer.get_average() > 0){
    state = State::concentric;
  }
  else if (state == State::concentric && velocity_buffer.get_average() <0){
    state = State::eccentric;
  }
}

Matrix BarbellExercise::CreateRotationMatrix(Vector g){
  Vector w = {0,0,-1};
  // 1. normalize g
  normalize(g);
  // 2. compute axis of rotation (u) 
  Vector u = cross(g, w);
  normalize(u);
  float theta = acos(dot(g,w));
  // Apply Rodigues Rotaiton FOrmula
  Matrix I = Matrix();
  Matrix ux = Matrix({0, -u.z, u.y,
                      u.z, 0, -u.x,
                      -u.y, u.x, 0});
  return I + ux*sin(theta) + (ux*ux) * (1-cos(theta));

}
