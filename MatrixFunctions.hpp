#pragma once

double** createMatrix(int N, int M);

void freeMatrix(double** matrix, int N);

void fillMatrixA(double** matrix, int N, int M, double x);

void fillMatrixB(double B[10][10]);

double** getPointerArray(double B[10][10]);
