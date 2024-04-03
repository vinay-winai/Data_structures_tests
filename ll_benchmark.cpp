#include <iostream>
#include <list> // Include for linked list 
#include <random>
#include <chrono>
#include <algorithm> 

using namespace std;

const int ARRAY_SIZE = 100'000'000;

void benchmarkLookupByValue(const list<int>& list) {
    // Note: Linear search is typical with linked lists
    auto start = chrono::high_resolution_clock::now();
    
    int target1 = *list.begin(); 
    int target2 = *(next(list.begin(), ARRAY_SIZE / 4));  
    int target3 = *(next(list.begin(), ARRAY_SIZE / 2));  
    int target4 = *(next(list.begin(), 3 * ARRAY_SIZE / 4));  
    int target5 = *(prev(list.end()));

    find(list.begin(), list.end(), target1); 
    find(list.begin(), list.end(), target2); 
    find(list.begin(), list.end(), target3); 
    find(list.begin(), list.end(), target4); 
    find(list.begin(), list.end(), target5); 
    auto end = chrono::high_resolution_clock::now();

    cout << "Lookup By Value Time (Linked List): " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";
}

void benchmarkInsert(list<int> list) { 
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, INT_MAX);
    int valueToInsert = distribution(generator);  

    // Insert at beginning
    auto start = chrono::high_resolution_clock::now();
    list.push_front(valueToInsert); 
    auto end = chrono::high_resolution_clock::now();
    cout << "Insert (Beginning) Time (Linked List): " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
         << "ns\n";

    // Insert at middle 
    start = chrono::high_resolution_clock::now();
    auto middle = next(list.begin(), ARRAY_SIZE / 2);
    list.insert(middle, valueToInsert); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (Middle) Time (Linked List): " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Insert at end
    start = chrono::high_resolution_clock::now();
    list.push_back(valueToInsert); 
    end = chrono::high_resolution_clock::now();
    cout << "Insert (End) Time (Linked List): " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
         << "ns\n";
}

void benchmarkDelete(list<int> list) { 
    // Delete at beginning
    auto start = chrono::high_resolution_clock::now();
    list.pop_front();
    auto end = chrono::high_resolution_clock::now();
    cout << "Delete (Beginning) Time (Linked List): " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
         << "ns\n";

    // Delete at middle
    start = chrono::high_resolution_clock::now();
    auto middle = next(list.begin(), ARRAY_SIZE / 2);
    list.erase(middle); 
    end = chrono::high_resolution_clock::now();
    cout << "Delete (Middle) Time (Linked List): " 
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
         << "ms\n";

    // Delete at end
    start = chrono::high_resolution_clock::now();
    list.pop_back(); 
    end = chrono::high_resolution_clock::now();
    cout << "Delete (End) Time (Linked List): " 
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() 
         << "ns\n";
}

int main() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, INT_MAX);

    list<int> list; 

    // Fill the linked list with random integers
    for (int i = 0; i < ARRAY_SIZE; i++) {
        list.push_back(distribution(generator)); 
    }

    int run = 1;
    while (run > 0){
        benchmarkLookupByValue(list);
        benchmarkInsert(list); 
        benchmarkDelete(list);
        run--;
    }

    return 0;
}


// 3 to 6 GB
// four vCPUS 16 - 20%
