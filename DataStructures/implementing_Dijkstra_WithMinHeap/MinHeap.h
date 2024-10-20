#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <climits>
using namespace std;

struct Node {
    char label;
    int cost;
};

class MinHeap {
private:
    Node* heap; // An array of nodes
    int capacity; // Maximum size of the heap
    int size; // Current size of the heap

public:
    MinHeap(int capacity = 10) : capacity(capacity), size(0) {
        heap = new Node[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    int findLabelIndex(char label){
        for (int i = 0 ;i < capacity; i++)
        {
            if(heap[i].label == label){
                return i;
            }
        }
        return -1;
    }

    void ensureCapacity() {
        if (size == capacity) {
            capacity *= 2; // Double the capacity
            Node* newHeap = new Node[capacity];
            for (int i = 0; i < size; i++) {
                newHeap[i] = heap[i];
            }
            delete[] heap;
            heap = newHeap;
        }
    }

    void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && heap[left].cost < heap[smallest].cost)
            smallest = left;
        if (right < size && heap[right].cost < heap[smallest].cost)
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(i);
    }

    Node extractHeap() {
    if (size < 1) {
        cout << "Heap underflow" << endl;
        return Node(); // Return a default-constructed node
    }
    Node min = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapify(0);
    // Decrease all labels by 1
    /*for(int i = 0; i < size; i++){
        heap[i].label -= 1;
    }*/
    return min;
    }

    void minHeapInsert(Node newNode) {
        ensureCapacity();
        size++;
        heap[size - 1] = newNode;
        heap[size - 1].label = newNode.label; 
        heapDecreaseKey(newNode.cost, newNode.label);
    }

    void heapDecreaseKey(int key, int index) {
        if (index >= size || index < 0) {
            //cout << "Error: Index out of bounds" << endl;
            return;
        }
        if (key > heap[index].cost) {
            //cout << "Error: New key is greater than the current key" << endl;
            return;
        }
        heap[index].cost = key;
        while (index > 0 && heap[(index - 1) / 2].cost > heap[index].cost) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    void printHeap() {
        cout << "Printing heap" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Index: " << i << ", Label: " << heap[i].label << ", Cost: " << heap[i].cost << endl;
        }
    }
};

#endif /* MINHEAP_H */