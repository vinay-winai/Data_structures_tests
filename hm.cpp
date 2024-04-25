#include <iostream>
#include <unordered_map>
#include <chrono>

int main() {
    std::unordered_map<int, int> hash_map;

    // Insert 10 million keys into the hash map
    for (int i = 0; i < 100'000'000; ++i) {
        hash_map[i] = i;
    }

    long long sum = 0;

    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    // Sum the keys in the hash map
    for (const auto& pair : hash_map) {
        sum += pair.first;
    }

    // Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate elapsed time
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Sum of keys: " << sum << std::endl;
    std::cout << "Time elapsed (milliseconds): " << elapsed.count() << std::endl;

    return 0;
}

// Result:

// Iteration time: ~1 sec