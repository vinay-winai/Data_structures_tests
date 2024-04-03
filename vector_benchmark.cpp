#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm> 

using namespace std;

const int ARRAY_SIZE = 100'000'000;

bool deleteByValue(std::vector<int>& vec, int item) {
     auto it = std::find(vec.begin(), vec.end(), item); // Find the element
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
     bool success = deleteByValue(array, 1); 
     end = chrono::high_resolution_clock::now();
     cout << "Delete (q1) Time: " 
          << (success ? "Success " : "Failure")
          << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
          << "ms\n";

     // Delete at mid
     start = chrono::high_resolution_clock::now();
     success = deleteByValue(array, 1);
     end = chrono::high_resolution_clock::now();
     cout << "Delete (Middle) Time: "
          << (success ? "Success " : "Failure") 
          << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
          << "ms\n";
    
     // Delete at q3
     start = chrono::high_resolution_clock::now();
     success = deleteByValue(array, 1);
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
     auto start = chrono::high_resolution_clock::now();
     for (int i = 0; i < ARRAY_SIZE; i++) {
          array.push_back(distribution(generator)); 
     }
     auto end = chrono::high_resolution_clock::now();
     cout << "Pre-allocate Time: " 
          << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
          << "ms\n";
     
     int run = 2;
     while (run>0){
          benchmarkLookupByValue(array);
          benchmarkInsert(array);
          benchmarkDelete(array);
     run--;
     }

     start = chrono::high_resolution_clock::now();
     // Change values to 0 at multiples of array length / #insertions
     int insertions = 100;
     int step = array.size() / insertions; 
     for (int i = 0; i < array.size(); i += step) {
          array[i] = 0;
     } 
     // Insert 1 next to existing 0s
     for (int i = 0; i < array.size(); ++i) {
          if (array[i] == 0) {
               if (i < array.size() - 1) {  // Ensure we don't insert beyond bounds
                    array.insert(array.begin() + i + 1, 1);
                    ++i;  // Skip over the inserted element
               }
          }
     }
     end = chrono::high_resolution_clock::now();
     cout << "Heavy Time: " 
     << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
     << "ms\n";
     
     start = chrono::high_resolution_clock::now();
     // delete # scattered items 
     int deletions = 100;
     while (deletions>0) {
          deleteByValue(array, 1);
          deletions--; 
     }
     end = chrono::high_resolution_clock::now();
     cout << "Heavy Delete Time: " 
     << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
     << "ms\n";
     
     
     start = chrono::high_resolution_clock::now();
     // loopup adv
     long long sum = 0;
     for (int i = 0; i < array.size(); ++i) {
          sum+=array[i];
     }
     end = chrono::high_resolution_clock::now();
     cout << sum
     << "\nHeavy Lookup Time: "
     << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
     << "ms\n";

     return 0;
}

// Sequential access with no array copies
// 2 shot 100 mil
// Memory 382MB 
// CPU MAX ~ 14%
// Pre-allocate Time: 256ms
// Lookup By Value Time: 64ms
// In nanosecs: 64612900ns
// Insert (Beginning) Time: 62ms
// Insert (q1) Time: Success 40ms
// Insert (Middle) Time: Success 34ms
// Insert (q3) Time: Success 34ms
// Insert (End) Time: 400ns
// Delete (Beginning) Time: 23ms
// Delete (q1) Time: Success 25ms
// Delete (Middle) Time: Success 23ms
// Delete (q3) Time: Success 23ms
// Delete (End) Time: 100ns
// Lookup By Value Time: 0ms
// In nanosecs: 100ns
// Insert (Beginning) Time: 35ms
// Insert (q1) Time: Success 31ms
// Insert (Middle) Time: Success 34ms
// Insert (q3) Time: Success 33ms
// Insert (End) Time: 200ns
// Delete (Beginning) Time: 23ms
// Delete (q1) Time: Success 24ms
// Delete (Middle) Time: Success 23ms
// Delete (q3) Time: Success 24ms
// Delete (End) Time: 100ns
// Heavy Time: 1694ms
// Heavy Delete Time: 2681ms
// 107360143194569021
// Heavy Lookup Time: 25ms

// Sequential 2 shot 10 mil
// Pre-allocate Time: 25ms
// Lookup By Value Time: 6ms
// In nanosecs: 6976200ns
// Insert (Beginning) Time: 5ms
// Insert (q1) Time: Success 3ms
// Insert (Middle) Time: Success 3ms
// Insert (q3) Time: Success 3ms
// Insert (End) Time: 400ns
// Delete (Beginning) Time: 2ms
// Delete (q1) Time: Success 2ms
// Delete (Middle) Time: Success 2ms
// Delete (q3) Time: Success 2ms
// Delete (End) Time: 100ns
// Lookup By Value Time: 0ms
// In nanosecs: 200ns
// Insert (Beginning) Time: 3ms
// Insert (q1) Time: Success 3ms
// Insert (Middle) Time: Success 3ms
// Insert (q3) Time: Success 4ms
// Insert (End) Time: 400ns
// Delete (Beginning) Time: 3ms
// Delete (q1) Time: Success 2ms
// Delete (Middle) Time: Success 2ms
// Delete (q3) Time: Success 2ms
// Delete (End) Time: 100ns
// Heavy Time: 147ms
// Heavy Delete Time: 247ms
// 10740104882810568
// Heavy Lookup Time: 2ms