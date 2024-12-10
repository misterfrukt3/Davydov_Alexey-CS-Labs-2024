#pragma once

namespace FindEquationRoot {
struct Equation {
    double result = 0.0;
    int iterations = 0;
    bool resultValid = true;
};

enum class Methods {
    Iteration = 1,
    Newton = 2,
    HalfDivision = 3,
};

[[nodiscard]] Equation CalculateIterationMethod(const double coefficient, const double calculationAccuracy);
[[nodiscard]] Equation CalculateNewtonsMethod(const double coefficient, const double calculationAccuracy);
[[nodiscard]] Equation CalculateHalfDivisionMethod(const double coefficient, const double calculationAccuracy, double leftEnd, double rightEnd);

void RunIterationsMethod();
void RunNewtonsMethod();
void RunHalfDivisionMethod();

void RunApplication();

void SelectMethod();
}  // namespace FindEquationRoot
