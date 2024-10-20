#include "BinaryTree.h"
#include <iostream>
using namespace std;


class MaxHeap : public Heap {
public:

    // Heapify a subtree rooted with node i
    void heapify(int i) override {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < arraySize && array[left]->data > array[largest]->data)
            largest = left;

        if (right < arraySize && array[right]->data > array[largest]->data)
            largest = right;

        if (largest != i) {
            swap(array[i], array[largest]);
            heapify(largest);
        }
    }

    // Build the heap
    void buildHeap() override {
        for (int i = arraySize / 2 - 1; i >= 0; i--)
            heapify(i);
    }

    // Heap sort
    void heapSort() override {
        buildHeap();
        for (int i = arraySize - 1; i > 0; i--) {
            swap(array[0], array[i]);
            heapSize--;
            heapify(0);
        }
    }
};

class MinHeap : public Heap {
public:

    // Heapify a subtree rooted with node i
    void heapify(int i) override {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < arraySize && array[left]->data < array[smallest]->data)
            smallest = left;

        if (right < arraySize && array[right]->data < array[smallest]->data)
            smallest = right;

        if (smallest != i) {
            swap(array[i], array[smallest]);
            heapify(smallest);
        }
    }

    // Build the heap
    void buildHeap() override {
        for (int i = arraySize / 2 - 1; i >= 0; i--)
            heapify(i);
    }

    // Heap sort
    void heapSort() override {
        buildHeap();
        for (int i = arraySize - 1; i > 0; i--) {
            swap(array[0], array[i]);
            heapSize--;
            heapify(0);
        }
    }
};


class MaxPriorityQueue : public MaxHeap{

    // Extracts the maximum element from the heap
    BinaryTreeNode* heapExtractMax() {
        if (heapSize < 1) {
            cout << "Heap underflow" << endl;
            return nullptr;
        }
        BinaryTreeNode* max = array[0];
        array[0] = array[heapSize - 1];
        heapSize--;
        heapify(0);
        return max;
        // function Runtime is O(log(n))
    }

    void heapIncreaseKey(int key, int index) {
        // Check if the index is within the bounds of the array
        if (index >= arraySize || index < 0) {
            cout << "Error: Index out of bounds" << endl;
            return;
        }

        // Check if the new key is smaller than the current key
        if (key < array[index]->n) {
            cout << "Error: New key is smaller than the current key" << endl;
            return;
        }

        // Update the key
        array[index]->n = key;

        // Heapify up
        while (index > 0 && array[index / 2]->n < array[index]->n) {
            swap(array[index], array[index / 2]);
            index = index / 2;
        }
        //runtime O(log(n))
    }

    void maxHeapInsert(int key) {
        // Increase the heap size by one
        heapSize++;

        // Create a new BinaryTreeNode with negative infinity as its value
        BinaryTreeNode* newNode = new BinaryTreeNode(INT_MIN);

        // Add the new node to the end of the array
        array[heapSize - 1] = newNode;

        // Call heapIncreaseKey to set the correct key for the new node
        heapIncreaseKey(key, heapSize - 1);
    }

};