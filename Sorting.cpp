#include "Sorting.hpp"

#include <iomanip>
#include <iostream>
#include <random>

namespace {
const int kRandomMin = 0;
const int kRandomMax = 99;

const size_t kFixedArraySize = 5;

const int kColumnWidth = 20;
const int kColumnWidthTitle = 50;

void FillArrayRandomValues(int* array, size_t arraySize) {
    if (!array) {
        return;
    }

    std::random_device r{};
    std::default_random_engine engine(r());
    std::uniform_int_distribution distribution(kRandomMin, kRandomMax);

    for (size_t i = 0; i < arraySize; ++i) {
        array[i] = distribution(engine);
    }

}

void CopyArray(int* const initial, int* resulting , size_t arraySize) {
    if (!initial || !resulting) {
        return;
    }

    for (size_t i = 0; i < arraySize; ++i) {
        resulting[i] = initial[i];
    }
}

void PrintArray(const int* array, size_t arraySize) {
    if (!array) {
        return;
    }

    for (size_t i = 0; i < arraySize; ++i) {
        std::cout << array[i] << ' ';
    }

    std::cout << std::endl;
}

void PrintResult(int compareCount, int swapCount) {
    std::cout << "Количество сравнений: " << compareCount << std::endl;
    std::cout << "Количество перестановок: " << swapCount << std::endl;
}
}  // namespace

namespace Sorting {
void SortSelection(int* array, size_t arraySize, int& compareCount, int& swapCount, bool ascending) {
    if (!array) {
        return;
    }

    compareCount = 0;
    swapCount = 0;

    for (size_t i = 0; i < arraySize - 1; ++i) {
        size_t requiredIndex = i;
        for (size_t j = i+1; j < arraySize; ++j) {
            if (ascending ? (array[j] < array[requiredIndex]) : (array[j] > array[requiredIndex])) {
                requiredIndex = j;
            }

            ++compareCount;
        }

        if (requiredIndex != i) {
            std::swap(array[i], array[requiredIndex]);

            ++swapCount;
        }
    }

}

void SortBubble(int* array, size_t arraySize, int& compareCount, int& swapCount, bool ascending) {
    if (!array) {
        return;
    }

    compareCount = 0;
    swapCount = 0;

    bool swapped = false;

    for (size_t i = 0; i < arraySize - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < arraySize - i - 1; ++j) {
            if (ascending ? (array[j] > array[j + 1]) : (array[j] < array[j + 1])) {
                std::swap(array[j], array[j + 1]);

                ++swapCount;
                swapped = true;
            }

            ++compareCount;
        }

        if (!swapped) {
            return;
        }
    }
}



void RunStaticArrayExample() {
    int arraySelectionSort[kFixedArraySize];
    FillArrayRandomValues(arraySelectionSort, kFixedArraySize);

    int compareCount = 0;
    int swapCount = 0;

    int arrayBubbleSort[kFixedArraySize];

    CopyArray(arraySelectionSort, arrayBubbleSort, kFixedArraySize);

    std::cout << "Исходный массив: ";
    PrintArray(arraySelectionSort, kFixedArraySize);
    std::cout << "-------------------------------------------------\n";
    SortSelection(arraySelectionSort, kFixedArraySize, compareCount, swapCount);
    std::cout << "Сортировка выбором по возрастанию: ";
    PrintArray(arraySelectionSort, kFixedArraySize);
    PrintResult(compareCount, swapCount);
    std::cout << "-------------------------------------------------\n";
    SortSelection(arraySelectionSort, kFixedArraySize, compareCount, swapCount);
    std::cout << "Повторная сортировка выбором по возрастанию: ";
    PrintArray(arraySelectionSort, kFixedArraySize);
    PrintResult(compareCount, swapCount);
    std::cout << "-------------------------------------------------\n";
    SortSelection(arraySelectionSort, kFixedArraySize, compareCount, swapCount, false);
    std::cout << "Сортировка выбором по убыванию: ";
    PrintArray(arraySelectionSort, kFixedArraySize);
    PrintResult(compareCount, swapCount);
    std::cout << "-------------------------------------------------\n";
    SortBubble(arrayBubbleSort, kFixedArraySize, compareCount, swapCount);
    std::cout << "Сортировка пузырьком по возрастанию: ";
    PrintArray(arrayBubbleSort, kFixedArraySize);
    PrintResult(compareCount, swapCount);
    std::cout << "-------------------------------------------------\n";
    SortBubble(arrayBubbleSort, kFixedArraySize, compareCount, swapCount);
    std::cout << "Повторная сортировка пузырьком по возрастанию: ";
    PrintArray(arrayBubbleSort, kFixedArraySize);
    PrintResult(compareCount, swapCount);
    std::cout << "-------------------------------------------------\n";
    SortBubble(arrayBubbleSort, kFixedArraySize, compareCount, swapCount, false);
    std::cout << "Сортировка пузырьком по убыванию: ";
    PrintArray(arrayBubbleSort, kFixedArraySize);
    PrintResult(compareCount, swapCount);
}

void RunDynamicArrayExample() {
    int comparisons = 0;
    int swaps = 0;

    int inputSize = 0;
    size_t arraySize = 0;

    std::cout << "Введите размер динамического массива (больше 0): ";
    std::cin >> inputSize;

    if (inputSize <= 0) {
        std::cout << "Введен неправильный размер динамического массива." << std::endl;
        return;
    } else {
        arraySize = inputSize;
    }

    int* arraySelectionSort = new int[arraySize];

    FillArrayRandomValues(arraySelectionSort, arraySize);

    int* arrayBubbleSort = new int[arraySize];

    CopyArray(arraySelectionSort, arrayBubbleSort, arraySize);

    std::cout << "Сортировка массива из " << arraySize << " элементов" << std::endl;
    std::cout << std::setw(kColumnWidthTitle) << "Сравнения\t" << "Перестановки" << std::endl;
    std::cout << "---------------------|-----------------------------------------\n";
    SortSelection(arraySelectionSort, arraySize, comparisons, swaps);
    std::cout << "Сортировка выбором   |" << std::setw(kColumnWidth) << comparisons << std::setw(kColumnWidth) << swaps<<std::endl;
    std::cout << "---------------------|-----------------------------------------\n";
    SortBubble(arrayBubbleSort, arraySize, comparisons, swaps);
    std::cout << "Сортировка пузырьком |" << std::setw(kColumnWidth) << comparisons << std::setw(kColumnWidth) << swaps << std::endl;
    std::cout << "---------------------|-----------------------------------------\n";
    std::cout << std::endl;

    delete[] arrayBubbleSort;
    delete[] arraySelectionSort;
}

void SelectSortMethod() {
    int arrayType = 0;
    std::cout << "Виды массивов:\n"
              << "1. Статический массив\n"
              << "2. Динамический массив\n"
              << "Введите номер вида массива: ";
    std::cin >> arrayType;
    std::cout << std::endl;

    switch (static_cast<ArrayChoose>(arrayType)) {
        case ArrayChoose::Static:
            RunStaticArrayExample();
            break;
        case ArrayChoose::Dynamic:
            RunDynamicArrayExample();
            break;
        default:
            std::cout << "Введен неверный номер метода сортировки." << std::endl;
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
