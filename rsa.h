#pragma once

namespace RSA {
struct PrimeDividers {
    int q = 0;
    int p = 0;
};

struct Key {
    int e = 0;
    int N = 1;
};

[[nodiscard]] PrimeDividers CalculatePrimeFact(int number);
[[nodiscard]] Key CalculatePrivKey(Key publicKey);
[[nodiscard]] int DecryptMessage(Key privateKey, int message);

void RunApplication();
}
