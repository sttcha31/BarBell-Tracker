#include <Arduino.h>
#include "BarbellExercise.h"
#include "Arduino_BMI270_BMM150.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Serial Started");

  if(!IMU.begin()){ 
    Serial.println("Failed to Start IMU");
    while(1);
  }
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");

}

void loop() {
  // put your main code here, to run repeatedly:
  float x, y, z;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }
}
