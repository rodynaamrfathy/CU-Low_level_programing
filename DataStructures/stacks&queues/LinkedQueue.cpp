#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class IntSLLNode {
public:
    int info;
    IntSLLNode *next;
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(int el, IntSLLNode *ptr = 0) {
        info = el; next = ptr;
    }
};

class IntSLLQueue {
private:
    IntSLLNode *head;  // Pointer to the front of the queue
    IntSLLNode *tail;  // Pointer to the rear of the queue
    int size;          // Number of elements in the queue
public:
    IntSLLQueue() : head(nullptr), tail(nullptr), size(0) {}

    void enqueue(int); // Function to add an element to the queue
    int dequeue();     // Function to remove and return the front element
    int front();       // Function to return the front element
    bool isEmpty();    // Function to check if the queue is empty
};

void IntSLLQueue::enqueue(int info) {
    IntSLLNode* newNode = new IntSLLNode(info); // Create a new node
    if (tail != nullptr) {
        tail->next = newNode; // Link the new node after the tail
    }
    tail = newNode; // Update the tail to the new node
    if (head == nullptr) {
        head = newNode; // If the queue was empty, set head to the new node
    }
    size++; // Increment the size of the queue
}

int IntSLLQueue::dequeue() {
    if (head == nullptr) {
        return -1; // If the queue is empty, return -1
    }
    IntSLLNode* delNode = head; // Node to be deleted
    int deletedInfo = delNode->info; // Store the data to be returned
    head = head->next; // Move head to the next node
    if (head == nullptr) {
        tail = nullptr; // If the queue is now empty, set tail to nullptr
    }
    delete delNode; // Free the memory of the deleted node
    size--; // Decrement the size of the queue
    return deletedInfo; // Return the deleted data
}

int IntSLLQueue::front() {
    if (head == nullptr) {
        return -1; // If the queue is empty, return -1
    }
    return head->info; // Return the data of the head node
}

bool IntSLLQueue::isEmpty() {
    return (size == 0); // Return true if size is 0
}

