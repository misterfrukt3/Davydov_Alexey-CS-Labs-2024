#include "rsa.h"

#include <cmath>
#include <iostream>

namespace RSA {
[[nodiscard]] PrimeDividers CalculatePrimeFact(int num) {
    for (int i = 2; (i * i < num); ++i) {
        if (num % i == 0) {
            return {i, num / i};
        }
    }

    std::cout << "Не удалось разложить на простые множители\n";
    return {};
}

[[nodiscard]] Key CalculatePrivKey(Key publicKey) {
    PrimeDividers Dividers = CalculatePrimeFact(publicKey.N);

    int EulerFunction = (Dividers.q - 1) * (Dividers.p - 1);
    int i = 2;

    while (publicKey.e * i % EulerFunction != 1) {
        ++i;
    }

    return {i, publicKey.N};
}

[[nodiscard]] int DecryptMessage(Key privKey, int message) {
    int result = 1;
    message = message % privKey.N;

    for (int i = 0; i < privKey.e; ++i) {
        result *= message;
        result %= privKey.N;
    }

    return result;
}
}  // namespace RSA
