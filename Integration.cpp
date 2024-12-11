#include "Integration.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace {
const double kDivisionByTwo = 2.0;
const double kDivisionByFive = 5.0;

const double kPowParameter = 4.0;
const double kMultSinusParameter = 22.0;

const size_t kMaxFunctionNameLength = 32;

const double kMiddle = 0.5;
const int kMaxElementaryRectanglesCount = 100000;

const int kWidthFucnName = 10;
const int kWidthIntegral = 15;
const int kWidthN = 7;

const double kEpsilon[] = {0.01, 0.001, 0.0001, 0.00001, 0.000001};

const double kBLeftBoundary = 2.0;

void ProvideCorrectNumberRange(double& a, double& b) {
    if (a > b) {
        std::swap(a, b);
    }
}
}  // namespace

namespace Integration {

double FSimple(double x) {
    return x;
}

double FSinus(double x) {
    return std::sin(kMultSinusParameter * x);
}

double FPow(double x) {
    return std::pow(x, kPowParameter);
}

double FAtan(double x) {
    return std::atan(x);
}

double ExactIntegralSimple(double a, double b) {
    return (b * b - a * a) / kDivisionByTwo;
}

double ExactIntegralSinus(double a, double b) {
    return (std::cos(a * kMultSinusParameter) - std::cos(b * kMultSinusParameter)) / kMultSinusParameter;
}

double ExactIntegralPow(double a, double b) {
    return (std::pow(b, kDivisionByFive) - std::pow(a, kDivisionByFive)) / kDivisionByFive;
}

double ExactIntegralAtan(double a, double b) {
    return b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / kDivisionByTwo;
}

double IntRect(FUN f, double a, double b, double eps, int* n) {
    int elementaryRectanglesCount = 1;
    double prevues = 0.0;
    double current = 0.0;
    double dX = 0.0;

    while (elementaryRectanglesCount < kMaxElementaryRectanglesCount) {
        *n = elementaryRectanglesCount;
        dX = (b - a) / elementaryRectanglesCount;
        current = 0.0;

        for (int i = 0; i < elementaryRectanglesCount; ++i) {
            double middle = a + (i + kMiddle) * dX;
            current += f(middle);
        }
        current *= dX;

        if (std::fabs(current - prevues) < eps) {
            break;
        }
        prevues = current;
        elementaryRectanglesCount *= 2;
    }

    return current;
}

double IntTrap(FUN f, double a, double b, double eps, int* n) {
    int N = 1;
    double prevues = 0.0;
    double current = 0.0;
    double dx = 0.0;

    while (true) {
        *n = N;
        dx = (b - a) / N;
        current = (f(a) + f(b)) / kDivisionByTwo;

        for (int i = 1; i < N; ++i) {
            double x = a + i * dx;
            current += f(x);
        }
        current *= dx;

        if (std::fabs(current - prevues) < eps) {
            break;
        }
        prevues = current;
        N *= 2;
    }

    *n = N;
    return current;
}

void PrintTabl(DataForPrint results[], int k) {
    std::cout << "+-----------+-----------------+-----------------+---------+\n";
    std::cout << "|  Function |     Integral    |      IntSum     |    N    |\n";
    std::cout << "+-----------+-----------------+-----------------+---------+\n";
    for (int i = 0; i < k; ++i) {
        std::cout << "| " << std::setw(kWidthFucnName) << results[i].functionName << "| " << std::setw(kWidthIntegral) << results[i].exactIntegral
                  << " | " << std::setw(kWidthIntegral) << results[i].computedIntegral << " | " << std::setw(kWidthN) << results[i].n << " |\n";
        std::cout << "+-----------+-----------------+-----------------+---------+\n";
    }

}

void RunApplication() {
    srand(static_cast<unsigned int>(time(nullptr)));

    FUN functions[] = {FSimple, FSinus, FPow, FAtan};
    const char* funcNames[] = {"y=x", "y=sin(22x)", "y=x^4", "y=arctg(x)"};

    double a = static_cast<double>(rand()) / RAND_MAX;
    double b = kBLeftBoundary + static_cast<double>(rand()) / RAND_MAX;

    ProvideCorrectNumberRange(a, b);

    std::cout << "значение a: " << a << "\n";
    std::cout << "значение b: " << b << "\n";

    for (double e : kEpsilon) {
        DataForPrint resultsRect[4]{};
        DataForPrint resultsTrap[4]{};

        double (*functionArray[4])(double, double) = {ExactIntegralSimple, ExactIntegralSinus, ExactIntegralPow, ExactIntegralAtan};

        for (int i = 0; i < 4; ++i) {
            double exact = 0;
            exact = functionArray[i](a, b);

            int nRect = 0;
            double intSumRect = IntRect(functions[i], a, b, e, &nRect);
            std::snprintf(resultsRect[i].functionName, kMaxFunctionNameLength, "%s", funcNames[i]);
            resultsRect[i].exactIntegral = exact;
            resultsRect[i].computedIntegral = intSumRect;
            resultsRect[i].n = nRect;

            int nTrap = 0;
            double intSumTrap = IntTrap(functions[i], a, b, e, &nTrap);
            std::snprintf(resultsTrap[i].functionName, kMaxFunctionNameLength, "%s", funcNames[i]);
            resultsTrap[i].exactIntegral = exact;
            resultsTrap[i].computedIntegral = intSumTrap;
            resultsTrap[i].n = nTrap;
        }
        std::cout << std::endl;
        std::cout << "метод прямоугольников. eps = " << e << ".\n\n";
        PrintTabl(resultsRect, 4);

        std::cout << std::endl;
        std::cout << "метод трапеций. eps = " << e << ".\n\n";
        PrintTabl(resultsTrap, 4);
    }
}
}  // namespace Integration
