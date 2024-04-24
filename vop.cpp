#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <memory>

int main() {
  std::ifstream file("numbers.txt");
  if (!file) {
    std::cerr << "Failed to open file for reading." << std::endl;
    return 1;
  }

  // Insertion phase with vector of pointers
  std::vector<int*> numbers;
  auto start = std::chrono::high_resolution_clock::now();

  int num;
  while (file >> num) {
    // Find insertion position (similar to previous code)
    auto it = numbers.begin();
    while (it != numbers.end() && *(*it) < num) {
      ++it;
    }

    // Insert at the found position (need to adjust pointer manipulation)
    numbers.insert(it, new int(num));
  }
  file.close();

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Total time taken to insert " << numbers.size() << " numbers (using vector of pointers): " << duration << " ms" << std::endl;

  // Deletion phase with vector of pointers
  std::ifstream deleteFile("delete.txt");
  if (!deleteFile) {
    std::cerr << "Failed to open delete file for reading." << std::endl;
    return 1;
  }

  start = std::chrono::high_resolution_clock::now();
  int deleteval;
  while (deleteFile >> deleteval) {
    auto it = std::find_if(numbers.begin(), numbers.end(), [&deleteval](int* ptr) { return *ptr == deleteval; });
    if (it != numbers.end()) {
      // Delete the dynamically allocated memory
      delete *it;
      // Erase the pointer from the vector
      numbers.erase(it);
    }
  }
  deleteFile.close();

  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Deleted, " << numbers.size() << " numbers left (using vector of pointers). Time: " << duration << " ms" << std::endl;

  return 0;
}
