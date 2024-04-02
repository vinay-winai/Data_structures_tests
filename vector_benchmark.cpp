#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm> 

using namespace std;

const int ARRAY_SIZE = 100'000'000;

void benchmarkLookupByValue(const vector<int>& array) {
    int target1 = array[0]; 
    int target2 = array[ARRAY_SIZE / 4]; 
    int target3 = array[ARRAY_SIZE / 2];
    int target4 = array[3 * ARRAY_SIZE / 4];
    int target5 = array[ARRAY_SIZE - 1]; 

    auto start = chrono::high_resolution_clock::now();
    find(array.begin(), array.end(), target1); // Find first
    find(array.begin(), array.end(), target2); 
    find(array.begin(), array.end(), target3); 
    find(array.begin(), array.end(), target4); 
    find(array.begin(), array.end(), target5); 
    auto end = chrono::high_resolution_clock::now();

    cout << "Lookup By Value Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";
}

void benchmarkInsert(vector<int> array) { // Pass by value to work on a copy
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, INT_MAX);
    int valueToInsert = distribution(generator);  

    // Insert at beginning
    auto start = chrono::high_resolution_clock::now();
    array.insert(array.begin(), valueToInsert); 
    auto end = chrono::high_resolution_clock::now();
    cout << "Insert (Beginning) Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Insert at middle 
    start = chrono::high_resolution_clock::now();
    array.insert(array.begin() + ARRAY_SIZE / 2, valueToInsert); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (Middle) Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Insert at end
    start = chrono::high_resolution_clock::now();
    array.insert(array.end(), valueToInsert); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (End) Time: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
         << "ns\n";
}

void benchmarkDelete(vector<int> array) { 
    // Delete at beginning
    auto start = chrono::high_resolution_clock::now();
    array.erase(array.begin()); 
    auto end = chrono::high_resolution_clock::now();
    cout << "Delete (Beginning) Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Delete at middle
    start = chrono::high_resolution_clock::now();
    array.erase(array.begin() + ARRAY_SIZE / 2); 
    end = chrono::high_resolution_clock::now();
    cout << "Delete (Middle) Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Delete at end
    start = chrono::high_resolution_clock::now();
    array.erase(array.end() - 1); 
    end = chrono::high_resolution_clock::now();
    cout << "Delete (End) Time: " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
         << "ns\n";
}

int main() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, INT_MAX);

    vector<int> array;
    array.reserve(ARRAY_SIZE); // Pre-allocate for efficiency

    // Fill the array with random integers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array.push_back(distribution(generator)); 
    }
    int run = 32;
    while (run>0){
          benchmarkLookupByValue(array);
          benchmarkInsert(array);
          benchmarkDelete(array);
    run--;
    }
    return 0;
}

// Best
// Memory 300MB - 1GB, avg 600MB 
// CPU ~ 16% - used around 6 vCPUs
// Lookup By Value Time: 64ms
// Insert (Beginning) Time: 60ms
// Insert (Middle) Time: 18ms
// Insert (End) Time: 300ns
// Delete (Beginning) Time: 23ms
// Delete (Middle) Time: 11ms
// Delete (End) Time: 100ns