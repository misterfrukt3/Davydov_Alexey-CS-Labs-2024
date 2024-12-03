#include <iostream>

#include "rsa.h"

int main(int, char**) {
    RSA::Key publicKey;

    std::cout << "Введите открытый ключ через пробел(пару чисел (e, N))" << std::endl;
    std::cin >> publicKey.e >> publicKey.N;

    int mess = 0;
    std::cout << "Введите зашифрованное сообщение:" << std::endl;
    std::cin >> mess;

    RSA::Key privKey = RSA::CalculatePrivKey(publicKey);

    std::cout << "Расшифрованное сообщение:" << std::endl;
    std::cout << RSA::DecryptMessage(privKey, mess) << std::endl;

    return 0;
}
