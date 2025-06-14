#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

struct Vector {
  float x;
  float y;
  float z;
};

float dot(const Vector& a, const Vector& b);

float magnitude(const Vector& v);

void normalize(Vector &v);

Vector add(const Vector &a, const Vector& b);

Vector scalar_mult(const Vector &v, float x);

//converts IMU force readings to real acceleration readings(0 m/s at rest);
Vector get_linear_acc(const Vector& v, const Vector& g);

//projects vector a onto vector b, and returns the scalar
float project(const Vector &a, const Vector &b);

void update(const Vector &a, Vector &v, Vector &p, float dt);
#endif 