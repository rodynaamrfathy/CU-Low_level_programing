// GROUP:   2
// ID:      20227012
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Rodyna Amr Fathy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];

        // kol element fy set lw7do w el parent -1 " aw hwa parent nfso"
        // singelton sets
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            num_nodes[i] = 1; // number of elements fy kol set
        }
    }
	void Destroy()
    {
        delete[] parent;
        delete[] num_nodes;
    }
    int Find(int i)
    {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = Find(parent[i]); // Path compression with return
    }
	bool Union(int i, int j)
    {
        int root_i = Find(i);
        int root_j = Find(j);

        // check homa fy nfs el set wlaa 
        if (root_i == root_j) {
            return false;
        }

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
// for me ashan lma arg3 ll ass
// N: Number of citizens in the town.
// M: Number of friendship pairs.
// You are given M pairs of people who are friends.
// Each pair consists of two integers, A and B, meaning that person A and person B are friends.
int main()
{
    //read the number of test cases.
    int T; 
    cin >> T;

     while (T--) {
        int N, M;
        cin >> N >> M;

        DisjointSets ds;
        ds.Initialize(N);

        // Read the pairs of friendships and union them
        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;

            ds.Union(A - 1, B - 1); // - 1 ashan bd2a men 0
        }
        // use 3dd el citizens ashana agib el root bta3 each w a3rf fy kol set kam
        int largest_group = 0;
        for (int i = 0; i < N; ++i) {
            int root = ds.Find(i);
            if (ds.num_nodes[root] > largest_group) {
                largest_group = ds.num_nodes[root];
            }
        }

        cout << largest_group << endl;
        ds.Destroy();
     }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////