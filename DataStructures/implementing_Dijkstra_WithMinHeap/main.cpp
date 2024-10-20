#include "WeightedGraph.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int main() {
    WeightedGraph graph;
    ifstream readGraph("graph.txt");
    if (!readGraph) {
        cout << "File not found" << endl;
        return 1;
    }

    graph.loadGraphFromFile(readGraph);

    graph.printAdjacencyMatrix();

    cout <<"number or vertices :";
    cout<< graph.getNVertices()<<endl;

    int *prev, *costs;

    graph.dijkstra(prev, costs, 'g');

    cout<< graph.getWeight('g', 'a') <<endl;
    cout<< graph.getWeight('a', 'b') <<endl;

    int* neighbors = graph.returnNeighbors(graph.labelToInt('g'));
    int numNeighbors = graph.numNeighbors(graph.labelToInt('g'));

    cout<< "Number of Neighbors 'g' : "<< numNeighbors<<endl;
    if (numNeighbors > 0) {
        cout << "Neighbors of vertex 'g':" << endl;
        for (int i = 0; i < numNeighbors; ++i) {
            cout << graph.getLabelByIndex(neighbors[i]) << " ";
        }
        cout << endl;
    } else {
        cout << "Vertex 'g' has no neighbors or is invalid." << endl;
    }

    delete[] neighbors;

    return 0;
}