#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm> 

using namespace std;

const int ARRAY_SIZE = 100'000'000;

bool deleteByValue(std::vector<int>& vec) {
    auto it = std::find(vec.begin(), vec.end(), 1); // Find the element
     if (it != vec.end()) { // If element found
          vec.erase(it);      // Delete the element
          return true;        // Indicate success
     } else {
          return false;       // Indicate element not found
     }
}

bool insertAtFirstZero(std::vector<int>& vec) {
    auto it = std::find(vec.begin(), vec.end(), 0);  // Find the first '0'
    if (it != vec.end()) {  
        vec.insert(it, 1);  // Insert '1' before the '0'
        return true;            // Indicate success
    } else {
        return false;           // Indicate '0' not found
    }
}

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
         << "ms\nIn nanosecs: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << "ns\n";
}

void benchmarkInsert(std::vector<int>& array) { 
     // Pre-set insertion points to 0
    array[0] = 0;
    array[ARRAY_SIZE / 4] = 0;
    array[ARRAY_SIZE / 2] = 0;
    array[3 * ARRAY_SIZE / 4] = 0;
    array[ARRAY_SIZE - 1] = 0; 
    int valueToInsert = 1;

    // Insert at beginning
    auto start = chrono::high_resolution_clock::now();
    array.insert(array.begin(), valueToInsert); 
    auto end = chrono::high_resolution_clock::now();
    cout << "Insert (Beginning) Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";
    
    // Insert at q1 
    start = chrono::high_resolution_clock::now();
    bool success = insertAtFirstZero(array); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (q1) Time: "
         << (success ? "Success " : "Failure")
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    
    // Insert at middle 
    start = chrono::high_resolution_clock::now();
    success = insertAtFirstZero(array); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (Middle) Time: " 
         << (success ? "Success " : "Failure")
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Insert at q3 
    start = chrono::high_resolution_clock::now();
    success = insertAtFirstZero(array); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (q3) Time: " 
         << (success ? "Success " : "Failure")
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

void benchmarkDelete(std::vector<int>& array) { 
    // Delete at beginning

    auto start = chrono::high_resolution_clock::now();
    array.erase(array.begin()); 
    auto end = chrono::high_resolution_clock::now();
    cout << "Delete (Beginning) Time: " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Delete at q1
    start = chrono::high_resolution_clock::now();
    bool success = deleteByValue(array); 
    end = chrono::high_resolution_clock::now();
    cout << "Delete (q1) Time: " 
         << (success ? "Success " : "Failure")
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Delete at mid
    start = chrono::high_resolution_clock::now();
    success = deleteByValue(array);
    end = chrono::high_resolution_clock::now();
    cout << "Delete (Middle) Time: "
         << (success ? "Success " : "Failure") 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";
    
    // Delete at q3
    start = chrono::high_resolution_clock::now();
    success = deleteByValue(array);
    end = chrono::high_resolution_clock::now();
    cout << "Delete (q3) Time: "
         << (success ? "Success " : "Failure") 
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
    std::uniform_int_distribution<int> distribution(2, INT_MAX);

    vector<int> array;
    array.reserve(ARRAY_SIZE); // Pre-allocate for efficiency

    // Fill the array with random integers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array.push_back(distribution(generator)); 
    }
    int run = 3;
    while (run>0){
          benchmarkLookupByValue(array);
          benchmarkInsert(array);
          benchmarkDelete(array);
    run--;
    }
    return 0;
}

// Best: Random Access
// Memory 300MB - 1GB, avg 600MB 
// CPU ~ 16% - used around 6 vCPUs
// Lookup By Value Time: 64ms
// Insert (Beginning) Time: 60ms
// Insert (Middle) Time: 18ms
// Insert (End) Time: 300ns
// Delete (Beginning) Time: 23ms
// Delete (Middle) Time: 11ms
// Delete (End) Time: 100ns

// Sequential access with no array copies
// Lookup By Value Time: 63ms
// In nanosecs: 63643400ns
// Insert (Beginning) Time: 64ms
// Insert (q1) Time: Success 34ms
// Insert (Middle) Time: Success 35ms
// Insert (q3) Time: Success 34ms
// Insert (End) Time: 500ns
// Delete (Beginning) Time: 24ms
// Delete (q1) Time: Success 24ms
// Delete (Middle) Time: Success 25ms
// Delete (q3) Time: Success 23ms
// Delete (End) Time: 100ns
// Lookup By Value Time: 0ms
// In nanosecs: 200ns
// Insert (Beginning) Time: 34ms
// Insert (q1) Time: Success 35ms
// Insert (Middle) Time: Success 35ms
// Insert (q3) Time: Success 34ms
// Insert (End) Time: 500ns
// Delete (Beginning) Time: 25ms
// Delete (q1) Time: Success 23ms
// Delete (Middle) Time: Success 23ms
// Delete (q3) Time: Success 24ms
// Delete (End) Time: 0ns