#include <iostream>
#include <cstdlib>
using namespace std;

class IntDLLNode {
public:
    int info;
    IntDLLNode *prev;
    IntDLLNode *next;
    IntDLLNode() {
        prev = 0;
        next = 0;
    }
    IntDLLNode(int el, IntDLLNode *next = 0, IntDLLNode *prev = 0) {
        info = el; this->next = next; this->prev = prev;
    }
};


class IntDLList{
private:
    IntDLLNode *head;
    IntDLLNode *tail;
    int size;
public:
    IntDLList() {
        head = tail = 0;
        size = 0;
    }

    void printList();
    void addToHead(int);
    void addToTail(int);
    //void addTolistANDsort(int);
    void addToPosition(int, int);
    void removeAllElements(int);
    void  deleteFromHead(); // delete the head and return its info;
    void  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    //void moveToTail(int);
    void reverseList();
    IntDLLNode* findMiddleElement();
    void mergeSortedLists(IntDLList& list);
    void removeDuplicates();
    void splitListInHalf(IntDLList& firstHalf, IntDLList& secondHalf);
    void rotateList(int k);
    void insertionSort();
    void swapNodes(int index1, int index2);

};

void IntDLList :: printList(){
    for (IntDLLNode* p = head ; p != 0 ; p = p->next){
        cout<< "\t Element: " << p ->info <<endl;
    }
}
void IntDLList :: addToHead(int info){
    IntDLLNode* newnod = new IntDLLNode(info);
    if(head != 0){
        newnod->next = head;
    }
    head = newnod;
    if(tail == 0){
        tail = newnod;
    }
    size++;
}
void IntDLList :: addToTail(int info){
    IntDLLNode* newnod = new IntDLLNode(info);
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
void IntDLList :: addToPosition(int info, int index){
    if (index == 0){
        addToHead(info);
    } else if (index >= size){ 
        addToTail(info);
    } else{
        IntDLLNode* p = head;
        for(int i = 0 ; i < index - 1; i++){
            p = p->next;
        }
        IntDLLNode *newnod= new IntDLLNode(info, p->next, p);
        p->next->prev = newnod;
        p->next = newnod;
        size++;
    }
}
void IntDLList :: deleteFromHead(){
    if(head == 0) return;
    IntDLLNode* temp = head;
    if(head == tail){
        head = tail = 0;
    }else{
        head = head->next;
        if (head != nullptr) // Check if the new head exists
            head->prev = nullptr;
    }
    delete temp;
    size--;
}
void IntDLList :: deleteFromTail(){
    if(head == 0) return;
    IntDLLNode* temp = tail;
    if(head != tail){
        tail = tail->prev;
        tail->next = 0;
    }
    delete temp;
    size--;
}
void IntDLList :: deleteNode(int info){
    if (head == nullptr)
        return;
    if(head->info == info){
        deleteFromHead();
        return ;
    }
    IntDLLNode* p = head;
    while (p->next != nullptr && p->next->info != info) {
        p = p->next;
    }
    if (p->next == nullptr) {
        return;
    }
    IntDLLNode* d = p->next;
    p->next = d->next;
    if (d->next != nullptr){
        d->next->prev = p;
    }
    if (d == tail) {
        tail = p;
    }
    delete d;
}
void IntDLList :: removeAllElements(int info){
    while(isInList(info)){
        deleteNode(info);
    }
}
bool IntDLList :: isInList(int info) const{
    IntDLLNode* p = head;
    while (p != nullptr) {
        if(p->info == info){
            return true;
        }
        p = p->next;
    }
    return false;
}

/*
the algorithm is to swap the head with tail
now the prev node is supposed to be the next node
and so on so i will swap the address of next and prev 
of every node
*/ 
void IntDLList::reverseList() {
    if (head == nullptr || head == tail) 
        return;

    IntDLLNode* current = head;
    IntDLLNode* temp = nullptr;

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




int main() {
    IntDLList myList;

    // Testing addToHead and addToTail
    myList.addToHead(1);
    myList.addToHead(2);
    myList.addToTail(3);
    myList.addToTail(4);
    myList.addToHead(2);
    myList.addToTail(3);
    myList.addToTail(2);
    cout << "Original list:" << endl;
    myList.printList();

    // Testing deleteFromHead and deleteFromTail
    myList.deleteFromHead();
    myList.deleteFromTail();
    cout << "List after deleting from head and tail:" << endl;
    myList.printList();

    // Testing addToPosition
    myList.addToPosition(5, 1);
    cout << "List after adding 5 at position 1:" << endl;
    myList.printList();

    // Testing deleteNode
    myList.deleteNode(5);
    cout << "List after deleting node with value 5:" << endl;
    myList.printList();

    // Testing removeAllElements
    myList.removeAllElements(2);
    cout << "List after removing all elements with value 2:" << endl;
    myList.printList();

    // Testing reverseList
    cout << "Reversed list:" << endl;
    myList.reverseList();
    myList.printList();

    // Testing isInList
    cout << "Is 3 in the list? " << (myList.isInList(3) ? "Yes" : "No") << endl;
    cout << "Is 6 in the list? " << (myList.isInList(6) ? "Yes" : "No") << endl;

    return 0;
}

