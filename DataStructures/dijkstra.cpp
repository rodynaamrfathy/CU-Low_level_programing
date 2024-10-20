#include <iostream>
#include <climits>
#include "MinHeap.h"
using namespace std;

class AdjacencyMatrix {
private:
    int **matrix;
    int numVertices;

public:

    int dijkstra(char startVertex, char* prev, int *distances);

    // Constructor to initialize the matrix with the given number of vertices
    AdjacencyMatrix(int vertices) : numVertices(vertices) {
        // Allocate memory for the matrix
        matrix = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            matrix[i] = new int[numVertices];
            // Initialize all elements to 0
            for (int j = 0; j < numVertices; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    // Destructor to free dynamically allocated memory
    ~AdjacencyMatrix() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Function to add an edge between two vertices
    void addEdge(int source, int destination, int weight) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            // Add the edge with the given weight
            matrix[source][destination] = weight;
            // For undirected graphs, you can uncomment the line below
            // matrix[destination][source] = weight;
        } else {
            cout << "Invalid vertices!" << endl;
        }
    }

    // Function to print the adjacency matrix
    void printMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};



int AdjacencyMatrix :: dijkstra(char source, char* prev, int *distances){
    // Create a priority queue for storing the nodes as a pair {cost,node}


}

int main() {
    // Create an adjacency matrix with 5 vertices
    int size = 5;
    AdjacencyMatrix graph(size);

    // Add some edges to the graph
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 1);s

    // Print the adjacency matrix
    graph.printMatrix();


    int *distances = new int[size];
    for (int i = 0; i < size; i++){
        distances[i] = numeric_limits<int>::max();
    }

    return 0;
}











/*int AdjacencyMatrix :: dijkstra(char source, char* prev, int *distances)
{
    bool visited[numVertices]; // Mark all vertices as not visited
    for (int i = 0; i < numVertices; ++i) {
        visited[i] = false;
    }
    distances[source] = 0; // Distance from source to itself is 0

    for (int i = 0; i < numVertices - 1; ++i) {
        // Find the vertex with the minimum distance from the set of vertices not yet processed
        int minDistance = numeric_limits<int>::max(), minIndex;
            for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && distances[j] <= minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }

        // Mark the selected vertex as visited
        visited[minIndex] = true;

        // Update distance values of adjacent vertices of the selected vertex
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && matrix[minIndex][j] && distances[minIndex] != numeric_limits<int>::max() && 
                distances[minIndex] + matrix[minIndex][j] < distances[j]) {
                distances[j] = distances[minIndex] + matrix[minIndex][j];
                prev[j] = minIndex;
            }
        }
    }
    return 1;
}*/
