#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>

namespace {
const double kPrecision = 0.000001;

const int kNegativeALimit = 10;
const int kNaturalALimit = 9;
const int kANaturalNegativeDivision = 0;

const int kNaturalAStep = 2;
const int kNegativeAStep = 3;
const double kXStep = 0.2;

const int kNaturalAStart = 2;
const int kNegativeAStart = 3;

const int kPowerTwo = 2;
const int kPowerThree = 3;

const int kBaseRemainderFive = 5;
const int kMinDivisionRemainder = 0;
const int kSpacingRestrictionVariables = 10;
const int kSpacingRestrictionFunction = 15;

const int kThirdTerm = 3;
const int KFithTerm = 5;
const int kTenthTerm = 10;
}  // namespace

void task1() {
    int n = 0;
    int m = 0;
    std::cout << "Введите значение n: ";
    std::cin >> n;
    std::cout << "Введите значение m (m < n): ";
    std::cin >> m;
    if (m >= n) {
        std::cout << "Введено недопустимое значение m\n";
    } else {
        int sumNumberOnSegment = 0;
        for (int i = 1; i <= n; ++i) {
            if (i % kBaseRemainderFive == kMinDivisionRemainder && i % m != kMinDivisionRemainder) {
                sumNumberOnSegment += i;
            }
        }
        std::cout << "Сумма чисел, которые делятся на 5 и не делятся на " << m << ": " << sumNumberOnSegment << std::endl;
    }
}

void task2() {
    int a = 0;
    double S = 1;
    std::cout << "Введите значение a: ";
    std::cin >> a;
    if (a >= kANaturalNegativeDivision) {
        for (int i = kNaturalAStart; i < kNaturalALimit; i += kNaturalAStep) {
            S *= (pow(i, kPowerTwo) - a);
        }
    } else {
        for (int i = kNegativeAStart; i < kNegativeALimit; i += kNegativeAStep) {
            S *= (i - 2);
        }
    }
    std::cout << "Результат: " << S << std::endl;
}

void task3() {
    std::cout << std::setw(kSpacingRestrictionVariables) << "x" << std::setw(kSpacingRestrictionFunction) << "Y(x)"
              << std::setw(kSpacingRestrictionFunction) << "S(x)" << std::setw(kSpacingRestrictionVariables) << "N" << std::endl;

    for (double x = 0; x <= 1; x += kXStep) {
        double Yx = x * x * atan(x);
        double sum = 0.0;
        double term = pow(x, kPowerThree);
        int n = 0;

        while (fabs(term) > kPrecision) {
            sum += term;
            n++;
            double k = -pow(x, kPowerTwo) / (2 * n + 1);
            term *= k;
        }
        std::cout << std::setw(kSpacingRestrictionVariables) << x << std::setw(kSpacingRestrictionFunction) << Yx
                  << std::setw(kSpacingRestrictionFunction) << sum << std::setw(kSpacingRestrictionVariables) << n << std::endl;
    }
}

void task4() {
    int n = 0;
    std::cout << "Введите значение n: ";
    std::cin >> n;
    if (n >= 3) {
        std::cout << "Промежуточные значения:" << std::endl;
    }
    double y = sqrt(2 * n + 1);
    for (int i = n - 1; i >= 1; --i) {
        y = sqrt(2 * i + 1 + y);
        if (i == n - kThirdTerm) {
            std::cout << "3 члена: " << y << std::endl;
        }
        if (i == n - KFithTerm) {
            std::cout << "5 членов: " << y << std::endl;
        }
        if (i == n - kTenthTerm) {
            std::cout << "10 членов: " << y << std::endl;
        }
    }
    std::cout << "y для n = " << n << ": " << y << std::endl;
}

int main() {
    char choice = ' ';
    char ContinueOrEnd = ' ';
    do {
        std::cout << "Выберите задание:\n";
        std::cout << "1. Найти сумму чисел, которые делятся на 5 и не делятся на m\n";
        std::cout << "2. Вычислить произведение в зависимости от a\n";
        std::cout << "3. Вычислить значения суммы ряда и функции Y(x)\n";
        std::cout << "4. Вычислить y по формуле с вложенными квадратными корнями\n";
        std::cout << "0. Выйти\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case '0':
                return 0;
            case '1':
                task1();
                break;
            case '2':
                task2();
                break;
            case '3':
                task3();
                break;
            case '4':
                task4();
                break;
            default:
                std::cout << "Неверный выбор!" << std::endl;
        }
        std::cout << "Продолжить работу? (y/n)\n";
        std::cin >> ContinueOrEnd;
    } while (ContinueOrEnd != 'n');
    return 0;
}
