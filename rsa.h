#pragma once

namespace RSA {
struct PrimeDividers {
    int first = 0;
    int second = 0;
};

struct Key {
    int exponent = 0;
    int module = 1;
};

[[nodiscard]] PrimeDividers CalculatePrimeFactorization(int number);
[[nodiscard]] Key CalculatePrivateKey(Key publicKey);
[[nodiscard]] int DecryptMessage(Key privateKey, int message);
}
