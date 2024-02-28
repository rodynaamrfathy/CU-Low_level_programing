#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
void bubble_sort(T *arr, size_t size) {
    T temp;
    for (size_t i = 0; i < size - 1; i++){
        for (size_t j = 0; j < size - 1; j++){
            if (arr[j] > arr[j + 1]){
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    char arr1[] = {'X', 'C', 'A', '6', 'Z'};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Before Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }

    bubble_sort(arr1, size);

    cout << "\nAfter Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }

    return 0;
}
