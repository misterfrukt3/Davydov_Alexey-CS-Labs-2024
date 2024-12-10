#include "FindEquationRoot.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int maxIterations = 100'000'000;
const double divisorMeanArithmetic = 2.0;

struct ParametrsEquation {
    double coefficient = 0.0;
    double calculationAccuracy = 0.0;
    int precision = 0;
};

[[nodiscard]] double CalculateFunction(double x, double coefficient) {
    return x - coefficient * std::cos(x);
}

[[nodiscard]] double CalculateFunctionDerivative(double x, double coefficient) {
    return 1 + coefficient * std::sin(x);
}

[[nodiscard]] ParametrsEquation ReadEquationParametersFromInput() {
    double coefficient = 0.0;
    double calculationAccuracy = 0.0;

    std::cout << "Введите коэфицент n при n*cos(x)\n";
    std::cin >> coefficient;
    std::cout << "Введите значение погрешности в формате 1e-a\n";
    std::cin >> calculationAccuracy;

    int precision = static_cast<int>(std::ceil(-std::log10(calculationAccuracy)));

    return {coefficient, calculationAccuracy, precision};
}
void outputResultEquation(FindEquationRoot::Equation function, int precision) {
    if (function.resultValid) {
        std::cout << "Результат: " << std::fixed << std::setprecision(precision) << function.result << "\n"
                  << "Количество итераций: " << function.iterations << std::endl;
    } else {
        std::cout << "Корень не найден\n";
    }
}
}  // namespace

namespace FindEquationRoot {
[[nodiscard]] Equation CalculateIterationsMethod(const double coefficient, const double calculationAccuracy) {
    double x = 0.0;
    double fX = CalculateFunction(x, coefficient);
    int iterations = 0;

    while (std::abs(fX) > calculationAccuracy && iterations <= maxIterations) {
        x -= fX;
        fX = CalculateFunction(x, coefficient);
        ++iterations;
    }

    if (std::abs(fX) > calculationAccuracy) {
        return {x, iterations, false};
    }

    return {x, iterations};
}

[[nodiscard]] Equation CalculateNewtonsMethod(const double coefficient, const double calculationAccuracy) {
    double x = 0.0;
    double fX = CalculateFunction(x, coefficient) / CalculateFunctionDerivative(x, coefficient);
    int iterations = 0;

    while (std::abs(fX) > calculationAccuracy && iterations <= maxIterations) {
        x -= (fX);
        fX = CalculateFunction(x, coefficient) / CalculateFunctionDerivative(x, coefficient);
        ++iterations;
    }

    return {x, iterations};
}

[[nodiscard]] Equation CalculateHalfDivisionMethod(const double coefficient, const double calculationAccuracy, double leftBoundary,
                                                   double rightBoundary) {
    double middleX = (leftBoundary + rightBoundary) / divisorMeanArithmetic;
    int iterations = 0;

    while (std::abs(rightBoundary - leftBoundary) > calculationAccuracy) {
        double fXLeftBoundary = CalculateFunction(leftBoundary, coefficient);
        double fXRightBoundary = CalculateFunction(rightBoundary, coefficient);
        double fX = CalculateFunction(middleX, coefficient);

        if ((fXLeftBoundary > 0) != (fX > 0)) {
            rightBoundary = middleX;
        } else if ((fXRightBoundary > 0) != (fX > 0)) {
            leftBoundary = middleX;
        } else {
            return {middleX, iterations, false};
        }

        middleX = (leftBoundary + rightBoundary) / divisorMeanArithmetic;
        ++iterations;
    }

    return {middleX, iterations};
}

void RunIterationsMethod() {
    ParametrsEquation data = ReadEquationParametersFromInput();

    outputResultEquation(CalculateIterationsMethod(data.coefficient, data.calculationAccuracy), data.precision);
}

void RunNewtonsMethod() {
    ParametrsEquation data = ReadEquationParametersFromInput();

    outputResultEquation(CalculateNewtonsMethod(data.coefficient, data.calculationAccuracy), data.precision);
}

void RunHalfDivisionMethod() {
    ParametrsEquation data = ReadEquationParametersFromInput();

    double leftBoundary = 0.0;
    double rightBoundary = 0.0;

    std::cout << "Введите границы отрезка через пробел, на котором будут искаться корни\n";
    std::cin >> leftBoundary >> rightBoundary;

    if (leftBoundary >= rightBoundary) {
        std::cout << "Введены недопустимые значения, левая граница должна быть не больше правой\n";
        return;
    }
    double fXLeftBoundary = CalculateFunction(leftBoundary, data.coefficient);
    double fXRightBoundary = CalculateFunction(rightBoundary, data.coefficient);
    if ((fXLeftBoundary > 0) == (fXRightBoundary > 0)) {
        std::cout << "На данном отрезке нету корня уравнения, на границах функция принимает значения одинаковых знаков\n";
        return;
    }
    outputResultEquation(CalculateHalfDivisionMethod(data.coefficient, data.calculationAccuracy, leftBoundary, rightBoundary), data.precision);
}
void SelectMethod() {
    int taskNumber = 0;

    std::cout << "Выберите номер, интересующего вас метода, и введите его в консоль для перехода\n";
    std::cout << "[1] Метод итераций\n";
    std::cout << "[2] Метод Ньютона\n";
    std::cout << "[3] Метод половинного деления\n";

    std::cin >> taskNumber;
    switch (static_cast<Methods>(taskNumber)) {
        case Methods::Iteration:
            RunIterationsMethod();
            break;
        case Methods::Newton:
            RunNewtonsMethod();
            break;
        case Methods::HalfDivision:
            RunHalfDivisionMethod();
            break;
        default:
            std::cout << "Такого номера задания нет(Введите значение от 1 до 3)\n";
            break;
    }
}

void RunApplication() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        SelectMethod();

        std::cout << "Продолжить работу? (y/n)\n";
        std::cin >> continueExecution;
    }
}

}  // namespace FindEquationRoot
