#include "vector_math.h"
#include <cmath>


float dot(const Vector& a, const Vector& b){
    return a.x * b.x + a.y *b.y + a.z * b.z;
}

float magnitude(const Vector& v){
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

void normalize(Vector &v){
    float mag = magnitude(v);
    v.x /= mag;
    v.y /= mag;
    v.z /= mag;
}

Vector add(const Vector &a, const Vector& b){
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector scalar_mult(const Vector &v, float x){
    return {v.x * x, v.y * x, v.z * x};
}
//converts IMU force readings to real acceleration readings(0 m/s at rest);
Vector get_linear_acc(const Vector& v, const Vector& g){
    return add(v,g); 
}

float project(const Vector &a, const Vector &b){
    return dot(a,b) / magnitude(b);
}

void update(const Vector &a, Vector &v, Vector &p, float dt){
    v = add(v, scalar_mult(a, dt));
    p = add(p, scalar_mult(v, dt));
}