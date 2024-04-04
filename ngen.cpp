#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>



int main() {
    const int numNumbers = 100'000;
    std::vector<int> numbers(numNumbers);

    // Fill the vector with numbers from 1 to n
    for (int i = 0; i < numNumbers; ++i) {
        numbers[i] = i;
    }

    // Shuffle the vector randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    std::ofstream file("delete.txt");
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    for (int num : numbers) {
        file << num << "\n";
    }
    file.close();
    std::cout << "Numbers written to file." << std::endl;

    return 0;
}