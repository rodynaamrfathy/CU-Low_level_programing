
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
void insertionSortLinear(int arr[], int size, int& comparisons, int& shifts) {
    bool flag = true;
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1; 
        while (j >= 0 && arr[j] > key) {
            flag = false;
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
            shifts++;
        }
        if(j >= 0 && arr[j] < key){
            comparisons++;
        }
        flag = true;
        arr[j + 1] = key;
        
        
    }
}

int main() {
    int arr[] = { 3, 1, 4, 2, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int comparisons = 0, shifts = 0;
    insertionSortLinear(arr, size, comparisons, shifts);
    cout << "Sorted array:";
    for (int i = 0; i < size; ++i) {
        cout << " " << arr[i];
    }
    cout << endl;
    cout << "Comparisons: " << comparisons << std::endl;
    cout << "Shifts: " << shifts << std::endl;
    return 0;
}
