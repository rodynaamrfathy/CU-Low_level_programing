#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
void merge(T arr[], int first, int middle, int last) {
    int i = 0, j = 0, k = first;
    int sizeL = middle - first + 1;
    int sizeR = last - middle;
    T* aleft = new T[sizeL];
    T* aright = new T[sizeR];
    
    for (int index = 0; index < sizeL; index++) {
        aleft[index] = arr[first + index];
    }
    for (int index = 0; index < sizeR; index++) {
        aright[index] = arr[middle + 1 + index];
    }

    while (i < sizeL && j < sizeR) {
        if (aleft[i] <= aright[j]) {
            arr[k] = aleft[i];
            i++;
        } else {
            arr[k] = aright[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of aleft, if any
    while (i < sizeL) {
        arr[k] = aleft[i];
        i++;
        k++;
    }

    // Copy the remaining elements of aright, if any
    while (j < sizeR) {
        arr[k] = aright[j];
        j++;
        k++;
    }

    delete[] aleft;
    delete[] aright;
}

template <class T>
void merge_sort(T arr[], int left, int right){
    if (left >= right)
        return ;
    int middle = (left + right)/2;
    merge_sort(arr, left, middle);
    merge_sort(arr, middle + 1, right);
    merge(arr, left, middle, right);
}

int main() {
    char arr1[] = {'X', 'C', 'A', '6', 'Z'};
    size_t size = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Before Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }

    merge_sort<char>(arr1, 0, size - 1);

    cout << "\nAfter Sorting:" << endl;
    for (size_t i = 0; i < size; i++) {
        cout << arr1[i] << "\t";
    }
    cout << endl;
    return 0;
}