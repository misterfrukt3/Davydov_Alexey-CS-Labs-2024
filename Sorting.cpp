#include "Sorting.hpp"

#include <iostream>

namespace Sorting {
void SelectSortMethod() {
    int taskNumber = 0;

    std::cout << "Выберите номер, интересующего вас метода соортировки, и введите его в консоль для перехода к нему\n";
    std::cout << "[1] Сортировка выбором\n";
    std::cout << "[2] Сортировка пузырьком\n";

    std::cin >> taskNumber;
    switch (static_cast<>(taskNumber)) {
        case:
            ();
            break;
        case:
            ();
            break;
        default:
            std::cout << "Такого номера задания нет(Введите значение от 1 до 2)\n";
            break;
    }
}

void RunApplication() {
    char continueExecution = 'y';

    while (continueExecution == 'y') {
        SelectSortMethod();
        std::cout << "Продолжить работу? (y/n)\n";
        std::cin >> continueExecution;
    }
}
}  // namespace Sorting
