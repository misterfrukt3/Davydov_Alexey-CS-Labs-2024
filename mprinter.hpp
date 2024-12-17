#include <iomanip>

namespace mprinter {
const int kDefaultMaxLineLength = 80;
const int kDefaultPrecision = 3;
const int kStaticMatricSize = 10;

enum class OutputMode {
    Fixed = 1,
    Exponential = 2
};
double GenerateMatrixElementLower(int row, int col);
double GenerateMatrixElementUpper(int row, int col);

double** CreateMatrix(int row, int col);
void DeleteMatrix(double** matrix, int rows);

void PrintMatrix(double** matrix, int rows, int cols, OutputMode outputMode, int precision = kDefaultPrecision,
                 int maxLineLength = kDefaultMaxLineLength);

void FillMatrixA(int** matrix, int rows, int cols);
void FillMatrixB(double B[kStaticMatricSize][kStaticMatricSize]);

double** GetPointerArray(double B[kStaticMatricSize][kStaticMatricSize]);

void RunApplication();
}  // namespace mprinter
