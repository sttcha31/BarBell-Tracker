#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include "vector_math.h"


struct Instantiator{
    float a11, a12, a13, 
          a21, a22, a23, 
          a31, a32, a33;
};

struct Index {
    size_t r, c;
};

class Matrix {
    public:
        Matrix(); // Identity Matrix
        Matrix(Instantiator in);
        float operator[](Index index);
        Vector operator*(Vector &v);
        Matrix operator*(float scalar);
        Matrix operator*(Matrix &other);
        Matrix operator+(Matrix &other);
        
    private:
        float data[3][3];
};

#endif 