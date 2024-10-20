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
    void dijkstra(int *prev, int *costs, char startVertex);
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

inline void WeightedGraph::dijkstra(int *prev, int *costs, char startVertex = -1)
{
    // priority queue 
    MinHeap pq(nVertices);

    if(startVertex == -1)
    {
        startVertex = this->startNode;
    }

    costs = new int[nVertices];
    prev = new int[nVertices];

    for (int i = 0; i < nVertices; ++i)
    {
        costs[i] = INT_MAX;
        prev[i] = -1;
    }

    int startIndex = labelToInt(startVertex);
    if (startIndex == -1)
    {
        cout << "Start vertex not found." << endl;
        return;
    }
    costs[startIndex] = 0;

    // ha7ot el nodes fy el priority queue el b3mlo visit bytl3
    // w el b3mlo relax brdo btl3o lhd ma el queue tfda keda na finish
    for (int i = 0; i < nVertices; i++)
    {
        Node newNode;
        newNode.label = labels[i];
        newNode.cost = costs[i];
        pq.minHeapInsert(newNode);
    }

    while (!pq.isEmpty())
    {
        //cout<<"heap BEFOREEE extraction";
        //pq.printHeap();
        //cout<<endl;
        Node minNode = pq.extractHeap();
        int u = labelToInt(minNode.label);
        //cout<< "the selected min value form heap"<< u <<endl;
        //cout<<"heap after extraction";
        //pq.printHeap();
        //cout<<endl;

        for (int v = 0; v < nVertices; v++)
        {
            if (g[u][v] != 0)
            {
                // Relaxation
                if (costs[u] != INT_MAX && costs[u] + g[u][v] < costs[v])
                {

                    //cout<<"costs[v]  "<< v << " / " << costs[v]  <<endl;
                    //cout<<"costs[u]  "<< u << " / "<< costs[u] <<endl;
                    //cout<<"g[u][v]  "<< g[u][v]<<endl;
                    costs[v] = costs[u] + g[u][v];
                    prev[v] = u;
                    //cout<<"AFTER UPDATE : costs[v]  "<< v << " / " << costs[v]  <<endl;
                    // Update the priority of the vertex in the priority queue
                    int nextLabel = pq.findLabelIndex(labels[v]);
                    pq.heapDecreaseKey(costs[v], nextLabel);
                    //cout<<"heap AFTER UPDATE";
                    //pq.printHeap();
                    //cout<<endl;
                }

            }
        }
    }

    // print
    // Create arrays to hold label, cost, and prev information
    char* sortedLabels = new char[nVertices];
    int* sortedCosts = new int[nVertices];
    int* sortedprev = new int[nVertices];

    // Populate the arrays with label, cost, and prev information
    for (int i = 0; i < nVertices; ++i)
    {
        sortedLabels[i] = labels[i];
        sortedCosts[i] = costs[i];
        sortedprev[i] = prev[i];
    }

    // Sort the labels array alphabetically along with corresponding costs and prevs
    for (int i = 0; i < nVertices - 1; ++i)
    {
        for (int j = i + 1; j < nVertices; ++j)
        {
            if (sortedLabels[i] > sortedLabels[j])
            {
                swap(sortedLabels[i], sortedLabels[j]);
                swap(sortedCosts[i], sortedCosts[j]);
                swap(sortedprev[i], sortedprev[j]);
            }
        }
    }

    // Print the sorted results
    for (int i = 0; i < nVertices; ++i)
    {
        cout << "Node: " << sortedLabels[i] << " Cost: " << sortedCosts[i] << " Prev: ";
        if (sortedprev[i] == -1)
        {
            cout << sortedLabels[i];
        }
        else
        {
            int predIndex = labelToInt(sortedLabels[i]);
            cout << labels[sortedprev[i]];
        }
        cout << endl;
    }

    // Deallocate memory for arrays
    delete[] sortedLabels;
    delete[] sortedCosts;
    delete[] sortedprev;
}


#endif /* WEIGHTEDGRAPH_H */
