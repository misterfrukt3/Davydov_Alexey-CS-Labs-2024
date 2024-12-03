#include "Sorting.hpp"

#include <iomanip>
#include <iostream>
#include <random>

namespace {
const int kMinIntElement = 0;
const int kMaxIntElement = 99;

const size_t kStaticArraySize = 7;

const int kColumnWidth = 20;
const int kColumnWidthTitle = 50;

void FillArrayWithRandomValues(int* array, size_t arraySize) {
    if (!array) {
        return;
    }

    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinIntElement, kMaxIntElement);

    for (size_t i = 0; i < arraySize; ++i) {
        array[i] = distribution(randomEngine);
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

void PrintResult(int comparisons, int swaps) {
    std::cout << "Количество сравнений: " << comparisons << std::endl;
    std::cout << "Количество перестановок: " << swaps << std::endl;

    std::cout << std::endl;
}
}  // namespace

namespace Sorting {
void BubbleSort(int* array, size_t arraySize, int& comparisons, int& swaps, bool ascending) {
    if (!array) {
        return;
    }

    comparisons = 0;
    swaps = 0;

    bool swapped = false;

    for (size_t i = 0; i < arraySize - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < arraySize - i - 1; ++j) {
            if (ascending ? (array[j] > array[j + 1]) : (array[j] < array[j + 1])) {
                std::swap(array[j], array[j + 1]);

                ++swaps;
                swapped = true;
            }

            ++comparisons;
        }

        if (!swapped) {
            return;
        }
    }
}

void SelectionSort(int* array, size_t arraySize, int& comparisons, int& swaps, bool ascending) {
    if (!array) {
        return;
    }

    comparisons = 0;
    swaps = 0;

    for (size_t i = 0; i < arraySize - 2; ++i) {
        size_t requiredIndex = i;
        for (size_t j = i + 1; j < arraySize; ++j) {
            if (ascending ? (array[j] < array[requiredIndex]) : (array[j] > array[requiredIndex])) {
                requiredIndex = j;
            }

            ++comparisons;
        }

        if (requiredIndex != i) {
            std::swap(array[i], array[requiredIndex]);

            ++swaps;
        }
    }
}

void ExecuteStaticArraySort() {
    int arraySelectionSort[kStaticArraySize];
    FillArrayWithRandomValues(arraySelectionSort, kStaticArraySize);

    int comparisons = 0;
    int swaps = 0;

    int arrayBubbleSort[kStaticArraySize];

    CopyArray(arraySelectionSort, arrayBubbleSort, kStaticArraySize);

    std::cout << "Исходный массив: ";
    PrintArray(arraySelectionSort, kStaticArraySize);
    std::cout << std::endl;

    SelectionSort(arraySelectionSort, kStaticArraySize, comparisons, swaps);
    std::cout << "Сортировка выбором по возрастанию: ";
    PrintArray(arraySelectionSort, kStaticArraySize);
    PrintResult(comparisons, swaps);

    SelectionSort(arraySelectionSort, kStaticArraySize, comparisons, swaps);
    std::cout << "Повторная сортировка выбором по возрастанию: ";
    PrintArray(arraySelectionSort, kStaticArraySize);
    PrintResult(comparisons, swaps);

    SelectionSort(arraySelectionSort, kStaticArraySize, comparisons, swaps, false);
    std::cout << "Сортировка выбором по убыванию: ";
    PrintArray(arraySelectionSort, kStaticArraySize);
    PrintResult(comparisons, swaps);

    std::cout << std::endl;

    BubbleSort(arrayBubbleSort, kStaticArraySize, comparisons, swaps);
    std::cout << "Сортировка пузырьком по возрастанию: ";
    PrintArray(arrayBubbleSort, kStaticArraySize);
    PrintResult(comparisons, swaps);

    BubbleSort(arrayBubbleSort, kStaticArraySize, comparisons, swaps);
    std::cout << "Повторная сортировка пузырьком по возрастанию: ";
    PrintArray(arrayBubbleSort, kStaticArraySize);
    PrintResult(comparisons, swaps);

    BubbleSort(arrayBubbleSort, kStaticArraySize, comparisons, swaps, false);
    std::cout << "Сортировка пузырьком по убыванию: ";
    PrintArray(arrayBubbleSort, kStaticArraySize);
    PrintResult(comparisons, swaps);

    std::cout << '\n';
}

void ExecuteDynamicArraySort() {
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

    FillArrayWithRandomValues(arraySelectionSort, arraySize);

    int* arrayBubbleSort = new int[arraySize];

    CopyArray(arraySelectionSort, arrayBubbleSort, arraySize);

    std::cout << "Сортировка массива из" << arraySize << "элементов" << std::endl;
    std::cout << std::setw(kColumnWidthTitle) << "Сравнения\t" << "Перестановки" << std::endl;
    SelectionSort(arraySelectionSort, arraySize, comparisons, swaps);
    std::cout << "Сортировка выбором  " << std::setw(kColumnWidth) << comparisons << std::setw(kColumnWidth) << swaps << std::endl;

    BubbleSort(arrayBubbleSort, arraySize, comparisons, swaps);
    std::cout << "Сортировка пузырьком" << std::setw(kColumnWidth) << comparisons << std::setw(kColumnWidth) << swaps << std::endl;
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
            ExecuteStaticArraySort();
            break;
        case ArrayChoose::Dynamic:
            ExecuteDynamicArraySort();
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
