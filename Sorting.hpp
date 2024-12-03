#pragma once

#include <cstddef>



namespace  Sorting{
enum class ArrayChoose {
    Static = 1,
    Dynamic = 2,
};

void SelectionSort(int* array, size_t arraySize, int& comparisons, int& swaps, bool ascending = true);
void BubbleSort(int* array, size_t arraySize, int& comparisons, int& swaps, bool ascending = true);

void ExecuteStaticArraySort();
void ExecuteDynamicArraySort();

void SelectSortMethod();


void RunApplication();
} // namespace  Sorting{}
