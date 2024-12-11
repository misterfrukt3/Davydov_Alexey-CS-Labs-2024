#include <iostream>
#include <cmath>
#include "MatrixFunctions.hpp"

namespace {
int factorial(int num) {
    int result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}
}

double** createMatrix(int N, int M) {
    double** matrix = new double*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new double[M];
    }
    return matrix;
}

void freeMatrix(double** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

void fillMatrixA(double** matrix, int N, int M, double x) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == j) {
                matrix[i][j] = 1.0;
            } else if (i < j) {
                matrix[i][j] = pow(x, i + 1) / pow(factorial(j + 1), i + 1);
        
            } else {
                matrix[i][j] = pow(-x, i + 1) / pow(factorial(j + 1), i + 1);
            }
        }
    }
}


void fillMatrixB(double B[10][10]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            B[i][j] = i * 10 + j;
        }
    }
}

double** getPointerArray(double B[10][10]) {
    double** pointerArray = new double*[10];
    for (int i = 0; i < 10; ++i) {
        pointerArray[i] = B[i];
    }
    return pointerArray;
}