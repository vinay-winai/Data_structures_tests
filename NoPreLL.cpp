#include <iostream>
#include <fstream>
#include <list>
#include <chrono>
#include <algorithm>

int main() {
    std::ifstream file("numbers.txt");
    if (!file) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return 1;
    }
    std::list<int> numbers;
    auto start = std::chrono::high_resolution_clock::now();
    int num;
    while (file >> num) {
        auto it = numbers.begin();
        while (it != numbers.end() && *it < num) {
            ++it;
        }
        numbers.insert(it, num);
    }
    file.close();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Total time taken to insert " << numbers.size() << " numbers: " << duration << " ms" << std::endl;

    std::ifstream deleteFile("delete.txt");
    if (!deleteFile) {
        std::cerr << "Failed to open delete file for reading." << std::endl;
        return 1;
    }

    start = std::chrono::high_resolution_clock::now();
    int deleteval;
    while (deleteFile >> deleteval) {
        std::list<int>::iterator pos = std::find(numbers.begin(), numbers.end(), deleteval);
        numbers.erase(pos);
    }
    deleteFile.close();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Deleted, " << numbers.size() << " numbers left. Time: " << duration << " ms" << std::endl;
    return 0;
}

// Results
// Total time taken to insert 100000 numbers: 24874 ms
// Deleted, 0 numbers left. Time: 27117 ms