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

void ProvideCorrectNumberRange(double& a, double& b) {
    if (a > b) {
        std::swap(a, b);
    }
}
}  // namespace

namespace Integration {

double fSimple(double x) {
    return x;
}

double fSinus(double x) {
    return std::sin(kMultSinusParameter * x);
}

double fPow(double x) {
    return std::pow(x, kPowParameter);
}

double fAtan(double x) {
    return std::atan(x);
}

double ExactIntegralSimple(double a, double b) {
    return (b * b - a * a) / kDivisionByTwo;
}

double ExactIntegralSinus(double a, double b) {
    return (std::cos(a * kMultSinusParameter) - std::cos(b * kMultSinusParameter)) / kMultSinusParameter;
}

double ExactIntegralPow(double a, double b) {
    return (std::pow(b, 5) - std::pow(a, 5)) / kDivisionByFive;
}

double ExactIntegralAtan(double a, double b) {
    return b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / kDivisionByTwo;
}

double IntRect(FUN f, double a, double b, double eps, int* n) {
    int N = 1;
    double prevues = 0.0;
    double current;
    double dx;

    do {
        *n = N;
        dx = (b - a) / N;
        current = 0.0;

        for (int i = 0; i < N; ++i) {
            double middle = a + (i + 0.5) * dx;
            current += f(middle);
        }
        current *= dx;

        if (fabs(current - prevues) < eps)
            break;

        prevues = current;
        N *= 2;
    } while (N < 100000);

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

        if (std::fabs(current - prevues) < eps)
            break;

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
        std::cout << "| " << std::setw(10) << results[i].functionName << "| " << std::setw(15) << results[i].exactIntegral << " | " << std::setw(15)
                  << results[i].computedIntegral << " | " << std::setw(7) << results[i].n << " |\n";
    }
    std::cout << "+-----------+-----------------+-----------------+---------+\n";
}

void RunApp() {
    srand(static_cast<unsigned int>(time(0)));

    double eps[] = {0.01, 0.001, 0.0001, 0.00001, 0.000001};
    FUN functions[] = {fSimple, fSinus, fPow, fAtan};
    const char* funcNames[] = {"y=x", "y=sin(22x)", "y=x^4", "y=arctg(x)"};

    double a = static_cast<double>(rand()) / RAND_MAX;
    double b = 2.0 + static_cast<double>(rand()) / RAND_MAX;

    ProvideCorrectNumberRange(a, b);

    std::cout << "значение a: " << a << "\n";
    std::cout << "значение b: " << b << "\n";

    for (double e : eps) {
        DataForPrint resultsRect[4]{};
        DataForPrint resultsTrap[4]{};

        double (*functionArray[4])(double, double) = {ExactIntegralSimple, ExactIntegralSinus, ExactIntegralPow, ExactIntegralAtan};

        for (int i = 0; i < 4; ++i) {
            double exact = 0;
            exact = functionArray[i](a, b);

            int nRect;
            double intSumRect = IntRect(functions[i], a, b, e, &nRect);
            snprintf(resultsRect[i].functionName, kMaxFunctionNameLength, "%s", funcNames[i]);
            resultsRect[i].exactIntegral = exact;
            resultsRect[i].computedIntegral = intSumRect;
            resultsRect[i].n = nRect;

            int nTrap;
            double intSumTrap = IntTrap(functions[i], a, b, e, &nTrap);
            snprintf(resultsTrap[i].functionName, kMaxFunctionNameLength, "%s", funcNames[i]);
            resultsTrap[i].exactIntegral = exact;
            resultsTrap[i].computedIntegral = intSumTrap;
            resultsTrap[i].n = nTrap;
        }
        std::cout << std::endl;
        std::cout << "метод прямоугольников eps = " << e << ".\n\n";
        PrintTabl(resultsRect, 4);

        std::cout << std::endl;
        std::cout << "метод трапеций eps = " << e << ".\n\n";
        PrintTabl(resultsTrap, 4);
    }
}
}  // namespace Integration
