#include <iostream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    const int NUM_ELEMENTS_1 = 100'000'000;
    const int NUM_ELEMENTS_2 = 200'000'000;
    const int TARGET_INDEX = NUM_ELEMENTS_1;

    // Vector setup
    vector<int> vec(NUM_ELEMENTS_1);
    for (int i = 0; i < NUM_ELEMENTS_1; ++i) {
        vec[i] = i; // Fill with sequential values
    }

    // Linked list setup
    list<int> llist(NUM_ELEMENTS_1);
    copy(vec.begin(), vec.end(), llist.begin());

    // *** Vector Performance ***

    // Resizing measurement
    auto resize_start = high_resolution_clock::now();
    vec.resize(NUM_ELEMENTS_2);
    for (int i = NUM_ELEMENTS_1; i < NUM_ELEMENTS_2; ++i) {
        vec[i-1] = i; // Fill with sequential values
    }
    auto resize_end = high_resolution_clock::now();

    // Access measurement
    auto access_start = high_resolution_clock::now();
    for (int value : vec) {
     if (value == NUM_ELEMENTS_1) {
          cout << "Value found" << endl;
          break; 
          }
     }
    auto access_end = high_resolution_clock::now();


    // *** Linked List Performance ***

    // Adding elements to reach 20 million (you can't resize a linked list directly)
    auto add_start = high_resolution_clock::now();
    for (int i = NUM_ELEMENTS_1; i < NUM_ELEMENTS_2; ++i) {
        llist.push_back(i); 
    }
    auto add_end = high_resolution_clock::now();

    // Access measurement
    auto access_list_start = high_resolution_clock::now();
    auto it = llist.begin();
    advance(it, TARGET_INDEX);
    int value_list = *it;
    cout << value_list << endl;
    auto access_list_end = high_resolution_clock::now();

    // *** Output ***
    cout << "Vector:" << endl;
    cout << "  Resize time: " 
         << duration_cast<milliseconds>(resize_end - resize_start).count()
         << " ms" << endl;
    cout << "  Access time: "
         << duration_cast<milliseconds>(access_end - access_start).count()
         << " ms" << endl;

    cout << "Linked List:" << endl;
    cout << "  Add elements time: "
         << duration_cast<milliseconds>(add_end - add_start).count()
         << " ms" << endl;
    cout << "  Access time: "
         << duration_cast<milliseconds>(access_list_end - access_list_start).count()
         << " ms" << endl;

    return 0;
}