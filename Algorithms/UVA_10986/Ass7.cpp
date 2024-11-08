// GROUP:   2
// ID:      20227012
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name:    Rodyna Amr Fathy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int	v;
	int	w;

    Edge(int vertix, int weight) : v(vertix), w(weight) {}

    Edge() : v(0), w(0) {}

    friend ostream& operator<<(ostream& os, const Edge& edge)
    {
        os << "(v: " << edge.v << ", w: " << edge.w << ")";
        return os;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize()
    {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }
	void Destroy()
    {
        delete[] arr;
    }
	void AddLast(Value v)
    {
        if (n == sz)
        {
            sz *= 2;
            Value* temp = new Value[sz];
            for (int i = 0; i < n; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[n++] = v;
    }
	void RemoveLast()
    {
        if (n > 0)
            n--;
    }
	Value& operator[](int i)
    {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap {
    int* pos; // pos[v] = i where a[i].v = v, otherwise pos[v] = -1
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) { // n is required to allocate and initialize pos[]
        a.Initialize();
        pos = new int[n];
        for (int i = 0; i < n; i++) {
            pos[i] = -1;
        }
        IsBefore = _IsBefore;
    }

    void Destroy() {
        delete[] pos;
        a.Destroy();
    }

    void Print() {
        int level = 0;
        int maxNodesAtLevel = 1; // Number of nodes at the current level

        cout << "Heap Tree Structure:" << endl;

        for (int i = 0; i < a.n; i++) {
            // Print a new line when moving to a new level
            if (i == maxNodesAtLevel - 1) {
                cout << endl;       // Start a new line for the new level
                level++;
                maxNodesAtLevel += (1 << level);  // 2^level nodes in the next level
            }

            cout << a[i] << " ";  // Assuming Elem has an overloaded << operator
        }

        cout << endl;
    }

    int Child(int i) {
        return 2 * i + 1;
    }

    int Parent(int i) {
        return (i - 1) / 2;
    }

    Elem GetFirst() {
        return a[0];
    }

    Elem RetrieveFirst() {
        Elem first = Elem();
        if (a.n != 0) {
            first = a[0];
            pos[first.v] = -1; // Mark the first element as removed
            a[0] = a[a.n - 1];
            pos[a[0].v] = 0; // Update pos for the new root
            a.RemoveLast();
            MoveDown(0);
        }

        return first;
    }

    void Add(Elem e) {
        a.AddLast(e);
        pos[e.v] = a.n - 1; // Update pos for the new element
        MoveUp(a.n - 1);
    }

    void MoveUp(int ind) {
        while (ind > 0 && IsBefore(a[ind], a[Parent(ind)])) {
            // Swap the element with its parent.
            Swap(ind, Parent(ind));
            ind = Parent(ind);
        }
    }

    void MoveDown(int ind) {
        int smallest = ind;
        int left = Child(ind);
        int right = left + 1;

        if (left < a.n && IsBefore(a[left], a[smallest]))
            smallest = left;
        if (right < a.n && IsBefore(a[right], a[smallest]))
            smallest = right;

        if (smallest != ind) {
            // Swap with the smaller child.
            Swap(ind, smallest);
            MoveDown(smallest);
        }
    }

    void Swap(int i, int j) {
        // Swap elements in the array
        Elem temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        // Update positions in the pos array
        pos[a[i].v] = i;
        pos[a[j].v] = j;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<Edge> adj;

	void Initialize()
    {
        adj.Initialize();
    }
	void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];

        for (int i = 0; i < n; ++i) {
            nodes[i].Initialize();
        }
    }
	void Destroy()
    {
        for (int i = 0; i < n; ++i) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }

    int dijkstra(int S, int T)
    {
        int* cost = new int[n];
        int* parents = new int[n];
        bool* visited = new bool[n];
        Heap<Edge> minheap;
        minheap.Initialize(IsBefore, n);

        for (int i = 0; i < n; ++i) {
            cost[i] = INT_MAX;
            parents[i] = -1;
            visited[i] = false;
        }

        cost[S] = 0;
        minheap.Add(Edge(S, 0));
        while(minheap.a.n != 0)
        {
            Edge current = minheap.RetrieveFirst();
            int u = current.v;
            
            if (visited[u])
                continue;
            visited[u] = true;

            for (int i = 0; i < nodes[u].adj.n; ++i) {
                Edge neighbor = nodes[u].adj[i];
                int v = neighbor.v;
                int new_cost = cost[u] + neighbor.w;

                if (new_cost < cost[v]) {
                    cost[v] = new_cost;
                    parents[v] = u;
                    minheap.Add(Edge(v, new_cost));
                }
            }

        }

        int result = cost[T];
        delete[] cost;
        delete[] parents;
        delete[] visited;
        minheap.Destroy();

        return result == INT_MAX ? -1 : result;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Graph graph;

    int cases;
    cin >> cases;

    for(int _case = 1; _case <= cases; _case++)
    {
        int n, m, S, T;
        int shortestpath = 0;

        cin>> n >> m >> S >> T;

        if(m == 0)
        {
            cout << "Case #"<< _case <<": unreachable"<<endl;
            continue;
        }

        graph.Initialize(n);

        for(int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            // Bidirectional
            graph.nodes[u].adj.AddLast(Edge(v, w));
            graph.nodes[v].adj.AddLast(Edge(u, w));
        }

        shortestpath = graph.dijkstra(S, T);
        
        cout<<"Case #"<< _case << ":" << shortestpath << endl;
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////