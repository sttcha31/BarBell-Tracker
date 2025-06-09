#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

struct Vector {
  float x;
  float y;
  float z;
};

float dot(const Vector& a, const Vector& b){
    return a.x * b.x + a.y *b.y + a.z * b.z;
}

float get_magnitude(const Vector& v){
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

//converts IMU force readings to real acceleration readings(0 m/s at rest);
Vector get_linear_acc(const Vector& v, const Vector& g){

}

void update(const Vector &a, Vector &v, Vector &p, float dt){
    
}
#endif 