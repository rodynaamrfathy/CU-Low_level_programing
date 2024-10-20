#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;


//task 1

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
        if(flag){
            comparisons++;
        }
        flag = true;
        arr[j + 1] = key;
        
        
    }
}


void insertionSortBinary(int arr[], int size, int& comparisons, int& shifts) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] > key) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
            comparisons++;
        }

        for (int j = i - 1; j >= low; j--) {
            arr[j + 1] = arr[j];
            shifts++;
        }
        arr[low] = key;

    }
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


//task 2

template <class T>
class SortingAlgorithms {
protected:
    int comparisons, moves;
public:
    SortingAlgorithms(){
        this->comparisons = 0;
        this->moves = 0;
    }
    virtual void sort(T *arr, size_t size) = 0;
    void print_array(T *arr, size_t size) {
        cout << "\t" << "sorted array:  ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "\t" << "Comparisons:  " << this->comparisons << endl;
        cout << "\t" << "Moves:  " << this->moves << endl;
    }
    void set_to_zero(){
        this->comparisons = 0;
        this->moves = 0;
    }
};

template <class T>
class SelectionSort : public SortingAlgorithms<T> {
public:
    void sort(T *arr, size_t size) {
        T temp;
        int min;

        for (size_t start = 0; start < size - 1; start++) {
            min = start;
            for (size_t index = start + 1; index < size; index++) {
                this->comparisons++;
                if (arr[min] > arr[index]) {
                    min = index;
                }
            }
            temp = arr[start];
            arr[start] = arr[min];
            arr[min] = temp;
            this->moves += 3;
        }
    }
};

template <class T>
class ShellSort : public SortingAlgorithms<T> {
public:
    void sort(T *arr, size_t size) {
        for (size_t gap = size / 2; gap > 0; gap /= 2) {
            for (size_t i = gap; i < size; i++) {
                T temp = arr[i];
                size_t j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    this->moves++;
                    this->comparisons++;
                    arr[j] = arr[j - gap];
                }
                this->comparisons++;
                arr[j] = temp;
            }
        }
    }
};

template <class T>
class Merge {
private:
    int comparisons;

    void merge(T arr[], int first, int middle, int last) {
        int i = 0, j = 0, k = first;
        int sizeL = middle - first + 1;
        int sizeR = last - middle;
        T *aleft = new T[sizeL];
        T *aright = new T[sizeR];

        for (int index = 0; index < sizeL; index++) {
            aleft[index] = arr[first + index];
        }
        for (int index = 0; index < sizeR; index++) {
            aright[index] = arr[middle + 1 + index];
        }

        while (i < sizeL && j < sizeR) {
            if (aleft[i] <= aright[j]) {
                comparisons++;
                arr[k] = aleft[i];
                i++;
            } else {
                comparisons++;
                arr[k] = aright[j];
                j++;
            }
            k++;
        }

        while (i < sizeL) {
            arr[k] = aleft[i];
            i++;
            k++;
        }

        while (j < sizeR) {
            arr[k] = aright[j];
            j++;
            k++;
        }

        delete[] aleft;
        delete[] aright;
    }

public:
    Merge() {
        comparisons = 0;
    }

    void merge_sort(T arr[], int left, int right) {
        if (left >= right)
            return;
        int middle = (left + right) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }

    void print_mergearray(T *arr, int size) {
        cout << "\t" << "sorted array:  ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "\t" << "Comparisons:  " << comparisons << endl;
    }
    void set_to_zero(){
        this->comparisons = 0;
    }
};



int main() {
    int answer;
    cout<<"enter 1 for task 1 OR 2 for task2"<<endl;
    cin>>answer;

    if (answer == 2)
    {
        cout<<endl;
        cout<<"----------TASK 2----------"<<endl;
        string name = "arrays.txt";
        ifstream file(name);
        Merge<int> to_merge;
        SelectionSort<int> selection_sort;
        ShellSort<int> shell_sort;

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                int size = line[0] - '0';
                int *arr1 = new int[size];
                int *arr2 = new int[size];
                int *arr3 = new int[size];

                cout << "\n \n \n ----------------------- \n \n \n";

                cout << "original array:  ";
                int index = 2;
                int arrIndex = 0;
                while (index < line.length()) {
                    string digit = "";
                    while (index < line.length() && line[index] != ' ') {
                        digit += line[index];
                        index++;
                    }
                    arr1[arrIndex] = stoi(digit);
                    arr2[arrIndex] = stoi(digit);
                    arr3[arrIndex] = stoi(digit);
                    arrIndex++;
                    index++;
                }
                for (int i = 0; i < size; i++) {
                    cout << arr1[i] << " ";
                }

                cout << "\n Selection sort:  " << endl;
                selection_sort.sort(arr1, size);
                selection_sort.print_array(arr1, size);
                selection_sort.set_to_zero();
                cout << "\n";

                cout << "Shell sort:  " << endl;
                shell_sort.sort(arr2, size);
                shell_sort.print_array(arr2, size);
                shell_sort.set_to_zero();
                cout << "\n";

                cout << "Merge sort:  " << endl;
                to_merge.merge_sort(arr3, 0, size - 1);
                to_merge.print_mergearray(arr3, size);
                to_merge.set_to_zero();

                cout << "\n";

                delete[] arr1;
                delete[] arr2;
                delete[] arr3;
            }
            file.close();
        } else {
            cout << "File not found" << endl;
        }
    }

    else if(answer ==1)
    {
        cout<<endl;
        cout<<"----------TASK 1----------"<<endl;
        int size;
        cout << "Enter the size of the array: ";
        cin >> size;
        int arr[size];
        cout << "Enter the elements of the array: "<<endl;
        for (int i = 0; i < size; ++i) {
            cin >> arr[i];
        }
        int comparisons = 0, shifts = 0;
        int comparisons_binary = 0, shifts_binary = 0;
        int arr_copy[size];
        for (int i = 0; i < size; ++i) {
            arr_copy[i] = arr[i];
        }
        int flag = 1;

        while(flag == 1)
        {
            int choice;
            cout<<"enter choice 1 for linear search"<< " "<<"OR 2 for binary serach"<<endl;
            cin>>choice;
            if (choice == 1){
                comparisons = 0;
                shifts = 0;
                insertionSortLinear(arr, size, comparisons, shifts);
                cout << "Sorted array using linear search: ";
                printArray(arr, size);
                cout << "Number of comparisons: " << comparisons << endl;
                cout << "Number of shifts: " << shifts << endl;
                cout<< endl;
            }
            else if(choice == 2){
            comparisons_binary = 0;
            shifts_binary = 0;
                insertionSortBinary(arr_copy, size, comparisons_binary, shifts_binary);
                cout << "Sorted array using binary search: ";
                printArray(arr_copy, size);
                cout << "Number of comparisons: " << comparisons_binary << endl;
                cout << "Number of shifts: " << shifts_binary << endl;
            }
            else
            {
                flag = 0;
                cout<<"------program terminated------"<<endl;
            }
        }
    }
    return 0;
}
