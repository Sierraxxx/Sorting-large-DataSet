# Sorting Strategies — 100,000 Words

Sorts a large word dataset using three algorithms and writes the results as `.txt` files.

## Algorithms

| # | Algorithm    | Structure              | Complexity              |
|---|--------------|------------------------|-------------------------|
| 1 | QuickSort    | `std::vector`          | O(n log n) average      |
| 2 | HeapSort     | Binary Max-Heap        | O(n log n) always       |
| 3 | AVL Tree     | Self-balancing BST     | O(n log n) + O(n) walk  |

## Project Structure

```
sorting-project/
├── CMakeLists.txt       ← CMake build file (CLion uses this)
├── README.md
├── .gitignore
├── main.cpp             ← entry point
└── src/
    ├── quicksort.h      ← QuickSort implementation
    ├── heapsort.h       ← HeapSort implementation
    ├── avl_tree.h       ← AVL Tree implementation
    └── dataset.h        ← file I/O utilities
```

## Requirements

- g++ with C++17 (`g++ --version`)
- `words_alpha.txt` with at least 100,000 words (provided by lecturer)

---

## How to build & run

### Option A — CLion (recommended)

1. **File → Open** → select the `sorting-project` folder
2. CLion detects `CMakeLists.txt` automatically → click **OK / Trust**
3. Open **Run → Edit Configurations**
4. In the **Program arguments** field, type the full path to your input file:
   ```
   /Users/you/Downloads/words_alpha.txt
   ```
5. Press **▶ Run**

Output files are written to the directory where the binary runs (`cmake-build-debug/` by default in CLion — you'll see them listed in the terminal output).

---

### Option B — Terminal (any OS with g++)

```bash
# 1. Compile
g++ -std=c++17 -O2 -I src -o sorting main.cpp

# 2. Run — pass the input file as argument
./sorting words_alpha.txt

# Or with a full path:
./sorting /path/to/words_alpha.txt
```

Output files appear in the **current directory**:
```
dataset.txt            ← 100k words, randomised
output_quicksort.txt   ← sorted by QuickSort
output_heapsort.txt    ← sorted by HeapSort
output_avl.txt         ← sorted by AVL Tree
```

---

### Option C — CMake in terminal

```bash
cmake -B build
cmake --build build
./build/sorting words_alpha.txt
```

---

## Expected terminal output

```
╔══════════════════════════════════════════════╗
║       SORTING STRATEGIES — 100k WORDS        ║
║  QuickSort | HeapSort | AVL Tree (inorder)   ║
╚══════════════════════════════════════════════╝

[ STEP 1 ] Building dataset from: words_alpha.txt
  Loading : words_alpha.txt ...
  Created : dataset.txt  (100000 randomised words)

[ STEP 2 ] QuickSort
  Sorted 100000 words in 42.31 ms
  Saved   : output_quicksort.txt

[ STEP 3 ] HeapSort
  Sorted 100000 words in 79.14 ms
  Saved   : output_heapsort.txt

[ STEP 4 ] AVL Tree
  Inserted & traversed 100000 words in 72.55 ms
  Saved   : output_avl.txt

┌──────────────────────────────────────────────┐
│              TIMING RESULTS                  │
├─────────────────────┬────────────────────────┤
│ Algorithm           │ Time                   │
├─────────────────────┼────────────────────────┤
│ QuickSort           │      42.31 ms          │
│ HeapSort            │      79.14 ms          │
│ AVL Tree (inorder)  │      72.55 ms          │
└─────────────────────┴────────────────────────┘
```
