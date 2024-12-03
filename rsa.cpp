#include <iostream>
#include <cmath>


#include "rsa.h"

namespace {
const int kMaxPrimeNumber = 592967;
}  // namespace

namespace RSA {
[[nodiscard]] PrimeDividers CalculatePrimeFactorization(int number) {
    for (int i = 2; (i * i < number) && (i < kMaxPrimeNumber); ++i) {
        if (number % i == 0) {
            return {i, number / i};
        }
    }

    std::cout << "Не удалось разложить на простые множители :(\n";
    return {};
}

[[nodiscard]] Key CalculatePrivateKey(Key publicKey) {
    PrimeDividers primeDividers = CalculatePrimeFactorization(publicKey.module);

    int EulerFunction = (primeDividers.first - 1) * (primeDividers.second - 1);
    int i = 2;

    while (publicKey.exponent * i % EulerFunction != 1) {
        ++i;
    }

    return {i, publicKey.module};
}

[[nodiscard]] int DecryptMessage(Key privateKey, int message) {
    int result = 1;
    message = message % privateKey.module;

    for (int i = 0; i < privateKey.exponent ; ++ i) {
        result *= message;
        result %= privateKey.module;
    }

    return result;
}
}  // namespace RSA
