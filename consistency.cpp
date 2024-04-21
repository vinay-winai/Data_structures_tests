#include <iostream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    const int NUM_ELEMENTS = 100'000'000;
    const int TARGET_INDEX = NUM_ELEMENTS;

    // Vector setup
    vector<int> vec(NUM_ELEMENTS);
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        vec[i] = i; // Fill with sequential values
    }

    // Linked list setup
    list<int> llist(NUM_ELEMENTS);
    copy(vec.begin(), vec.end(), llist.begin());

    // *** Vector Performance ***

    // Resizing measurement
    auto resize_start = high_resolution_clock::now();
    vec.resize(NUM_ELEMENTS*2);
    vec[NUM_ELEMENTS] = NUM_ELEMENTS;
    auto resize_end = high_resolution_clock::now();

    // Access measurement
    auto access_start = high_resolution_clock::now();
    for (int value : vec) {
     if (value == NUM_ELEMENTS) {
          cout << "Value found" << endl;
          break; 
          }
     }
    auto access_end = high_resolution_clock::now();


    // *** Linked List Performance ***

    // Adding elements to reach 20 million (you can't resize a linked list directly)
    auto add_start = high_resolution_clock::now();
    for (int i = NUM_ELEMENTS; i < NUM_ELEMENTS; ++i) {
        llist.push_back(i); 
    }
    auto add_end = high_resolution_clock::now();

    // Access measurement
    auto resize_list_start = high_resolution_clock::now();
    llist.push_back(NUM_ELEMENTS);
    auto resize_list_end = high_resolution_clock::now();

    auto access_list_start = high_resolution_clock::now();
    auto it = llist.begin();
    advance(it, TARGET_INDEX/2);
    int value_list = *it;
    cout << value_list << endl;
    auto access_list_end = high_resolution_clock::now();

    // *** Output ***
    cout << "Vector:" << endl;
    cout << "  N+1 time: " 
         << duration_cast<milliseconds>(resize_end - resize_start).count()
         << " ms" << endl;
    cout << "  Access time: "
         << duration_cast<milliseconds>(access_end - access_start).count()
         << " ms" << endl;

    cout << "Linked List:" << endl;
    cout << "  N+1 time: "
         << duration_cast<milliseconds>(resize_list_end - resize_list_start).count()
         << " ms" << endl;
    cout << "  Access time: "
         << duration_cast<milliseconds>(access_list_end - access_list_start).count()
         << " ms" << endl;

    return 0;
}

// Results

// Value found
// 100000000
// Vector:
//   N+1 time: 108 ms
//   Access time: 37 ms
// Linked List:
//   N+1 time: 0 ms
//   Access time: 1038 ms


// V1 Results:

// Value found
// 100000000
// Vector:
//   Resize time: 148 ms
//   Access time: 39 ms
// Linked List:
//   Add elements time: 3689 ms
//   Access time: 1048 ms

