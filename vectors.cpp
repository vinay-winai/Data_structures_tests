#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    vector<int> data;
    random_device rd;
    mt19937 gen(rd());

    // Insertion benchmark
    auto start_insert = high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        int value = gen();
        auto it = lower_bound(data.begin(), data.end(), value); // Find insertion point
        data.insert(it, value); 
    }
    auto end_insert = high_resolution_clock::now();

    // Deletion benchmark
    auto start_delete = high_resolution_clock::now();
    while (!data.empty()) {
        int index = gen() % data.size();
        data.erase(data.begin() + index); 
    }
    auto end_delete = high_resolution_clock::now();

    // Print timings
    auto insert_time = duration_cast<milliseconds>(end_insert - start_insert);
    auto delete_time = duration_cast<milliseconds>(end_delete - start_delete);
    
    cout << "Insertion Time: " << insert_time.count() << "ms\n";
    cout << "Deletion Time: " << delete_time.count() << "ms\n";

    return 0;
}