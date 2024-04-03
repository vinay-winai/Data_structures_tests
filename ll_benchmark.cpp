#include <iostream>
#include <list>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

const int LIST_SIZE = 100'000'000;

void benchmarkLookupByValue(const list<int>& lst) {
    auto it = lst.begin();
    advance(it, 0);
    int target1 = *it;
    advance(it, LIST_SIZE / 4);
    int target2 = *it;
    advance(it, LIST_SIZE / 4);
    int target3 = *it;
    advance(it, LIST_SIZE / 4);
    int target4 = *it;
    advance(it, LIST_SIZE / 4);
    int target5 = *it;

    auto start = chrono::high_resolution_clock::now();
    auto found1 = find(lst.begin(), lst.end(), target1);
    auto found2 = find(lst.begin(), lst.end(), target2);
    auto found3 = find(lst.begin(), lst.end(), target3);
    auto found4 = find(lst.begin(), lst.end(), target4);
    auto found5 = find(lst.begin(), lst.end(), target5);
    auto end = chrono::high_resolution_clock::now();

    cout << "Lookup By Value Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\nIn nanosecs: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << "ns\n";
}

void benchmarkInsert(list<int>& lst) {
    auto it = lst.begin();
    advance(it, 0);
    *it = 0;
    advance(it, LIST_SIZE / 4);
    *it = 0;
    advance(it, LIST_SIZE / 4);
    *it = 0;
    advance(it, LIST_SIZE / 4);
    *it = 0;
    advance(it, (LIST_SIZE / 4)-1);
    *it = 0;
    int valueToInsert = 1;

    auto start = chrono::high_resolution_clock::now();
    lst.insert(lst.begin(), valueToInsert);
    auto end = chrono::high_resolution_clock::now();
    cout << "Insert (Beginning) Time: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << "ns\n";

    start = chrono::high_resolution_clock::now();
    it = lst.begin();
    advance(it, LIST_SIZE / 4);
    lst.insert(find(it, lst.end(), 0), valueToInsert);
    end = chrono::high_resolution_clock::now();
    cout << "Insert (q1) Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    start = chrono::high_resolution_clock::now();
    it = lst.begin();
    advance(it, LIST_SIZE / 2);
    lst.insert(find(it, lst.end(), 0), valueToInsert);
    end = chrono::high_resolution_clock::now();
    cout << "Insert (Middle) Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    start = chrono::high_resolution_clock::now();
    it = lst.begin();
    advance(it, 3 * LIST_SIZE / 4);
    lst.insert(find(it, lst.end(), 0), valueToInsert);
    end = chrono::high_resolution_clock::now();
    cout << "Insert (q3) Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    start = chrono::high_resolution_clock::now();
    lst.insert(lst.end(), valueToInsert);
    end = chrono::high_resolution_clock::now();
    cout << "Insert (End) Time: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << "ns\n";
}

void benchmarkDelete(list<int>& lst) {
    auto start = chrono::high_resolution_clock::now();
    lst.pop_front();
    auto end = chrono::high_resolution_clock::now();
    cout << "Delete (Beginning) Time: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << "ns\n";

    start = chrono::high_resolution_clock::now();
    auto it = find(lst.begin(), lst.end(), 1);
    lst.erase(it);
    end = chrono::high_resolution_clock::now();
    cout << "Delete (q1) Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    start = chrono::high_resolution_clock::now();
    it = find(lst.begin(), lst.end(), 1);
    lst.erase(it);
    end = chrono::high_resolution_clock::now();
    cout << "Delete (Middle) Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    start = chrono::high_resolution_clock::now();
    it = find(lst.begin(), lst.end(), 1);
    lst.erase(it);
    end = chrono::high_resolution_clock::now();
    cout << "Delete (q3) Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    start = chrono::high_resolution_clock::now();
    lst.pop_back();
    end = chrono::high_resolution_clock::now();
    cout << "Delete (End) Time: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << "ns\n";
}

int main() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(2, INT_MAX);

    list<int> lst;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < LIST_SIZE; i++) {
        lst.push_back(distribution(generator));
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Pre-allocate Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    int run = 2;
    while (run > 0) {
        benchmarkLookupByValue(lst);
        benchmarkInsert(lst);
        benchmarkDelete(lst);
        run--;
    }   
    
    start = chrono::high_resolution_clock::now();
    int insertions = 100;
    int step = lst.size() / insertions;
    auto it = lst.begin();
    int count = 0; 
    while (it != lst.end()) {  
        if (count % step == 0) {
            *it = 0; 
        }
        ++count;
        ++it;
    }

     // Insert 1s after the 0s
     it = lst.begin();
     while (it != lst.end()) {
     if (*it == 0) {
          it = lst.insert(next(it), 1);
          it = next(it); // Move the iterator past the inserted element
     } else {
          it++;
     }
     }    
    end = chrono::high_resolution_clock::now();
    cout << "Heavy Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";
       
    start = chrono::high_resolution_clock::now();
    int deletions = 100;
    while (deletions > 0) {
          auto it = find(lst.begin(), lst.end(), 1);
          lst.erase(it);
          deletions--;
     }
    end = chrono::high_resolution_clock::now();
    cout << "Heavy Delete Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";
    
    start = chrono::high_resolution_clock::now();
    long long sum = 0;
    for (const auto& value : lst) {
        sum += value;
    }

    end = chrono::high_resolution_clock::now();
    cout << sum
         << "\nHeavy Lookup Time: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << "ms\n";

    return 0;
}


// Sequential 2 shot 100 mil
// Memory 3GB 
// CPU MAX~ 16% - used around 4 vCPUs
// Pre-allocate Time: 3812ms
// Lookup By Value Time: 2262ms
// In nanosecs: 2262663600ns
// Insert (Beginning) Time: 2600ns
// Insert (q1) Time: 260ms
// Insert (Middle) Time: 530ms
// Insert (q3) Time: 788ms
// Insert (End) Time: 600ns
// Delete (Beginning) Time: 800ns
// Delete (q1) Time: 237ms
// Delete (Middle) Time: 471ms
// Delete (q3) Time: 693ms
// Delete (End) Time: 1600ns
// Lookup By Value Time: 911ms
// In nanosecs: 911264000ns
// Insert (Beginning) Time: 2300ns
// Insert (q1) Time: 256ms
// Insert (Middle) Time: 540ms
// Insert (q3) Time: 826ms
// Insert (End) Time: 600ns
// Delete (Beginning) Time: 900ns
// Delete (q1) Time: 228ms
// Delete (Middle) Time: 453ms
// Delete (q3) Time: 738ms
// Delete (End) Time: 1900ns
// Heavy Time: 1988ms
// Heavy Delete Time: 45342ms
// 107375702171184704
// Heavy Lookup Time: 914ms

// Sequential 2 shot 10 mil
// Pre-allocate Time: 384ms
// Lookup By Value Time: 237ms
// In nanosecs: 237616700ns
// Insert (Beginning) Time: 2200ns
// Insert (q1) Time: 26ms
// Insert (Middle) Time: 56ms
// Insert (q3) Time: 78ms
// Insert (End) Time: 600ns
// Delete (Beginning) Time: 900ns
// Delete (q1) Time: 22ms
// Delete (Middle) Time: 46ms
// Delete (q3) Time: 67ms
// Delete (End) Time: 300ns
// Lookup By Value Time: 89ms
// In nanosecs: 89992900ns
// Insert (Beginning) Time: 2300ns
// Insert (q1) Time: 26ms
// Insert (Middle) Time: 55ms
// Insert (q3) Time: 79ms
// Insert (End) Time: 600ns
// Delete (Beginning) Time: 600ns
// Delete (q1) Time: 22ms
// Delete (Middle) Time: 47ms
// Delete (q3) Time: 69ms
// Delete (End) Time: 1900ns
// Heavy Time: 195ms
// Heavy Delete Time: 4493ms
// 10737198222065806
// Heavy Lookup Time: 93ms