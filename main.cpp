/*
 * ================================================================
 *  Sorting Strategies — 100,000 words
 *  ----------------------------------------------------------------
 *  Usage:
 *    ./sorting <input_file.txt>
 *
 *  Example:
 *    ./sorting words_alpha.txt
 *
 *  The program reads the input file, picks 100,000 random words,
 *  sorts them with three algorithms, and writes the results as
 *  .txt files in the SAME directory where the command is run.
 *
 *  Output files produced:
 *    dataset.txt            <- 100k words, randomised (input for sorters)
 *    output_quicksort.txt   <- sorted by QuickSort
 *    output_heapsort.txt    <- sorted by HeapSort
 *    output_avl.txt         <- sorted by AVL Tree (inorder)
 * ================================================================
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#include "dataset.h"
#include "quicksort.h"
#include "heapsort.h"
#include "avl_tree.h"

using namespace std;
using namespace chrono;

// ── Timer ─────────────────────────────────────────────────────
struct Timer {
    time_point<high_resolution_clock> t0;
    void   start()           { t0 = high_resolution_clock::now(); }
    double elapsedMs() const {
        return duration<double, milli>(
            high_resolution_clock::now() - t0).count();
    }
};

// ── UI helpers ────────────────────────────────────────────────
void printUsage(const char* prog) {
    cerr << "\n  Usage: " << prog << " <input_file.txt>\n\n";
    cerr << "  Example:\n";
    cerr << "    " << prog << " words_alpha.txt\n\n";
    cerr << "  The input file must contain at least 100,000 words (one per line).\n\n";
}

void printBanner() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════╗\n";
    cout << "║       SORTING STRATEGIES — 100k WORDS        ║\n";
    cout << "║  QuickSort | HeapSort | AVL Tree (inorder)   ║\n";
    cout << "╚══════════════════════════════════════════════╝\n\n";
}

void printResults(double qsMs, double hsMs, double avlMs) {
    cout << "\n";
    cout << "┌──────────────────────────────────────────────┐\n";
    cout << "│              TIMING RESULTS                  │\n";
    cout << "├─────────────────────┬────────────────────────┤\n";
    cout << "│ Algorithm           │ Time                   │\n";
    cout << "├─────────────────────┼────────────────────────┤\n";
    printf("│ QuickSort           │ %10.2f ms           │\n", qsMs);
    printf("│ HeapSort            │ %10.2f ms           │\n", hsMs);
    printf("│ AVL Tree (inorder)  │ %10.2f ms           │\n", avlMs);
    cout << "└─────────────────────┴────────────────────────┘\n";
}

// ── Main ──────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    printBanner();

    // Require exactly one argument: the input file
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }

    string inputFile = argv[1];

    // Output files are written in the current working directory
    // (wherever the user runs the command from)
    string datasetOut  = "dataset.txt";
    string quickOut    = "output_quicksort.txt";
    string heapOut     = "output_heapsort.txt";
    string avlOut      = "output_avl.txt";

    // ── Step 1: build randomised dataset ─────────────────────
    cout << "[ STEP 1 ] Building dataset from: " << inputFile << "\n";
    vector<string> dataset;
    try {
        dataset = createDataset(inputFile, datasetOut, 100000, 42);
    } catch (const exception& e) {
        cerr << "\n  ERROR: " << e.what() << "\n\n";
        return 1;
    }

    Timer  t;
    double qsMs = 0, hsMs = 0, avlMs = 0;

    // ── Step 2: QuickSort ─────────────────────────────────────
    cout << "\n[ STEP 2 ] QuickSort\n";
    {
        vector<string> data = dataset;
        t.start();
        runQuickSort(data);
        qsMs = t.elapsedMs();
        printf("  Sorted %zu words in %.2f ms\n", data.size(), qsMs);
        writeOutput(quickOut, data,
                    "QuickSort (median-of-three pivot, std::vector)", qsMs);
    }

    // ── Step 3: HeapSort ──────────────────────────────────────
    cout << "\n[ STEP 3 ] HeapSort\n";
    {
        vector<string> data = dataset;
        t.start();
        runHeapSort(data);
        hsMs = t.elapsedMs();
        printf("  Sorted %zu words in %.2f ms\n", data.size(), hsMs);
        writeOutput(heapOut, data,
                    "HeapSort (binary max-heap, in-place)", hsMs);
    }

    // ── Step 4: AVL Tree ──────────────────────────────────────
    cout << "\n[ STEP 4 ] AVL Tree\n";
    {
        AVLTree avl;
        t.start();
        for (const string& w : dataset) avl.insert(w);
        vector<string> sorted = avl.getSorted();
        avlMs = t.elapsedMs();
        printf("  Inserted & traversed %zu words in %.2f ms\n",
               sorted.size(), avlMs);
        writeOutput(avlOut, sorted,
                    "AVL Tree (self-balancing BST, inorder traversal)", avlMs);
    }

    // ── Summary ───────────────────────────────────────────────
    printResults(qsMs, hsMs, avlMs);

    cout << "\n  Output files (in current directory):\n";
    cout << "    " << datasetOut  << "   <- randomised input\n";
    cout << "    " << quickOut    << "   <- QuickSort\n";
    cout << "    " << heapOut     << "   <- HeapSort\n";
    cout << "    " << avlOut      << "   <- AVL Tree\n\n";

    return 0;
}
