#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <sstream>

// ── Detect and strip UTF-16 BOM, convert to UTF-8 string ─────
// Handles: UTF-16 LE, UTF-16 BE, UTF-8 BOM, plain UTF-8
std::string readFileAsUTF8(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filename);

    // Read entire file into buffer
    std::string buffer((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    if (buffer.size() < 2) return buffer;

    unsigned char b0 = (unsigned char)buffer[0];
    unsigned char b1 = (unsigned char)buffer[1];

    // UTF-16 Little Endian (FF FE)
    if (b0 == 0xFF && b1 == 0xFE) {
        std::string utf8;
        utf8.reserve(buffer.size() / 2);
        // Skip BOM (first 2 bytes), read pairs of bytes
        for (size_t i = 2; i + 1 < buffer.size(); i += 2) {
            unsigned char lo = (unsigned char)buffer[i];
            unsigned char hi = (unsigned char)buffer[i + 1];
            uint16_t ch = (uint16_t)(hi << 8 | lo);
            if (ch == '\r') continue; // strip \r
            if (ch < 0x80) {
                utf8 += (char)ch;
            } else if (ch < 0x800) {
                utf8 += (char)(0xC0 | (ch >> 6));
                utf8 += (char)(0x80 | (ch & 0x3F));
            } else {
                utf8 += (char)(0xE0 | (ch >> 12));
                utf8 += (char)(0x80 | ((ch >> 6) & 0x3F));
                utf8 += (char)(0x80 | (ch & 0x3F));
            }
        }
        return utf8;
    }

    // UTF-16 Big Endian (FE FF)
    if (b0 == 0xFE && b1 == 0xFF) {
        std::string utf8;
        utf8.reserve(buffer.size() / 2);
        for (size_t i = 2; i + 1 < buffer.size(); i += 2) {
            unsigned char hi = (unsigned char)buffer[i];
            unsigned char lo = (unsigned char)buffer[i + 1];
            uint16_t ch = (uint16_t)(hi << 8 | lo);
            if (ch == '\r') continue;
            if (ch < 0x80) {
                utf8 += (char)ch;
            } else if (ch < 0x800) {
                utf8 += (char)(0xC0 | (ch >> 6));
                utf8 += (char)(0x80 | (ch & 0x3F));
            } else {
                utf8 += (char)(0xE0 | (ch >> 12));
                utf8 += (char)(0x80 | ((ch >> 6) & 0x3F));
                utf8 += (char)(0x80 | (ch & 0x3F));
            }
        }
        return utf8;
    }

    // UTF-8 BOM (EF BB BF) — just strip the BOM
    if (b0 == 0xEF && b1 == 0xBB && buffer.size() > 2 &&
        (unsigned char)buffer[2] == 0xBF) {
        return buffer.substr(3);
    }

    // Plain UTF-8 or ASCII — strip \r just in case
    std::string clean;
    clean.reserve(buffer.size());
    for (char c : buffer)
        if (c != '\r') clean += c;
    return clean;
}

// ── Load every word from a file (auto-detects UTF-16) ────────
std::vector<std::string> loadWords(const std::string& filename) {
    std::string content = readFileAsUTF8(filename);
    std::istringstream stream(content);
    std::vector<std::string> words;
    words.reserve(400000);
    std::string word;
    while (stream >> word) words.push_back(word);
    return words;
}

// ── Pick N random words, shuffle, write dataset.txt ──────────
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
    out.flush();
    out.close();
    if (out.fail())
        throw std::runtime_error("Failed to write dataset: " + datasetFile);

    std::cout << "  Created : " << datasetFile
              << "  (" << n << " randomised words)" << std::endl;
    return dataset;
}

// ── Write sorted words to a .txt file ────────────────────────
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
    out.flush();
    out.close();
    if (out.fail())
        throw std::runtime_error("Failed to write output: " + filename);

    std::cout << "  Saved   : " << filename
              << "  (" << words.size() << " words)" << std::endl;
}
