#include <iostream>
#include <string>
using namespace std;

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
        arr = nullptr;
        sz = 0;
        n = 0;
    }

    void AddLast(Value v) {
        if (n == sz) {
            sz *= 2;
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
        if (n > 0) n--;
    }

    Value& operator[](int i) {
        return arr[i];
    }
};

struct code {
    int frequency;
    char character;
    string codeInBinary;
    code* left;
    code* right;

    code() : frequency(0), character('\0'), left(nullptr), right(nullptr) {}

    void printcode() {
        if (!codeInBinary.empty()) {
            cout << character << " -> " << codeInBinary << endl;
        }
    }
};

template<class Elem>
struct Heap {
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&)) {
        IsBefore = _IsBefore;
        a.Initialize();
    }

    void Destroy() {
        a.Destroy();
    }

    int Child(int i) { return 2 * i + 1; }
    int Parent(int i) { return (i - 1) / 2; }

    void MoveUp(int ind) {
        while (ind > 0 && IsBefore(a[ind], a[Parent(ind)])) {
            swap(a[ind], a[Parent(ind)]);
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
            swap(a[ind], a[smallest]);
            MoveDown(smallest);
        }
    }

    void Add(Elem e) {
        a.AddLast(e);
        MoveUp(a.n - 1);
    }

    Elem RetrieveFirst() {
        Elem first = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return first;
    }

    int FindCharInHeap(char c) {
        for (int i = 0; i < a.n; ++i) {
            if (a[i].character == c) return i;
        }
        return -1;
    }
};

bool IsBeforeInt(code& a, code& b) {
    return a.frequency < b.frequency;
}

void GenerateCodes(code* node, string prefix) {
    if (!node) return;

    if (!node->left && !node->right) {
        node->codeInBinary = prefix;
        node->printcode();
        return;
    }

    GenerateCodes(node->left, prefix + "0");
    GenerateCodes(node->right, prefix + "1");
}

void Huffmancodingtree(Heap<code>& minheap) {
    while (minheap.a.n > 1) {
        code* first = new code(minheap.RetrieveFirst());
        code* second = new code(minheap.RetrieveFirst());

        code* newNodeToMerge = new code();
        newNodeToMerge->frequency = first->frequency + second->frequency;
        newNodeToMerge->left = first;
        newNodeToMerge->right = second;

        minheap.Add(*newNodeToMerge);
    }

    code* root = new code(minheap.RetrieveFirst());
    GenerateCodes(root, "");
}

void UpdateHeapWithText(Heap<code>& heap, string& text) {
    for (int i = 0; i < text.size(); i++) {
        int index = heap.FindCharInHeap(text[i]);
        if (index != -1) {
            heap.a[index].frequency++;
            heap.MoveUp(index);
        } else {
            code newNode;
            newNode.character = text[i];
            newNode.frequency = 1;
            heap.Add(newNode);
        }
    }
}


int main()
{
    string text;
    Heap<code> minheap;
    minheap.Initialize(IsBeforeInt);

    while(true)
    {
        cout << "Enter a text (or 'q' to quit): ";
        cin >> text;
        if (text == "q")
            break;

        UpdateHeapWithText(minheap, text);
        Huffmancodingtree(minheap);
    }

    minheap.Destroy();

}
