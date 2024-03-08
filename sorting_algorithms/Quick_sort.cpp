#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
int partition(T arr[], int start, int end) {
    T pivot = arr[end]; // rightmost element is the pivot
    int index = start;

    for (int j = start; j < end; j++) {
        if (arr[j] <= pivot) {
            swap(arr[index], arr[j]);
            index++;
        }
    }

    swap(arr[index], arr[end]);
    return index;
}
template <class T>
void quick_sort(T arr[], int start, int end){
    if (start >= end)
        return ;
    int index = partition(arr, start, end);
    quick_sort(arr, start, index - 1);
    quick_sort(arr, index + 1, end);
}

int main() {
    char arr1[] = {'X', 'C', 'A', '6', 'Z'};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Before Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }

    quick_sort<char>(arr1, 0, size - 1);

    cout << "\nAfter Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }
    cout << endl;
    return 0;
}