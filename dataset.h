#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>

// Load every word from a file
std::vector<std::string> loadWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filename);
    std::vector<std::string> words;
    words.reserve(400000);
    std::string word;
    while (file >> word) words.push_back(word);
    return words;
}

// Pick N random words from source, shuffle, write dataset.txt next to the binary
std::vector<std::string> createDataset(const std::string& sourceFile,
                                        const std::string& datasetFile,
                                        int n = 100000,
                                        unsigned int seed = 42) {
    std::cout << "  Loading : " << sourceFile << " ..." << std::endl;
    std::vector<std::string> all = loadWords(sourceFile);

    if ((int)all.size() < n)
        throw std::runtime_error(
            "Source file has only " + std::to_string(all.size()) +
            " words, but " + std::to_string(n) + " are required.");

    std::mt19937 rng(seed);
    std::shuffle(all.begin(), all.end(), rng);
    std::vector<std::string> dataset(all.begin(), all.begin() + n);

    std::ofstream out(datasetFile);
    if (!out.is_open())
        throw std::runtime_error("Cannot write: " + datasetFile);
    for (const std::string& w : dataset) out << w << "\n";
    out.close();

    std::cout << "  Created : " << datasetFile
              << "  (" << n << " randomised words)" << std::endl;
    return dataset;
}

// Write sorted words to a .txt file in the given path
void writeOutput(const std::string& filename,
                 const std::vector<std::string>& words,
                 const std::string& method,
                 double timeMs) {
    std::ofstream out(filename);
    if (!out.is_open())
        throw std::runtime_error("Cannot write: " + filename);
    out << "# Method : " << method << "\n";
    out << "# Words  : " << words.size() << "\n";
    out << "# Time   : " << timeMs << " ms\n";
    out << "# -----------------------------------------\n";
    for (const std::string& w : words) out << w << "\n";
    out.close();
    std::cout << "  Saved   : " << filename << std::endl;
}
