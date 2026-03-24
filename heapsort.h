#pragma once
#include <vector>
#include <string>

/**
 * HeapSort using a Binary Max-Heap built in-place over std::vector<string>
 * Complexity: O(n log n) always — no worst case degradation
 */

void heapify(std::vector<std::string>& arr, int n, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void runHeapSort(std::vector<std::string>& arr) {
    int n = (int)arr.size();

    // Phase 1: Build max-heap (bottom-up)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Phase 2: Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);   // move current root to end
        heapify(arr, i, 0);          // re-heapify reduced heap
    }
}
