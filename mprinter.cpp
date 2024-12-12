#include "mprinter.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

namespace {
const int kLeftLimitMatrixDimensions = 8;
const int kRightLimitMatrixDimensions = 15;

const int kLeftLimitPrecision = 3;
const int kRightLimitPrecision = 5;

const int kStaticMatricSize = 10;

const int kPartThreeValue = 20;
}  // namespace

namespace mprinter {
long Factorial(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int GenRandomNumber(int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(minVal, maxVal);

    int randomValue = distrib(gen);
    return randomValue;
}

double GenerateMatrixElementUpper(int row, int col) {
    return (1.0 / std::pow(Factorial(col), row));
}

double GenerateMatrixElementLower(int row, int col) {
    return std::pow(-1.0, row) / std::pow(Factorial(col), row);
}

double** CreateMatrix(int rows, int cols) {
    auto** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void DeleteMatrix(double** matrix, int rows) {
    if (matrix == nullptr) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];  // Удаление каждой строки
    }
    delete[] matrix;  // Удаление массива указателей
}

void FillMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i < j) {
                matrix[i][j] = GenerateMatrixElementUpper(i + 1, j + 1);
            } else if (i > j) {
                matrix[i][j] = GenerateMatrixElementLower(i + 1, j + 1);
            } else {
                matrix[i][j] = 1;
            }
        }
    }
}

void PrintMatrix(double** matrix, int rows, int cols, OutputMode outputMode, int precision, int maxLineLength) {
    int margin = 4;
    if (outputMode == OutputMode::Exponential) {
        margin += 8;
    }
    int oneElementWidth = precision + margin;
    int elenemtsInOneRow = maxLineLength / oneElementWidth;
    int tableWidth = std::min(oneElementWidth * std::min(elenemtsInOneRow, cols) + margin, maxLineLength + margin);
    int pagesCount = cols / elenemtsInOneRow;
    if (cols % elenemtsInOneRow != 0) {
        pagesCount++;
    }

    if (outputMode == OutputMode::Fixed) {
        std::cout << std::fixed;
    } else {
        std::cout << std::scientific;
    }
    std::cout << std::setprecision(precision) << std::setfill('=');
    std::cout << std::setw(tableWidth) << "=" << std::endl << std::setfill(' ');

    for (int i = 0; i < pagesCount; i++) {
        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < elenemtsInOneRow; k++) {
                if (i * elenemtsInOneRow + k < cols) {
                    std::cout << std::setw(oneElementWidth) << matrix[j][i * elenemtsInOneRow + k];
                }
            }
            std::cout << std::endl;
        }
        if (i != pagesCount - 1) {
            std::cout << std::setfill('-') << std::setw(tableWidth) << '-' << std::endl;
            std::cout << std::setfill(' ');
        }
    }

    std::cout << std::setfill('=') << std::setw(tableWidth) << "=" << std::endl << std::setfill(' ');
}

void RunApplication() {
    std::cout << std::endl << "Часть 1" << std::endl;

    int rows = GenRandomNumber(kLeftLimitMatrixDimensions, kRightLimitMatrixDimensions);
    int cols = GenRandomNumber(kLeftLimitMatrixDimensions, kRightLimitMatrixDimensions);
    int precision = GenRandomNumber(kLeftLimitPrecision, kRightLimitPrecision);
    int mode = 0;
    std::cout << "Выберите тип вывода:\n    1) Фиксированный\n    2) Экспоненциальный\n";
    std::cin >> mode;
    OutputMode outputMode = static_cast<OutputMode>(mode);

    std::cout << "Cтрок: " << rows << " Столбцов: " << cols << " Точность: " << precision << std::endl << std::endl;

    double** dynamicMatrix = CreateMatrix(rows, cols);
    FillMatrix(dynamicMatrix, rows, cols);
    PrintMatrix(dynamicMatrix, rows, cols, outputMode, precision);
    DeleteMatrix(dynamicMatrix, rows);

    std::cout << std::endl << "Часть 2" << std::endl;

    double staticMatrix[kStaticMatricSize][kStaticMatricSize];
    for (int i = 0; i < kStaticMatricSize; i++) {
        for (int j = 0; j < kStaticMatricSize; j++) {
            staticMatrix[i][j] = (i + 1) * kStaticMatricSize + (j + 1);
        }
    }
    double* serviceArray[kStaticMatricSize];
    for (int i = 0; i < kStaticMatricSize; i++) {
        serviceArray[i] = staticMatrix[i];
    }
    PrintMatrix(serviceArray, kStaticMatricSize, kStaticMatricSize, OutputMode::Fixed, 0);

    std::cout << std::endl << "Часть 3" << std::endl;

    std::cout << staticMatrix << "  " << staticMatrix[0] << "  " << staticMatrix[2] << std::endl;
    std::cout << staticMatrix[0][0] << "  " << **staticMatrix << "  " << *staticMatrix[0] << std::endl;
    std::cout << *(*(staticMatrix + 1)) << "  " << *staticMatrix[1] << std::endl;
    std::cout << *(staticMatrix[0] + 1) << "  " << *(*staticMatrix + 1) << std::endl;
    std::cout << staticMatrix[0][20] << "  " << *(staticMatrix[0] + 20) << "  " << *staticMatrix[2] << std::endl;
}
}  // namespace mprinter
