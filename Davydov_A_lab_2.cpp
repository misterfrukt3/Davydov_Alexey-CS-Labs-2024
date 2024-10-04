#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kStepSizeForDivisibilityByFive = 5;

const int kNegativeALimit = 10;
const int kNoneNegativeALimit = 9;
const int kANegativeDivision = 0;

const int kNoneNegativeAStep = 2;
const int kNegativeAStep = 3;

const int kNoneNegativeAStart = 2;
const int kNegativeAStart = 3;

const double kXStep = 0.2;
const double kPrecision = 1e-6;
const int kCountWithVariables = 10;
const int kCountWithFunction = 15;

const int kPartialSumThirdTerms = 3;
const int KPartialSumFithTerms = 5;
const int kPartialSumTenthTerms = 10;
}  // namespace

void Task1() {
    int n = 0;
    int m = 0;
    std::cout << "Введите значение n: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Введено недопустимое значение n\n";
        return;
    }
    std::cout << "Введите значение m (m < n): ";
    std::cin >> m;
    if (m >= n) {
        std::cout << "Введено недопустимое значение m\n";
        return;
    }

    int sum = 0;
    for (int i = kStepSizeForDivisibilityByFive; i <= n; i += kStepSizeForDivisibilityByFive) {
        if (i % m != 0) {
            sum += i;
        }
    }
    std::cout << "Сумма чисел, которые делятся на 5 и не делятся на " << m << ": " << sum << std::endl;
}

void Task2() {
    double a = 0;
    double S = 1;
    std::cout << "Введите значение a: ";
    std::cin >> a;

    if (a >= kANegativeDivision) {
        for (int i = kNoneNegativeAStart; i < kNoneNegativeALimit; i += kNoneNegativeAStep) {
            S *= i * i - a;
        }
    } else {
        for (int i = kNegativeAStart; i < kNegativeALimit; i += kNegativeAStep) {
            S *= (i - 2);
        }
    }
    std::cout << "Результат: " << S << std::endl;
}

void Task3() {
    std::cout << std::setw(kCountWithVariables) << "x" << std::setw(kCountWithFunction) << "Y(x)" << std::setw(kCountWithFunction) << "S(x)"
              << std::setw(kCountWithVariables) << "N" << std::endl;
    double x = 0;

    while (x <= 1.0) {
        double Yx = x * x * std::atan(x);
        double sum = 0.0;
        double term = x * x * x;
        int n = 0;

        while (std::fabs(term) > kPrecision) {
            sum += term;
            ++n;
            double k = -(x * x) * (2 * n - 1) / (2 * n + 1);
            term *= k;
        }

        std::cout << std::setw(kCountWithVariables) << x << std::setw(kCountWithFunction) << Yx << std::setw(kCountWithFunction) << sum
                  << std::setw(kCountWithVariables) << n << std::endl;
        x += kXStep;
    }
}

void Task4() {
    int n = 0;
    std::cout << "Введите значение n: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Введено недопустимое значение n\n";
        return;
    }
    if (n >= 3) {
        std::cout << "Промежуточные значения:" << std::endl;
    }
    double y = std::sqrt(2 * n + 1);
    for (int i = n - 1; i >= 1; --i) {
        y = std::sqrt(2 * i + 1 + y);
        if (i == n - kPartialSumThirdTerms || i == n - KPartialSumFithTerms || i == n - kPartialSumTenthTerms) {
            std::cout << n - i << " члена: " << y << std::endl;
        }
    }
    std::cout << "y для n = " << n << ": " << y << std::endl;
}

int main(int, char**) {
    int task = 0;
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        std::cout << "Выберите задание:\n";
        std::cout << "1. Найти сумму чисел, которые делятся на 5 и не делятся на m\n";
        std::cout << "2. Вычислить произведение в зависимости от a\n";
        std::cout << "3. Вычислить значения суммы ряда и функции Y(x)\n";
        std::cout << "4. Вычислить y по формуле c вложенными квадратными корнями\n";
        std::cout << "0. Выйти\n";
        std::cout << "Ваш выбор: ";
        std::cin >> task;

        switch (task) {
            case 0:
                return 0;
            case 1:
                Task1();
                break;
            case 2:
                Task2();
                break;
            case 3:
                Task3();
                break;
            case 4:
                Task4();
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
        std::cout << "Продолжить работу? (y/n)\n";
        std::cin >> continueExecution;
    }
    return 0;
}
