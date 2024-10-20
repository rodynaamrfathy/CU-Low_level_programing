 #include <iostream>
using namespace std;


void insertionSortLinear(int arr[], int size, int& comparisons, int& shifts) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            comparisons++;
            shifts++;
        }
        arr[j + 1] = key;
        comparisons++;
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

int main() {
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
    return 0;
}