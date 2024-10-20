#include <iostream>
using namespace std;

template<class T>
class CircularQueue {
private:
    int front, rear, capacity;
    T *queue;
public:
    CircularQueue(int initialSize) : front(-1), rear(-1), capacity(initialSize) {
        queue = new T[capacity];
    }
    bool isEmpty();
    bool isFull();
    void enqueue(T element);
    T dequeue();
    T peekFront();
    ~CircularQueue(){
        delete[] queue;
    }
};

template<class T>
bool CircularQueue<T>::isEmpty() {
    return front == -1;
}

template<class T>
bool CircularQueue<T>::isFull() {
    return (rear + 1) % capacity == front;
}

template<class T>
void CircularQueue<T>::enqueue(T element) {
    if (isFull()){
        cout << "Queue is FULL. Cannot enqueue element." << endl;
        return ;
    }
    if (front == -1)
        front = rear = 0; // If the Queue was empty, set the front also to be zero
    else
        rear = (rear + 1) % capacity;
    queue[rear] = element;  
}

template<class T>
T CircularQueue<T>::dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue element." << endl;
        return T();
    }
    T temp = queue[front];
    //incase it is the last element
    if(front == rear){
        front = rear = -1;
    }
    else{
        front = (front + 1) % capacity;
    }
    return temp;
}

template<class T>
T CircularQueue<T>::peekFront() {
    if (isEmpty()) {
        cout << "Queue is empty. Cannot dequeue element." << endl;
        return T();
    }
    T temp = queue[front];
    return temp;
}

int main() {
    // Create a circular queue of integers with initial size 3
    CircularQueue<int> myQueue(3);

    // Enqueue some elements
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);
    cout << "Front element: " << myQueue.peekFront() << endl; // Front element should be 10

    // Try to enqueue when the queue is full
    myQueue.enqueue(40); // Should display "Queue is FULL. Cannot enqueue element."

    // Dequeue elements
    cout << "Dequeued element: " << myQueue.dequeue() << endl; // Dequeued element should be 10
    cout << "Dequeued element: " << myQueue.dequeue() << endl; // Dequeued element should be 20
    cout << "Front element: " << myQueue.peekFront() << endl; // Front element should be 30

    // Try to dequeue when the queue is empty
    myQueue.dequeue(); // Should display "Queue is empty. Cannot dequeue element."

    // Enqueue more elements
    myQueue.enqueue(40);
    myQueue.enqueue(50);
    cout << "Front element: " << myQueue.peekFront() << endl; // Front element should be 30

    // Dequeue all elements
    cout << "Dequeued element: " << myQueue.dequeue() << endl; // Dequeued element should be 30
    cout << "Dequeued element: " << myQueue.dequeue() << endl; // Dequeued element should be 40
    cout << "Dequeued element: " << myQueue.dequeue() << endl; // Dequeued element should be 50

    // Try to peek when the queue is empty
    myQueue.peekFront(); // Should display "Queue is empty. Cannot peek front element."

    return 0;
}

