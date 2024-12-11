#include <iostream>
#include <iomanip>
#include "MPrinter.hpp"

namespace {
const int maxLineLength =120;
}

void printMatrix(double** matrix, int rows, int columns, int precision, bool exponentialFormat) {
    const int columnWidth = precision + 9;
    const int elementsInOneRow = maxLineLength / columnWidth;
    const int pagesCount = (columns + elementsInOneRow - 1) / elementsInOneRow;

    std::cout << std::setprecision(precision) << std::fixed << std::setfill('=');
    std::cout << std::setw(maxLineLength) << "=" << std::endl << std::setfill(' ');

    for (int page = 0; page < pagesCount; ++page) {
        for (int row = 0; row < rows; ++row) {
            
            for (int col = 0; col < elementsInOneRow; ++col) {
                int index = page * elementsInOneRow + col;
                if (index < columns) {
                    if (exponentialFormat) {
                        std::cout << std::setw(columnWidth) << std::scientific << matrix[row][index];
                    } else {
                        std::cout << std::setw(columnWidth) << std::fixed << matrix[row][index];
                    }
                }
            }
            std::cout << std::endl;
        }

        if (page != pagesCount - 1) {
            std::cout << std::setfill('-') << std::setw(maxLineLength) << '-' << std::endl;
            std::cout << std::setfill(' ');
        }
    }
    
    std::cout << std::setfill('=') << std::setw(maxLineLength) << "=" << std::endl << std::setfill(' ');
}

