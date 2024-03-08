#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

template<class T>
class MultiArray;

template<class T>
class Array
{
    string name;
    T *arr;
    int size;
public:
    Array(string name, int size)
    {
        this->size = size;
        this->name = name;
        arr = new T[size];
    }
    string getName() const
    {
        return name;
    }

    int getSize() const
    {
        return size;
    }

    T* getArr() const
    {
        return arr;
    }
    Array(const Array& obj)
    {
        name = obj.name;
        size = obj.size;
        arr = new T[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = obj.arr[i];
        }
    }
    ~Array()
    {
        delete[] arr;
    }
    friend class MultiArray<T>;
};

template<class T>

class MultiArray
{
    int noOfArrays;
public:
    Array<T> **arrays;

    MultiArray()
    {
        cout<<"no arrays created"<<endl;
        noOfArrays = 0;
    }
    int getnoOfArrays() const
    {
    return noOfArrays;
    }
    MultiArray(const MultiArray& obj)
    {
        noOfArrays = obj.noOfArrays;
        arrays = new Array<T>*[noOfArrays];
        for (int i = 0; i < noOfArrays; i++)
        {
            arrays[i] = new Array<T>(*obj.arrays[i]);
        }
    }

    MultiArray(int n)
    {
        string name;
        int elementsperarray;

        this->noOfArrays = n;
        arrays = new Array<T>*[n];
        for (int i=0; i < n; i++)
        {
            cout << "Enter the name of Array " << i + 1 << ": ";
            cin>> name;
            cout << "How many elements does Array " << i + 1 << " have?: ";
            cin >> elementsperarray;
            cout << endl;
            arrays[i] = new Array<T>(name,elementsperarray);
        }
    }
    MultiArray(int noOfArrays, string *arrs, int *elementsperarray)
    {
        this->noOfArrays = noOfArrays;
        arrays = new Array<T>*[noOfArrays];
        for (int i=0; i < noOfArrays; i++)
        {
            arrays[i] = new Array<T>(arrs[i],elementsperarray[i]);
        }
    }

    void loadFromFile(string arrName, string fileName)
    {
        ifstream file(fileName);
        int i = 0;
        if (file.is_open())
        {
            for (i = 0; i < noOfArrays; i++)
            {
                if (arrays[i]->name == arrName)
                {
                    for (int j = 0; j < arrays[i]->size; j++)
                    {
                        file >> arrays[i]->arr[j];
                    }
                    break;
                }
            }
            file.close();
            return;
        }
        else
        {
            cout << "Unable to open file: " << fileName << endl;
        }
        if (i == noOfArrays)
        {
            cout << "Not found in file." << endl;
        }
    }

    T* subArray(string name, int startIndex, int endIndex, int step = 1)
    {
        T *tempArr = new T [abs(startIndex - endIndex) + 1];
        for (int i = 0; i < noOfArrays; i++)
        {
            if (arrays[i]->name == name)
            {
                for(int j = startIndex; j < endIndex; j+= step)
                {
                    tempArr[j] = arrays[i]->arr[j];
                }
                for(int j = endIndex; j < startIndex; j-= step)
                {
                    tempArr[j] = arrays[i]->arr[j];
                }
            }
        }
        if (startIndex > endIndex)
        {
            return (reverse(tempArr->name));
        }
        return tempArr;
    }

    void reverse(string name)
    {
        T *arr2;
        int k = 0;

        for (int i = 0; i < noOfArrays; i++)
        {
            if (arrays[i]->name == name)
            {
                arr2 = new T[arrays[i]->size];
                for (int j = arrays[i]->size - 1; j >= 0; j--)
                {
                    if (k < arrays[i]->size)
                    {
                        arr2[k] = arrays[i]->arr[j];
                        k++;
                    }
                }
                for (int j = 0; j < arrays[i]->size; j++)
                {
                    arrays[i]->arr[j] = arr2[j];
                }
                delete[] arr2;

                return;
            }
        }

            cout << "Array with name " << name << " not found. " << endl;
    }


    void _sort(string name)
    {
        for (int i = 0; i < noOfArrays; i++)
        {
            if (arrays[i]->name == name)
            {
                sort(arrays[i]->arr, (arrays[i]->arr) + arrays[i]->size);
            }
        }
    }

    bool search(T item)
    {
        for (int i = 0; i < noOfArrays; i++)
        {
            for(int j = 0; j < arrays[i]->size; j++)
            {
                if(item == arrays[i]->arr[j])
                {
                    return true;
                }
            }
        }
        return false;
    }

    T& operator()(string name, int index)
    {
        for (int i = 0; i < noOfArrays; i++)
        {
            if (arrays[i]->name == name)
            {
                if (index >= 0 && index < arrays[i]->size)
                {
                    return arrays[i]->arr[index];
                }
                /*else
                {
                    throw out_of_range("Index out of bounds");
                }*/
            }
        }
        //throw runtime_error("Array not found");
    }

    MultiArray split(string name)
    {
    int size2;
    int size1;
    int i;
    string arrs[] = {"1st", "2nd"};
    int arri[] = {size1, size2};

    for (i = 0; i < noOfArrays; i++)
    {
        if (arrays[i]->name == name)
        {
            size1 = arrays[i]->size / 2;
            size2 = (arrays[i]->size % 2 == 0) ? size1 : size1 + 1;

            MultiArray newobj(2, arrs, arri);

            for (int j = 0; j < size1; j++)
            {
                newobj.arrays[0]->arr[j] = arrays[i]->arr[j];
            }
            for (int j = 0; j < size2; j++)
            {
                newobj.arrays[1]->arr[j] = arrays[i]->arr[size1 + j];
            }

            return newobj;
        }
    }
    cout << "Array with name " << name << " not found. " << endl;
    return MultiArray();
    }

    T* merge( )
    {
            int totalSize = 0;

            for (int i = 0; i < noOfArrays; i++)
            {
                totalSize += arrays[i]->size;
            }

            
            T* merged = new T[totalSize];

            int currentIndex = 0;

            for (int i = 0; i < noOfArrays; i++)
            {
                for (int j = 0; j < arrays[i]->size; j++)
                {
                    merged[currentIndex++] = arrays[i]->arr[j];
                }
            }
            return merged;
    }

    void applyToArray(string name, void (*func)(T&))
    {
        for(int i = 0; i < noOfArrays; i++)
        {
             if (arrays[i]->name == name)
             {
                for(int j=0 ; j < arrays[i]->size; j++)
                {
                    func(arrays[i]->arr[j]);
                }
                return ;
             }
        }
    }

    template <class U>
    friend ostream& operator<<(ostream& out, const MultiArray<U>& obj);    
    ~MultiArray()
    {
        for (int i = 0; i < noOfArrays; i++) 
        {
            delete arrays[i];
        }

        delete[] arrays;
    }
};

template<class T>
ostream& operator<<(ostream& out, const MultiArray<T>& obj)
{
    T* arrayOfReq;
    for (int i = 0; i < obj.getnoOfArrays(); i++)
    {
        arrayOfReq = obj.arrays[i]->getArr();
        out << "Array " << i + 1 << " (" << obj.arrays[i]->getName() << "): ";
        for (int j = 0; j < obj.arrays[i]->getSize(); j++)
        {
            out << arrayOfReq[j] << " ";
        }
        out << endl;
    }
    return out;
}

template <class T2>
void square(T2 &x)
{
   x *= x;
}


int main()
{
    int noOfArrays;
    string input;
    cout<<endl;
    cout<<"Welcome to my program!!"<<endl;
    cout<<"Type the number of arrays:"<<endl;
    cin>>noOfArrays;
    MultiArray<int> myMultiArray(3);

    cout<<"type the \"name of the array you want to load\" form file or type \"auto\" so it can load data on it's own"<<endl;
    cin>> input;
    if("auto" == input)
    {
        for(int k = 0; k < myMultiArray.getnoOfArrays(); k++)
        {
            myMultiArray.loadFromFile(myMultiArray.arrays[k]->getName(), "data.txt");
        }
    }
    else
    {
        myMultiArray.loadFromFile(input, "data.txt");
    }

    cout << "Initial MultiArray:" << endl;
    cout << myMultiArray << endl;

    cout<<"Type the name of the array you want to apply a function to"<<endl;
    cin>> input;
    myMultiArray.applyToArray(input, square);

    cout << "MultiArray after applying square function:" << endl;
    cout << myMultiArray << endl;

    /*cout<<"Type the name of the array you want to split"<<endl;
    cin>> input;
    MultiArray<int> splitArray = myMultiArray.split(input);

    cout << "Splited Arrays:" << endl;
    cout << splitArray << endl;*/

    cout<<"merging arrays......."<<endl;
    int* mergedArray = myMultiArray.merge();

    cout << "Merged Array:" << endl;
    for (int i = 0; i < myMultiArray.getnoOfArrays(); i++)
    {
        cout << mergedArray[i] << " ";
    }
    cout << endl;

    cout<<"Type the name of the array you want to reverse"<<endl;
    cin>> input;
    myMultiArray.reverse(input);

    cout << "MultiArray after reversing"<< input << ":" << endl;
    cout << myMultiArray << endl;

    return 0;
}