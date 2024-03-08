#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
void shell_sort(T *arr, size_t size){
    for (size_t gap = size/2; gap > 0; gap /= 2){
        for (size_t i = gap; i < size; i++) {
            T temp = arr[i];
            size_t j;
            for (j = i; j >= gap && temp < arr[j - gap]; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

template <class T>
void print_array(T arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}
int main() {
    char arr1[] = {'C', 'A', 'X', '6', 'Z'};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Before Sorting:" << endl;
    print_array(arr1, size);

    shell_sort(arr1, size);

    cout << "\nAfter Sorting:" << endl;
    print_array(arr1, size);

    return 0;
}