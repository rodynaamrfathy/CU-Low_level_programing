#include <iostream>
using namespace std;

template<class T>
class IntSLLNode {
public:
    T info;
    IntSLLNode<T> *next;
    IntSLLNode() {
        next = nullptr;
    }
    IntSLLNode(T el, IntSLLNode<T> *ptr = nullptr) {
        info = el; 
        next = ptr;
    }
};

template<class T>
class LinkedQueue {
private:
    IntSLLNode<T> *front, *rear;
    int size;
    int capacity;
public:
    LinkedQueue(int initialSize) : front(nullptr), rear(nullptr), size(0), capacity(initialSize) {}
    bool isEmpty();
    bool isFull();
    void enqueue(T element);
    T dequeue();
    T peekFront();
    ~LinkedQueue(){
        while (!isEmpty())
            dequeue();
    }
};

template<class T>
bool LinkedQueue<T>::isEmpty() {
    return size == 0;
}

template<class T>
bool LinkedQueue<T>::isFull() {
    return size == capacity;
}

template<class T>
void LinkedQueue<T>::enqueue(T element) {
    if (isFull()) {
        cout << "Queue is full.\n";
        return;
    }
    IntSLLNode<T> *newNode = new IntSLLNode<T>(element);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    rear->next = front; // Make the queue circular
    size++;
}

template<class T>
T LinkedQueue<T>::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return T(); // Default value for T, assuming T is a class with a default constructor
    }
    IntSLLNode<T> *del = front;
    T deletedInfo = del->info;
    if (front == rear) {
        front = rear = nullptr;
    } else {
        front = front->next;
        rear->next = front; // Adjust rear pointer to maintain circularity
    }
    delete del;
    size--;
    return deletedInfo;
}

template<class T>
T LinkedQueue<T>::peekFront() {
    if (isEmpty()) {
        cout << "Queue is empty.\n";
        return T(); // Default value for T
    }
    return front->info;
}

int main() {
    // Creating a linked queue of capacity 5
    LinkedQueue<int> queue(5);

    // Testing isEmpty when queue is empty
    cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;

    // Testing enqueue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);

    // Testing isFull
    cout << "Is queue full? " << (queue.isFull() ? "Yes" : "No") << endl;

    // Testing peekFront
    cout << "Front element: " << queue.peekFront() << endl;

    // Testing dequeue
    cout << "Dequeued: " << queue.dequeue() << endl;
    cout << "Front element after dequeue: " << queue.peekFront() << endl;

    // Testing enqueue when queue is full
    queue.enqueue(60);

    // Testing dequeue when queue is empty
    while (!queue.isEmpty()) {
        cout << "Dequeued: " << queue.dequeue() << endl;
    }
    cout << "Front element after all dequeues: " << queue.peekFront() << endl;

    // Testing dequeue when queue is already empty
    cout << "Dequeued: " << queue.dequeue() << endl;

    return 0;
}
