// GROUP:   2
// ID:      20227012
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Rodyna Amr Fathy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

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
		sz = 0;
		n = 0;
	}
	void AddLast(Value v)
	{
		if (n == sz) {
			sz = sz * 3 / 2; // Golden Ratio Growth
			Value* newArr = new Value[sz];
			for (int i = 0; i < n; ++i) {
				newArr[i] = arr[i];
			}
			delete[] arr;
			arr = newArr;
		}
		arr[n++] = v;
	}
	void RemoveLast()
	{
        if (n > 0) {
            n--;
        }	
	}
	Value& operator[](int i)
	{
		return arr[i];
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&))
	{
		IsBefore = _IsBefore;
		a.Initialize();
	}
	void Destroy()
	{
		a.Destroy();
		IsBefore = nullptr;
	}
	int Child(int i)
	{
		return 2 * i + 1;
	}
	int Parent(int i)
	{
		return (i - 1) / 2;
	}
	void MoveUp(int ind)
	{
		while (ind > 0 && IsBefore(a[ind], a[Parent(ind)]))
		{
			// Swap
			Elem temp = a[ind];
			a[ind] = a[Parent(ind)];
			a[Parent(ind)] = temp;

			ind = Parent(ind);
		}
	} 
	void MoveDown(int ind)
	{
		int smallest = ind;
		int left = Child(ind);
		int right = left + 1;

		if (left < a.n && IsBefore(a[left], a[smallest]))
			smallest = left;
		if (right < a.n && IsBefore(a[right], a[smallest]))
			smallest = right;

		if (smallest != ind)
		{
			// Swap
			Elem temp = a[ind];
			a[ind] = a[smallest];
			a[smallest] = temp;

			// Repeat
			MoveDown(smallest);
		}
	} 
	void Add(Elem e)
	{
		a.AddLast(e);
		MoveUp(a.n - 1);
	}
	Elem GetFirst()
	{
		// Top
		return a[0];
	}
	Elem RetrieveFirst()
	{ 
		if (a.n == 0) throw runtime_error("Heap is empty");
		// Pop
		Elem first = a[0];
		a[0] = a[a.n - 1];
		a.RemoveLast(); // Use RemoveLast instead of decrementing n directly
		MoveDown(0);

		return first;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a < b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    while (true)
    {
        int N;
        cin >> N;

        if (N == 0) break;

        Heap<int> h;
        h.Initialize(IsBeforeInt);
        int totalCost = 0;

        for (int i = 0; i < N; i++) 
        {
            int num;
            cin >> num;
            h.Add(num);
        }

        while (h.a.n > 1)
        {
            int A = h.RetrieveFirst();
            int B = h.RetrieveFirst();

            int sum = A + B;
            totalCost += sum;
            h.Add(sum);
        }

        cout << totalCost << endl;
        h.Destroy();
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////