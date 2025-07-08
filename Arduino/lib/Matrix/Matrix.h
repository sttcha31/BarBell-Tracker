#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

struct Vector {
  float x;
  float y;
  float z;
};

struct MatrixStruct{
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
        Matrix(MatrixStruct in);
        MatrixStruct get();
        float operator[](Index index) const;
        float& operator[](Index index);
        Vector operator*(const Vector &v);
        Matrix operator*(float scalar);
        Matrix operator*(const Matrix &other);
        Matrix operator+(const Matrix &other);
        
    private:
        float data[3][3];
};

#endif 