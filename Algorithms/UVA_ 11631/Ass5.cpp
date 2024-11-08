// GROUP:   2
// ID:      20227012
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Rodyna Amr Fathy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * struct DisjointSets - Data structure for union-find operations.
 * @n: Number of elements (sets).
 * @parent: Array that holds the parent of each element.
 * @num_nodes: Array that holds the number of elements in each set.
 *
 * Description: This structure implements the Disjoint Set data structure, 
 * also known as Union-Find. It supports operations like union and find 
 * with path compression to optimize the performance.
 */
struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    /**
     * Initialize - Initializes the disjoint sets.
     * @_n: Number of elements in the sets.
     *
     * Description: Each element starts in its own set, 
     * with itself as its parent.
     */
    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];

        // Singleton sets: each element is its own parent initially.
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            num_nodes[i] = 1; // Each set starts with one element.
        }
    }

    /**
     * Destroy - Frees memory used by the DisjointSets structure.
     */
    void Destroy()
    {
        delete[] parent;
        delete[] num_nodes;
    }

    /**
     * Find - Finds the representative (parent) of the set containing 'i'.
     * @i: The element to find.
     *
     * Return: The parent (representative) of the set containing element 'i'.
     *
     * Description: Uses path compression to speed up future queries.
     */
    int Find(int i)
    {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = Find(parent[i]); // Path compression
    }

    /**
     * Union - Merges two sets containing elements 'i' and 'j'.
     * @i: First element.
     * @j: Second element.
     *
     * Return: true if the sets were successfully merged, false if they were already in the same set.
     */
    bool Union(int i, int j)
    {
        int root_i = Find(i);
        int root_j = Find(j);

        // If they are already in the same set, return false.
        if (root_i == root_j) {
            return false;
        }

        // Merge smaller set into larger set.
        if (num_nodes[root_i] < num_nodes[root_j]) {
            parent[root_i] = root_j;
            num_nodes[root_j] += num_nodes[root_i];
        }
        else {
            parent[root_j] = root_i;
            num_nodes[root_i] += num_nodes[root_j];
        }

        return true;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Merge - Merges two sorted halves of an array.
 * @a: Pointer to the array.
 * @n: Total number of elements in the array.
 * @IsBefore: Comparator function that returns true if the first element should come before the second.
 *
 * Description: This function takes an array that has two sorted halves 
 * (e.g., the left half and right half of an array) and merges them 
 * into a single sorted array based on the comparison function `IsBefore`.
 */
template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(const Type& a, const Type& b)) // Mark comparator parameters as const
{
    int i = 0, j = 0, k = 0;
    int mid = n / 2;
    int sizeL = mid;
    int sizeR = n - mid;

    Type* left = new Type[sizeL];
    Type* right = new Type[sizeR];

    for (int index = 0; index < sizeL; index++)
        left[index] = a[index];

    for (int index = 0; index < sizeR; index++)
        right[index] = a[sizeL + index];

    // Merge the temporary arrays back into the original array
    while (i < sizeL && j < sizeR) {
        if (IsBefore(left[i], right[j])) {  // Use IsBefore for comparison
            a[k] = left[i];
            i++;
        } else {
            a[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left, if any
    while (i < sizeL) {
        a[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right, if any
    while (j < sizeR) {
        a[k] = right[j];
        j++;
        k++;
    }

    // Free the allocated memory
    delete[] left;
    delete[] right;
}


/**
 * MergeSort - Recursively sorts an array using Merge Sort algorithm.
 * @a: Pointer to the array.
 * @n: Total number of elements in the array.
 * @IsBefore: Comparator function to compare elements.
 *
 * Description: This function implements the Merge Sort algorithm. It divides
 * the array into halves, sorts each half recursively, and merges them back
 * using the `Merge` function. The sorting is done according to the comparator
 * function `IsBefore`.
 */
template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(const Type& a, const Type& b))
{
    if (n <= 1)
        return;
    
    int middle = n / 2;
    MergeSort(a, middle, IsBefore);
    MergeSort(a + middle, n - middle, IsBefore);
    Merge(a, n, IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * struct Edge - Represents an edge in the graph.
 * @u: Starting vertex of the edge.
 * @v: Ending vertex of the edge.
 * @w: Weight of the edge.
 *
 * Description: This structure represents an edge in the graph, with two vertices
 * and a weight. The weight of the edge is used for sorting and determining
 * which edges should be included in Kruskal's algorithm.
 */
struct Edge
{
    int u, v;
    int w;
};


/**
 * IsBeforeEdge - Comparator function to compare two edges.
 * @a: The first edge to compare.
 * @b: The second edge to compare.
 *
 * Return: Returns true if the weight of edge a is less than the weight of edge b.
 *
 * Description: This function compares two edges based on their weights.
 * It is used as a comparator in the `MergeSort` function to sort edges
 * in ascending order of their weights.
 */
bool IsBeforeEdge(const Edge& a, const Edge& b)
{
    return a.w < b.w;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * main - Entry point of the program.
 *
 * Return: Always returns 0.
 *
 * Description: 
 */
int main()
{
    // M:  number of junctions in Byteland
    // N:  number of roads in Byteland
    int M, N;
    while (true) {
        cin >> M >> N;
        if (M == 0 && N == 0) {
            break;
        }

        DisjointSets roads;
        roads.Initialize(M);

        Edge *edges = new Edge[N];
        int totalWeight = 0;
        for (int i = 0; i < N; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            totalWeight += edges[i].w;
        }

        // Sort edges by weight before applying Kruskal's algorithm
        MergeSort(edges, N, IsBeforeEdge);

        int MSTWeight = 0;
        for (int i = 0; i < N; i++) {
            if (roads.Union(edges[i].u, edges[i].v)) {
                MSTWeight += edges[i].w;
            }
        }

        // Print the difference between the total weight and the MST weight
        cout << totalWeight - MSTWeight << endl;

        roads.Destroy();
        delete[] edges;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
