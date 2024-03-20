clude <iostream>
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
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
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
        head->prev = 0;
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
bool IntDLList :: isInList(int info){
    IntDLLNode* p = head;
    while (p != nullptr) {
        if(p->info == info){
            return true;
        }
        p = p->next;
    }
    return false;
}
