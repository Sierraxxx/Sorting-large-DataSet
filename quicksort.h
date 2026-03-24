#pragma once
#include <vector>
#include <string>

/**
 * QuickSort over std::vector<string>
 * Average complexity: O(n log n)
 * Worst case:         O(n^2)  [mitigated with median-of-three pivot]
 */

int medianOfThree(std::vector<std::string>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])  std::swap(arr[low],  arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low],  arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid],  arr[high]);
    // Place pivot at high-1
    std::swap(arr[mid], arr[high]);
    return high;
}

int partition(std::vector<std::string>& arr, int low, int high) {
    int pivotIdx = medianOfThree(arr, low, high);
    std::string pivot = arr[pivotIdx];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<std::string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void runQuickSort(std::vector<std::string>& arr) {
    if (!arr.empty())
        quickSort(arr, 0, (int)arr.size() - 1);
}
