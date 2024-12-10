#pragma once

#include <cstddef>

namespace Sorting {
enum class ArrayChoose {
    Static = 1,
    Dynamic = 2,
};

void SortSelection(int* array, size_t arraySize, int& comparisons, int& swaps, bool ascending = true);
void SortBubble(int* array, size_t arraySize, int& comparisons, int& swaps, bool ascending = true);

void RunStaticArrayExample();
void RunDynamicArrayExample();

void SelectSortMethod();

void RunApplication();
}  // namespace Sorting
