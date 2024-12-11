#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MatrixFunctions.hpp"
#include "MPrinter.hpp"
using namespace std;
int main() {
   
    srand(time(0));
    int N = rand() % 8 + 8;
    int M = rand() % 8 + 8;
    int precision = rand() % 6 + 3;

    double x = 1.0;

    double** matrixA = createMatrix(N, M);
    fillMatrixA(matrixA, N, M, x);

    std::cout << "Matrix A (Exponential Format):" << std::endl;
    printMatrix(matrixA, N, M, precision, true);

    std::cout << "Matrix A (Normal Format):" << std::endl;
    printMatrix(matrixA, N, M, precision, false);

    freeMatrix(matrixA, N);

    double B[10][10];
    fillMatrixB(B);

    double** pointerArrayB = getPointerArray(B);
    std::cout << "Matrix B:" << std::endl;
    printMatrix(pointerArrayB, 10, 10, 0, false);

    cout<<B<<"  "<< "\n";
    char y{};
    cin>>y;

    cout<<B[1] <<" "<< *B[3] <<"  "<< endl;
    cout << &B[1][4] << "" << *(B + 4) << "" << B[0] + 6 << endl;
    cout << *(*(B + 6)) << "" << *B[2]-3 << endl;
    cout << (B[4] - 3) << "" << *(*B + 5) << endl;
    cout << &B[0][14] << "" << *(B[2] + 22) << "" << *(B[4] - 13) << endl;

    delete[] pointerArrayB;

    return 0;
}