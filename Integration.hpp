#pragma once
#include <cstddef>

namespace Integration {

enum class MethodType {
    Rectangles = 1,
    Trapezoids = 2,
};

typedef double (*FUN)(double);

double fSimple(double x);
double fSinus(double x);
double fPow(double x);
double fAtan(double x);

double ExactIntegralSimple(double a, double b);
double ExactIntegralSinus(double a, double b);
double ExactIntegralPow(double a, double b);
double ExactIntegralAtan(double a, double b);

double IntRect(FUN f, double a, double b, double eps, int* n);
double IntTrap(FUN f, double a, double b, double eps, int* n);

struct DataForPrint {
    char functionName[32];
    double exactIntegral;
    double computedIntegral;
    int n;
};

void PrintTabl(DataForPrint i_prn[], int k);

void RunApp();

}
