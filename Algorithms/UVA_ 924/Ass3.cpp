// GROUP:   2
// ID:      20227012
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Rodyna Amr Fathy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array {
    int n, sz;
    Value* arr;

    void Initialize() {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }
    void Destroy() {
        delete[] arr;
        sz = 0;
        n = 0;
    }
    void AddLast(Value v) {
        if (n == sz) {
            sz = sz * 2;
            Value* newArr = new Value[sz];
            for (int i = 0; i < n; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[n++] = v;
    }
    void RemoveLast() {
        if (n > 0) {
            n--;
        }
    }
    Value& operator[](int i) {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node {
    Array<int> adj;

    void Initialize() {
        adj.Initialize();
    }
    void Destroy() {
        adj.Destroy();
    }
};

struct Graph {
    int n;
    Node* nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].Initialize();
        }
    }
    void Destroy() {
        for (int i = 0; i < n; i++) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue {
    int front, rear, sz;
    Type* elems;

    void Initialize(int size) {
        sz = size;
        elems = new Type[sz];
        front = rear = -1; 
    }
    void Destroy() {
        delete[] elems;
    }
    bool isEmpty() {
        return front == -1;
    }
    bool isFull() {
        return (rear + 1) % sz == front;
    }
    void Add(Type t) {
        if (isFull()) {
            cout << "Queue is FULL. Cannot enqueue element." << endl;
            return;
        }
        if (front == -1)
            front = rear = 0;
        else
            rear = (rear + 1) % sz;
        elems[rear] = t;
    }
    Type Pop() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue element." << endl;
            exit(EXIT_FAILURE);
        }
        Type popped = elems[front];
        if (front == rear) {
            front = rear = -1;
        }
        else {
            front = (front + 1) % sz;
        }
        return popped;
    }
    Type Peek() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue element." << endl;
            exit(EXIT_FAILURE);
        }
        return elems[front];
    }
    int Num() {
        if (isEmpty()) {
            return 0;
        }
        return (rear >= front) ? rear - front + 1 : sz - front + rear + 1;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int E;
    cin >> E;

    Graph graph;
    graph.Initialize(E);

    for (int i = 0; i < E; i++) {
        int numberOfFriends;
        cin >> numberOfFriends;

        for (int j = 0; j < numberOfFriends; j++) {
            int friendIndex;
            cin >> friendIndex;
            graph.nodes[i].adj.AddLast(friendIndex);
        }
    }

    bool* visited = new bool[E];

    int T;
    cin >> T;
    while (T--) {
        // Reset visited array
        fill(visited, visited + E, false);
        
        int source;
        cin >> source;

        Queue<int> queue;
        queue.Initialize(E);
        queue.Add(source);
        visited[source] = true;

        int* levelCount = new int[E]; // Array to count nodes at each level
        memset(levelCount, 0, E * sizeof(int));

        int maxBoomSize = 0, firstBoomDay = 0;
        int currentLevel = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.Num(); // Get the number of nodes at the current level

            // Process all nodes in the current level
            for (int i = 0; i < levelSize; i++) {
                int parent = queue.Pop();
                Array<int>& adj = graph.nodes[parent].adj;

                // Enqueue all unvisited adjacent nodes
                for (int j = 0; j < adj.n; j++) {
                    int neighbor = adj[j];
                    if (!visited[neighbor]) {
                        queue.Add(neighbor);
                        visited[neighbor] = true;
                        levelCount[currentLevel + 1]++;
                    }
                }
            }

            // Check boom size for the next level
            if (levelCount[currentLevel + 1] > maxBoomSize) {
                maxBoomSize = levelCount[currentLevel + 1];
                firstBoomDay = currentLevel + 1;
            }

            currentLevel++;
        }

        // Output results
        if (maxBoomSize > 0) {
            cout << maxBoomSize << " " << firstBoomDay << endl;
        } else {
            cout << "0" << endl; 
        }

        delete[] levelCount;
        queue.Destroy();
    }

    delete[] visited;
    graph.Destroy();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////