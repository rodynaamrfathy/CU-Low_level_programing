#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
void selection_sort(T *arr, size_t size) {
    T temp; 
    int min;
    for (size_t start = 0; start < size - 1; start++) {
        min = start;
        for (size_t index = start + 1; index < size; index++) {
            if (arr[min] > arr[index]) {
                min = index;
            }
        }
        temp = arr[start];
        arr[start] = arr[min];
        arr[min] = temp;
    }
}

int main() {
    char arr1[] = {'6', 'A', 'X', 'C', 'Z'};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Before Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }

    selection_sort(arr1, size);

    cout << "\nAfter Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }

    return 0;
}
