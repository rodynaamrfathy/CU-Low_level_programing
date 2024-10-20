#include <iostream>
#include <cstdlib>
#include <string>
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


class IntSLLStack{
private:
    IntSLLNode *head;
    IntSLLNode *tail;
    int size;
public:
    IntSLLStack() {
        head = tail = 0;
        size = 0;
    }

    int top();
    void push(int);
    int  pop();
    bool isEmpty();
    bool isTrue();
};

void IntSLLStack :: push(int info){
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

int IntSLLStack :: pop(){
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

int IntSLLStack :: top(){
    if(head == 0) {
        return -1;
    }
    return (head->info);
}

bool IntSLLStack :: isEmpty(){
    return ( size == 0);
}

bool checkBrackets(const string expression) {
    IntSLLStack stack;
    bool isbalanced = true;
    int i = 0;
    while (isbalanced && expression[i] != '\0') {
        char c = expression[i];
        switch (c) {
            case '(': case '{': case '[':
                stack.push(c);
                break;
            case ')':
                if (stack.isEmpty() || stack.pop() != '(') {
                    isbalanced = false;
                }
                break;
            case '}':
                if (stack.isEmpty() || stack.pop() != '{') {
                    isbalanced = false;
                }
                break;
            case ']':
                if (stack.isEmpty() || stack.pop() != '[') {
                    isbalanced = false;
                }
                break;
        }
        i++;
    }
    if (!stack.isEmpty()) {
        isbalanced = false;
    }
    return isbalanced;
}


/*int stackaddition(){

}*/

int main(){
    string  exp1 = "{[()]}";
    cout << ((checkBrackets(exp1)) ? "Balanced" : "Not Balanced" )<< endl;
    
    string  exp2 = "{aaa";
    cout << ((checkBrackets(exp1)) ? "Balanced" : "Not Balanced" )<< endl;
}