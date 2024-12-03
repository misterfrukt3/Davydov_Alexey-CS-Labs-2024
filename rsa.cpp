#include "rsa.h"

#include <cmath>
#include <iostream>

namespace RSA {
[[nodiscard]] PrimeDividers CalculatePrimeFact(int num) {
    for (int i = 2; (i * i < num); ++i) {
        if (num % i == 0) {
            std::cout << i << " " << num / i << std::endl;
            return {i, num / i};
        }
    }
    PrimeDividers result = {0, 0};
    std::cout << "Не удалось разложить на простые множители\n";
    return result;
}

[[nodiscard]] Key CalculatePrivKey(Key publicKey) {
    PrimeDividers Dividers = CalculatePrimeFact(publicKey.N);
    if (Dividers.q == 0 && Dividers.p == 0) {
        Key result = {0, 0};
        return result;
    }
    int EulerFunction = (Dividers.q - 1) * (Dividers.p - 1);
    int i = 2;

    while (publicKey.e * i % EulerFunction != 1) {
        ++i;
    }
    Key result = {i, publicKey.N};
    return result;
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

void RunApplication() {
    RSA::Key publicKey;

    std::cout << "Введите открытый ключ через пробел(пару чисел (e, N))" << std::endl;
    std::cin >> publicKey.e >> publicKey.N;

    int mess = 0;
    std::cout << "Введите зашифрованное сообщение:" << std::endl;
    std::cin >> mess;

    RSA::Key privKey = RSA::CalculatePrivKey(publicKey);
    if (privKey.e == 0 && privKey.N == 0) {
    } else {
        std::cout << "Расшифрованное сообщение:" << std::endl;
        std::cout << RSA::DecryptMessage(privKey, mess) << std::endl;
    }
}
}  // namespace RSA
