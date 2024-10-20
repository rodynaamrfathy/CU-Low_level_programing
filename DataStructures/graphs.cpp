#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int SIZE = 3;
string* linetoarray(string line) {
    string* array = new string[SIZE]; // Fixed size, change as needed
    int k = 0;
    string element;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != '\t' && line[i] != '=' && line[i] != ' ' && line[i] != ';') {
            element += line[i];
        } else if (!element.empty()) {
            array[k] = element;
            k++;
            element.clear();
        }
    }
    if (!element.empty() && k < SIZE) {
        array[k] = element;
    }
    return array;
}


class WeightedGraph
{
    int** g;
    int nVertices;
    char* labels;
    char startNode;

public:
    // Function to allocate memory for the graph
    void allocateMemory(int vertices);
    int labelToInt(char label);
    void addLabel(char label);
    int getNVertices();
    int getWeight(char label1, char label2);
    int* returnNeighbors(int v);
    int numNeighbors(int v);
    void loadGraphFromFile(ifstream& readGraph);
    char getLabelByIndex(int index) const {
        if (index >= 0 && index < nVertices)
            return labels[index];
        else
            return '\0'; // Return null character for invalid index
    }
    void printAdjacencyMatrix() {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < nVertices; ++i) {
        for (int j = 0; j < nVertices; ++j) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    }
};

inline void WeightedGraph::allocateMemory(int vertices)
{
    g = new int*[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        g[i] = new int[vertices];
        // Initialize the matrix elements to zero
        for (int j = 0; j < vertices; ++j)
        {
            g[i][j] = 0;
        }
    }
    nVertices = vertices;
    // allocate memory for labels
    labels = new char[nVertices];
    // initialize the label array to null
    for (int i = 0; i < nVertices; i++)
    {
        labels[i] = '\0';
    }
}

inline int WeightedGraph::labelToInt(char label)
{
    for (int i = 0; i < nVertices; i++)
    {
        if (labels[i] == label)
            return i;
    }
    cout << "Label not found" << endl << "Please enter a valid label." << endl;
    return -1;
}

inline void WeightedGraph::addLabel(char label)
{
    bool exists = false;
    for (int i = 0; i < nVertices; i++)
    {
        if (labels[i] == label)
        {
            exists = true;
            break;
        }
    }
    if (!exists)
    {
        for (int i = 0; i < nVertices; i++)
        {
            if (labels[i] == '\0')
            {
                labels[i] = label;
                break;
            }
        }
    }
}

inline int WeightedGraph::getNVertices()
{
    return nVertices;
}

inline int WeightedGraph::getWeight(char label1, char label2)
{
    // returns weight of the edge connecting the given vertices
    int vertex1, vertex2;
    vertex1 = labelToInt(label1);
    vertex2 = labelToInt(label2);
    return g[vertex1][vertex2];
}

inline int* WeightedGraph::returnNeighbors(int v)
{
    // returns the indices of the neighbors of the vertex v as an int array
    int numberOfNeighbors = numNeighbors(v);
    
    if (numberOfNeighbors == -1) {
        cout << "Invalid vertex" << endl;
        return new int[0];
    }

    int* neighbors = new int[numberOfNeighbors];
    int j = 0;

    if (v >= 0 && v < nVertices)
    {
        for (int i = 0; i < nVertices; i++)
        {
            if (g[v][i] != 0)
                neighbors[j++] = i;
        }
        return neighbors;
    }

    cout << "Invalid node" << endl;
    return new int[0]; 
}


inline int WeightedGraph::numNeighbors(int v)
{
    // returns the number of neighbors of the vertex v
    if (v >= 0 && v < nVertices)
    {
        int count = 0;
        for (int i = 0; i < nVertices; i++)
        {
            if (g[v][i] != 0)
                count++;
        }
        return count;
    }
    cout << "Invalid vertex" << endl;
    return -1;
}

inline void WeightedGraph::loadGraphFromFile(ifstream& readGraph)
{
    // allocates the adjacency matrix & initializes edge weights from the specified file
    string line;
    string* arrayOfGraphData;

    getline(readGraph, line);
    allocateMemory(stoi(line));
    getline(readGraph, line); // here this line contains number of edges
    // line = edges hn3ml beha eh?
    while (getline(readGraph, line))
    {
        arrayOfGraphData = linetoarray(line);
        if (arrayOfGraphData[0] == "start" || arrayOfGraphData[0] == "Start")
        {
            startNode = arrayOfGraphData[1][0];
            continue; // msh arfa tb2a break wala eh
        }
        char vertex1 = arrayOfGraphData[0][0];
        char vertex2 = arrayOfGraphData[1][0];
        addLabel(vertex1);
        addLabel(vertex2);
        int weight = stoi(arrayOfGraphData[2]);
        int index1 = labelToInt(vertex1);
        int index2 = labelToInt(vertex2);
        g[index1][index2] = weight;
    }

    
}

bool connected() {
    // Checks if the graph is connected by looking for consecutive edges in the adjacency matrix
    
    // Loop through all vertices except the last one
    for (int i = 0; i < nVertices - 1; ++i) {
        // If there is no edge between vertex i and vertex i+1, the graph is not connected
        if (adjacencyMatrix[i][i + 1] == 0) {
            return false;
        }
    }
    // If all consecutive vertices are connected, return true
    return true;
}

// Depth-First Search (DFS) using a stack
bool WeightedGraph::DFS(int start) {
    if (start < 0 || start >= nVertices) {
        cout << "Invalid start vertex" << endl;
        return false;
    }

    vector<bool> visited(nVertices, false);
    stack<int> stack;

    stack.push(start);

    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();

        if (!visited[v]) {
            visited[v] = true;

            int* neighbors = returnNeighbors(v);
            int numNeighbors = numNeighbors(v);

            for (int i = 0; i < numNeighbors; i++) {
                int neighbor = neighbors[i];
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                }
            }

            delete[] neighbors;
        }
    }

    for (bool isVisited : visited) {
        if (!isVisited) {
            return false; // If any vertex is not visited, the graph is not connected
        }
    }

    return true; // All vertices were visited, the graph is connected
}

#endif /* WEIGHTEDGRAPH_H */
