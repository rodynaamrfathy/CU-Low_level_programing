#include <iostream>
#include <string>
using namespace std;

class DoublyLinkedList {

private:

    struct Node {
        char Character;
        Node *next;
        Node *prev;
    };

    Node *Head;
    Node *Tail;
    int Length;

public:

    DoublyLinkedList() {
        Head = Tail = nullptr;
        Length = 0;
    }

    bool isEmpty() {
        return (Head == nullptr);
    }

    void InsertFirst(char character) {

        Node *newNode = new Node;
        newNode->Character = character;

        if (Length == 0) {
            Head = Tail = newNode;
            newNode->next = newNode->prev = nullptr;
        } else {

            newNode->next = Head;
            newNode->prev = nullptr;
            Head->prev = newNode;
            Head = newNode;

        }
        Length++;
    }

    void InsertLast(char character) {

        Node *newNode = new Node;
        newNode->Character = character;

        if (Length == 0) {

            Head = Tail = newNode;
            newNode->next = newNode->prev = nullptr;

        } else {

            newNode->prev = Tail;
            newNode->next = nullptr;
            Tail->next = newNode;
            Tail = newNode;

        }
        Length++;
    }

    void InsertAtPosition(char character, int pos) {
        if (pos < 0 || pos > Length) {
            cout << "Out of range\n";
            return;
        }

        Node *newNode = new Node;
        newNode->Character = character;

        if (pos == 0) {
            newNode->next = Head;
            newNode->prev = nullptr;

            if (Head != nullptr) {
                Head->prev = newNode;
            } else {
                Tail = newNode;
            }

            Head = newNode;
        } else if (pos == Length) {
            newNode->prev = Tail;
            newNode->next = nullptr;

            if (Tail != nullptr) {
                Tail->next = newNode;
            } else {
                Head = newNode;
            }

            Tail = newNode;
        } else {
            Node *current;
            int midpoint = Length / 2;

            if (pos <= midpoint) {
                current = Head;
                for (int i = 1; i < pos; i++) {
                    current = current->next;
                }
            } else {
                current = Tail;
                for (int i = Length - 1; i > pos; i--) {
                    current = current->prev;
                }
            }

            newNode->prev = current;
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;
        }

        Length++;
    }
    void RemoveFirst() {

        if (Length == 0) {
            cout << "Empty list\n";
            return;
        } else if (Length == 1) {
            delete Head;
            Head = Tail = nullptr;
        } else {
            Node *current = Head;
            Head = Head->next;
            Head->prev = nullptr;
            delete current;
        }
        Length--;
    }

    void RemoveLast() {

        if (Length == 0) {
            cout << "Empty list\n";
            return;
        } else if (Length == 1) {

            delete Head;
            Head = Tail = nullptr;

        } else {

            Node *current = Tail;
            Tail = Tail->prev;
            Tail->next = nullptr;
            delete current;

        }
        Length--;
    }

    void RemoveAtPosition(int pos) {

        if (pos < 0 || pos > Length) {
            cout << "Out of range\n";
            return;
        } else {

            if (pos == 0) {
                RemoveFirst();
            }

            else if (pos == Length - 1) {
                RemoveLast();
            }

            else {

                Node *current = Head->next;
                Node *prev = Head;
                for (int i = 1; i < pos; i++) {
                    prev = current;
                    current = current->next;
                }

                prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                Length--;

            }

        }

    }

    void Concatenate(DoublyLinkedList &list) {

        if (list.isEmpty()) {
            cout << "list to concatenate is empty\n";
            return;
        }

        if (this->Head == nullptr) {
            this->Head = list.Head;
            this->Tail = list.Tail;
        } else {
            this->Tail->next = list.Head;
            this->Tail->next->prev = this->Tail;
            this->Tail = list.Tail;
        }
        this->Length += list.Length;

    }

    string ExtractSubString (int start,int length) {

        if (start < 0 || start >= Length || length <=0) {

            return "oops cant extract";
        }


        Node *current = Head;

        for (int i = 0;i<start;i++) {
            current = current -> next;
        }
        string substring="";
        for (int i = 0;i<length;i++) {
            substring += current ->Character;
            current = current -> next;
        }
        return substring;

    }

    int Search (string substring) {

        if (substring == "") {
            return -1;
        }

        Node * current = Head;
        int idx1 = 0;

        while (current != nullptr) {
            int idx2 = 0;
            while (current != nullptr && current -> Character == substring[idx2]) {
                idx2++;
                current = current->next;
            }
            if (substring[idx2] == '\0') {
                return idx1;
            }
            idx1++;
            current = current -> next;

        }

        return -1;

    }



    void Print(){

        Node *current = Head;
        while (current != NULL){
            cout<<current->Character;
            current = current -> next;
        }
        cout<<endl;
    }

   void Replace(string replace, string news) {
    int start = Search(replace);

    if (start == -1) {
        return;
    }

    int i = 0;
    int lengthDelete = replace.length();

    while (i < lengthDelete) {
        RemoveAtPosition(start);
        i++;
    }

    int idx = 0;
    while (news[idx] != '\0') {
        InsertAtPosition(news[idx], start + idx);
        idx++;
    }
}



        


};

int main() {
    DoublyLinkedList list1, list2;
    int i = 0;
    // Input for list 1
    string str1;
    cout << "Enter string to add to list 1: ";
    getline(cin, str1);
    while (str1[i] != '\0') {
        list1.InsertLast(str1[i]);
        i++;
    }

    // Input for list 2
    string str2;
    i = 0;
    cout << "Enter string to add to list 2: ";
    getline(cin, str2);
    while (str2[i] != '\0') {
        list2.InsertLast(str2[i]);
        i++;
    }

    // Concatenation
    list1.Concatenate(list2);
    cout << "Concatenated List: ";
    list1.Print();

    // Removing a character by index
    int indexToRemove;
    cout << "Choose a character by index to remove: ";
    cin >> indexToRemove;
    list1.RemoveAtPosition(indexToRemove);
    cout << "List after removal: ";
    list1.Print();

    // Getting a substring
    int index, length;
    cout << "Enter index and length to get substring: ";
    cin >> index >> length;
    string substring = list1.ExtractSubString(index, length);
    cout << "Substring: " << substring << endl;

    // Searching for a string
    string searchString;
    cout << "Search for a string in the list: ";
    cin >> searchString;
    int searchIndex = list1.Search(searchString);
    if (searchIndex != -1)
        cout << "Found at index " << searchIndex << endl;
    else
        cout << "Not found." << endl;

    // Replacing substrings
    string replaceStr1, replaceStr2;
    cout << "Enter 2 substrings to replace one with another: ";
    cin >> replaceStr1 >> replaceStr2;
    list1.Replace(replaceStr1, replaceStr2);
    cout << "List after replacement: ";
    list1.Print();

    // Reversing the list
    //list1.Reverse(); 
    //cout << "Reversed List: ";
    //list1.Print();

    return 0;
}