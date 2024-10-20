#include <iostream>
#include <cstdlib>
using namespace std;

class IntSLLNode {
public:
    int info;
    IntSLLNode *next;
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(int el, IntSLLNode *ptr = 0) {
        info = el; next = ptr;
    }
};


class IntSLList{
private:
    IntSLLNode *head;
    IntSLLNode *tail;
    int size;
public:
    IntSLList() {
        head = tail = 0;
        size = 0;
    }

    void printList();
    void addToHead(int);
    void addToTail(int);
    void addTolistANDsort(int);
    void addToPosition(int, int);
    void removeAllElements(int);
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    void moveToTail(int);

};

void IntSLList :: printList(){
    for (IntSLLNode* p = head ; p != 0 ; p = p->next){
        cout << "\t Element: " << p ->info << endl;
    }
}

void IntSLList :: addToHead(int info){
    IntSLLNode* newnod = new IntSLLNode(info);
    if(head != 0){
        newnod->next = head;
    }
    head = newnod;
    if(tail == 0){
        tail = head;
    }
    size++;
}

void IntSLList :: addToTail(int info){
    IntSLLNode* newnod = new IntSLLNode(info);
    if(tail != 0){
        tail->next = newnod;
    }
    tail = newnod;
    if(head == 0){
        head = tail;
    }
    size++;
}

void IntSLList :: addTolistANDsort(int info){
    IntSLLNode *newnod = new IntSLLNode(info);
    IntSLLNode *p = head;
    if(head == 0 || info <= p->info ){
        addToHead(newnod->info);
        return;
    }
    IntSLLNode *current = head;
    IntSLLNode *prev = 0;
    while(p != 0 && current->info < info){
        prev = current;
        current = current->next;
    }
    newnod->next = prev->next;
    prev->next = newnod;
    size++;
}

void IntSLList ::  addToPosition(int index, int info){
    if (index == 0){
        addToHead(info);
    }
    else if (index >= size){ 
        addToTail(info);
        }
    else{
        IntSLLNode* p = head;
        for(int i = 0 ; i < index - 1; i++){
            p = p->next;
        }
        p->next = new IntSLLNode(info, p);
    }
    size++;
}

int IntSLList :: deleteFromHead(){
    if(head == 0){
        return -1;
    }
    IntSLLNode* del = head;
    int deletedInfo = del->info;
    if(head == tail){
        tail = head = 0;
    }
    else{
        head = head->next;
    }
    delete del;
    size--;
    return deletedInfo;
}

int IntSLList :: deleteFromTail(){
    if(tail == 0){
        return  -1;
    }
    IntSLLNode *del = tail;
    int deletedInfo = del->info;
    if(head == tail){
        head = tail = 0;
    }
    else{
        IntSLLNode* p = head;
        while (p->next != tail) {
            p = p->next;
        }
        tail = p;
        del = p->next;
        tail->next = 0;
    }
    delete  del;
    size--;
    return deletedInfo;
}

void IntSLList :: deleteNode(int info){
    if (head == nullptr)
        return;
    if(head->info == info){
        deleteFromHead();
        return ;
    }
    IntSLLNode* p = head;
    while (p->next != nullptr && p->next->info != info) {
        p = p->next;
    }
    if (p->next == nullptr) {
        return;
    }
    IntSLLNode* d = p->next;
    p->next = d->next;
    if (d == tail) {
        tail = p;
    }
    delete d;
    size--;
    
}

void IntSLList :: removeAllElements(int info){
    while(isInList(info)){
        deleteNode(info);
    }
}

bool IntSLList :: isInList(int info) const{
    IntSLLNode* p = head;
    while (p != nullptr) {
        if(p->info == info){
            return true;
        }
        p = p->next;
    }
    return false;
}

void IntSLList :: moveToTail(int info){
    int index = isInList(info);
    if(index == -1){
        return ;
    }
    deleteNode(info);
    addToTail(info);
}

int main() {
    IntSLList myList;
    IntSLList myListsorted;

    // Adding elements to the list
    myList.addToTail(5);
    myList.addToTail(10);
    myList.addToTail(15);
    myList.addToTail(20);
    myList.addToTail(25);
    myList.addToTail(15);
    myList.addToTail(15);

    // Printing the initial list
    cout << "Initial list:" << endl;
    myList.printList();

    // Removing all occurrences of 15 from the list
    cout << "Removing all occurrences of 15 from the list..." << endl;
    myList.removeAllElements(15);

    // Printing the modified list
    cout << "Modified list:" << endl;
    myList.printList();

    // Deleting the head and tail nodes
    cout << "Deleting the head and tail nodes..." << endl;
    myList.deleteFromHead();
    myList.deleteFromTail();

    // Printing the final list
    cout << "Final list:" << endl;
    myList.printList();

    myListsorted.addTolistANDsort(100);
    myListsorted.addTolistANDsort(50);
    myListsorted.addTolistANDsort(10);
    myListsorted.addTolistANDsort(1);
    myListsorted.addTolistANDsort(3);
    myListsorted.addTolistANDsort(4);
    myListsorted.addTolistANDsort(5);

    cout<<"\n\n___________________________________\n\n"<<endl;
    cout << "new list (100, 50, 10, 1, 3, 4, 5)" << endl;
    myListsorted.printList();

    myListsorted.moveToTail(1);
    cout << "\nAfter moving element 1 to the end"<<endl;
    myListsorted.printList();
    return 0;
}