#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class charDLLNode {
public:
    char info;
    charDLLNode *prev;
    charDLLNode *next;
    charDLLNode() {
        prev = 0;
        next = 0;
    }
    charDLLNode(int el, charDLLNode *next = 0, charDLLNode *prev = 0) {
        info = el; this->next = next; this->prev = prev;
    }
};


class charDLList{
public:
    charDLLNode *head;
    charDLLNode *tail;
    int size;
public:
    charDLList() {
        head = tail = 0;
        size = 0;
    }
    void printList();
    void addToTail(char);
    void addToHead(char);
    void addToPosition(char, int);
    void removeFromPosition(int);
    void deleteFromHead();
    void deleteFromTail();
    void reverseList();
    void concatenation(charDLList &);
    string getSubstring(int, int);
    int search(string);
    void replacement(string, string);
};
void charDLList :: printList(){
    for (charDLLNode* p = head ; p != 0 ; p = p->next){
        cout<< p ->info;
    }
    cout<<endl;
}
void charDLList :: addToTail(char info){
    charDLLNode* newnod = new charDLLNode(info);
    if(tail != 0){
        newnod->prev = tail;
        tail->next = newnod;
    }
    tail = newnod;
    if(head == 0){
        head = newnod;
    }
    size++;
}
void charDLList :: addToHead(char info){
    charDLLNode* newnod = new charDLLNode(info);
    if(head != 0){
        newnod->next = head;
        head->prev = newnod;
    }
    head = newnod;
    if(tail == 0){
        tail = newnod;
    }
    size++;
}
void charDLList :: addToPosition(char info, int index){
    if (index == 0){
        addToHead(info);
    } else if (index >= size){ 
        addToTail(info);
    } else {
        charDLLNode* p = head;
        for(int i = 0 ; i < index - 1; i++){
            p = p->next;
        }
        charDLLNode *newnod= new charDLLNode(info, p->next, p);
        p->next->prev = newnod;
        p->next = newnod;
        size++;
    }
}
void charDLList :: removeFromPosition(int index){
    if (index == 0){
        deleteFromHead();
    } else if (index >= size){ 
        deleteFromTail();
    }
    else {
        charDLLNode* p = head;
        for(int i = 0 ; i < index - 1; i++){
            p = p->next;
        }
        charDLLNode* d = p->next;
        p->next = d->next;
        if (d->next != nullptr){
            d->next->prev = p;
        }
        if (d == tail) {
            tail = p;
        }
        delete d;
    }
}
void charDLList :: deleteFromHead(){
    if(head == 0) return;
    charDLLNode* temp = head;
    if(head == tail){
        head = tail = 0;
    }else{
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
    }
    delete temp;
    size--;
}
void charDLList :: deleteFromTail(){
    if(head == 0) return;
    charDLLNode* temp = tail;
    if(head != tail){
        tail = tail->prev;
        tail->next = 0;
    }
    delete temp;
    size--;
}
void charDLList:: reverseList() {
    if (head == nullptr || head == tail) 
        return;

    charDLLNode* current = head;
    charDLLNode* temp = nullptr;

    temp = head;
    head = tail;
    tail = temp;

    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
}
void charDLList:: concatenation(charDLList &list){
    if (list.head == nullptr)
        return;
    if(this->head == nullptr){
        //make our head the head of l2 "address in memory"
        this->head = list.head;
        this->tail = list.tail;
    }
    else{
        this->tail->next=list.head;
        this->tail->next->prev = this->tail;
        this->tail = list.tail;
    }
    this->size += list.size;
}

/*// another way for concatenation
void concatenation(IntDLList &list){
    if (list.head == nullptr)
        return;
    if(this->head == nullptr){
        //make our head the head of l2 "address in memory"
        this->head = list.head;
        this->tail = list.tail;
    }
    else{
        IntDLLNode* current = this->head;
        while(current != nullptr){
            addToTail(current->info);
            current = current -> next;
        }
    }
}
*/
string charDLList:: getSubstring(int index, int length) {
    // Assuming index starts from zero
    charDLLNode* p = this->head;
    if (this->head == nullptr)
        return "nullptr";

    // Move p to the starting index
    for (int i = 0; i < index; ++i) {
        if (p == nullptr)
            return "reached the end of list";
        p = p->next;
    }

    // Make sure length is not longer than size
    length = min(length, this->size - index);

    string result = "";
    for (int i = 0; i < length && p != nullptr; ++i) {
        result += p->info;
        p = p->next;
    }
    return result;
}
int charDLList:: search(string s) {
    if (this->head == nullptr)
        return -1;

    charDLLNode* main = this->head;
    charDLLNode* loop;
    int i = 0;

    while (main != nullptr) {
        int j = 0;
        loop = main;
        while (loop != nullptr && loop->info == s[j]) { 
            j++;
            loop = loop->next;
        }
        if (s[j] == '\0')
            return i;
        i++;
        main = main->next;
    }
    return -1;
}
void charDLList:: replacement(string tobereplaced, string newstr) {
    int startIndex = search(tobereplaced);
    if (startIndex == -1) {
        return;
    }
    int i = 0;
    int len = tobereplaced.length();
    while (i < len && this->head != nullptr) {
        if (startIndex >= size)
            return;
        removeFromPosition(startIndex);
    }
    int j = 0;
    while (newstr[j] != '\0') {
        addToPosition(newstr[j], startIndex + j);
        j++;
    }
}


int main() {
    charDLList list1, list2;
    int i = 0;
    // Input for list 1
    string str1;
    cout << "Enter string to add to list 1: ";
    getline(cin, str1);
    while (str1[i] != '\0'){
        list1.addToTail(str1[i]);
        i++;
    }

    // Input for list 2
    string str2;
    i = 0;
    cout << "Enter string to add to list 2: ";
    getline(cin, str2);
    while (str2[i] != '\0'){
        list2.addToTail(str2[i]);
        i++;
    }

    // Concatenation
    list1.concatenation(list2);
    cout << "Concatenated List: ";
    list1.printList();

    // Removing a character by index
    int indexToRemove;
    cout << "Choose a character by index to remove: ";
    cin >> indexToRemove;
    list1.removeFromPosition(indexToRemove);
    cout << "List after removal: ";
    list1.printList();

    // Getting a substring
    int index, length;
    cout << "Enter index and length to get substring: ";
    cin >> index >> length;
    string substring = list1.getSubstring(index, length);
    cout << "Substring: " << substring << endl;

    // Searching for a string
    string searchString;
    cout << "Search for a string in the list: ";
    cin >> searchString;
    int searchIndex = list1.search(searchString);
    if (searchIndex != -1)
        cout << "Found at index " << searchIndex << endl;
    else
        cout << "Not found." << endl;

    // Replacing substrings
    string replaceStr1, replaceStr2;
    cout << "Enter 2 substrings to replace one with another: ";
    cin >> replaceStr1 >> replaceStr2;
    list1.replacement(replaceStr1, replaceStr2);
    cout << "List after replacement: ";
    list1.printList();

    // Reversing the list
    list1.reverseList();
    cout << "Reversed List: ";
    list1.printList();

    return 0;
}