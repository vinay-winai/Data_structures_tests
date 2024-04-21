#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

// Struct for a node in the linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to insert a value in the sorted linked list
void insert(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (!head || val < head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* curr = head;
    while (curr->next && curr->next->data < val) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

// Function to delete a value from the linked list
void deleteNode(Node*& head, int val) {
    if (!head) return;
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* curr = head;
    while (curr->next && curr->next->data != val) {
        curr = curr->next;
    }
    if (curr->next) {
        Node* temp = curr->next;
        curr->next = curr->next->next;
        delete temp;
    }
}

int main() {
    std::ifstream file("numbers.txt");
    if (!file) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return 1;
    }
    Node* head = nullptr;
    auto start = std::chrono::high_resolution_clock::now();
    int num;
    while (file >> num) {
        insert(head, num);
    }
    file.close();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    int count = 0;
    Node* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    std::cout << "Total time taken to insert " << count << " numbers: " << duration << " ms" << std::endl;

    std::ifstream deleteFile("delete.txt");
    if (!deleteFile) {
        std::cerr << "Failed to open delete file for reading." << std::endl;
        return 1;
    }
    start = std::chrono::high_resolution_clock::now();
    int deleteval;
    while (deleteFile >> deleteval) {
        deleteNode(head, deleteval);
    }
    deleteFile.close();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    count = 0;
    temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    std::cout << "Deleted, " << count << " numbers left. Time: " << duration << " ms" << std::endl;

    // Clean up the linked list
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
