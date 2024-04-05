#include <iostream>
#include <list>
#include <chrono>

std::list<int> createLinkedList(int size) {
    std::list<int> list;
    for (int i = 1; i <= size; i++) {
        list.push_back(i);
    }
    return list;
}

long long calculateSum(const std::list<int>& list) {
    long long sum = 0;
    for (int num : list) {
        sum += num;
    }
    return sum;
}

int main() {
    std::list<int> list = createLinkedList(10'000'000);

    auto startTime = std::chrono::high_resolution_clock::now();
    long long sum = calculateSum(list);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Sum of all elements in the linked list (iteration 1): " << sum << std::endl;
    std::cout << "Time taken for the first iteration: " << duration << " ms" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++) {
        sum = calculateSum(list);
    }
    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Time taken for 100 iterations: " << duration << " ms" << std::endl;

    return 0;
}


// Sum of all elements in the linked list (iteration 1): 50000005000000
// Time taken for the first iteration: 91 ms
// Time taken for 100 iterations: 10587 ms