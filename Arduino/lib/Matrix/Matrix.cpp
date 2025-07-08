#include "Matrix.h"

Matrix::Matrix() {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i == j){
                data[i][j] = 1;
            } else {
                data[i][j] = 0;
            } 
        }
    }
}

Matrix::Matrix(MatrixStruct in){
    data[0][0] = in.a11;
    data[0][1] = in.a12;
    data[0][2] = in.a13;

    data[1][0] = in.a21;
    data[1][1] = in.a22;
    data[1][2] = in.a23;

    data[2][0] = in.a31;
    data[2][1] = in.a32;
    data[2][2] = in.a33;
}

MatrixStruct Matrix::get(){
    return {data[0][0], data[0][1], data[0][2],
            data[1][0], data[1][1], data[1][2],
            data[2][0], data[2][1], data[2][2]};
}
float Matrix::operator[](Index index) const{
    return data[index.r][index.c];
}

float& Matrix::operator[](Index index){
    return data[index.r][index.c];
}

Vector Matrix::operator*(const Vector &v){
    return { v.x * data[0][0] + v.y * data[0][1] + v.z * data[0][2],
             v.x * data[1][0] + v.y * data[1][1] + v.z * data[1][2],
             v.x * data[2][0] + v.y * data[2][1] + v.z * data[2][2]};
}

Matrix Matrix::operator*(float scalar) {
    return Matrix({
        scalar * data[0][0], scalar * data[0][1], scalar * data[0][2],
        scalar * data[1][0], scalar * data[1][1], scalar * data[1][2],
        scalar * data[2][0], scalar * data[2][1], scalar * data[2][2]
    });
}

Matrix Matrix::operator*(const Matrix &other) {
    float a11 = data[0][0] * other[{0,0}] + data[0][1] * other[{1,0}] + data[0][2] * other[{2,0}];
    float a12 = data[0][0] * other[{0,1}] + data[0][1] * other[{1,1}] + data[0][2] * other[{2,1}];
    float a13 = data[0][0] * other[{0,2}] + data[0][1] * other[{1,2}] + data[0][2] * other[{2,2}];

    float a21 = data[1][0] * other[{0,0}] + data[1][1] * other[{1,0}] + data[1][2] * other[{2,0}];
    float a22 = data[1][0] * other[{0,1}] + data[1][1] * other[{1,1}] + data[1][2] * other[{2,1}];
    float a23 = data[1][0] * other[{0,2}] + data[1][1] * other[{1,2}] + data[1][2] * other[{2,2}];

    float a31 = data[2][0] * other[{0,0}] + data[2][1] * other[{1,0}] + data[2][2] * other[{2,0}];
    float a32 = data[2][0] * other[{0,1}] + data[2][1] * other[{1,1}] + data[2][2] * other[{2,1}];
    float a33 = data[2][0] * other[{0,2}] + data[2][1] * other[{1,2}] + data[2][2] * other[{2,2}];

    return Matrix({a11, a12, a13, a21, a22, a23, a31, a32, a33});
}

Matrix Matrix::operator+(const Matrix &other){
    return Matrix({data[0][0] + other[{0,0}], data[0][1] + other[{0,1}], data[0][2] + other[{0,2}],
                   data[1][0] + other[{1,0}], data[1][1] + other[{1,1}], data[1][2] + other[{1,2}],
                   data[2][0] + other[{2,0}], data[2][1] + other[{2,1}], data[2][2] + other[{2,2}]});
}