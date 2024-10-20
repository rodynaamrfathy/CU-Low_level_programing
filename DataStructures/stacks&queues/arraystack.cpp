#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

template <class T>
class Stack{
private:
    int array[MAX_SIZE];
    int top_index;

public:
    Stack(){
        top_index = -1;
    }
    bool isEmpty();
    bool isFull();
    void push(int);
    int pop();
    int top();
};
template <class T>
bool Stack<T> :: isEmpty(){
    return (top_index == -1);
}
template <class T>
bool Stack<T> :: isFull(){
    return (top_index >= MAX_SIZE - 1);
}
template <class T>
void Stack<T> :: push(int value){
    if(isFull()) {
        cout << "Stack overflow" << endl;
        return;
    }
    array[++top_index] = value;
}
template <class T>
int Stack<T> :: pop(){
    int top_element =  array[top_index];
    top_index--;
    return top_element;
}
template <class T>
int Stack<T> :: top(){
    if(isEmpty()){
        exit(-1);
    }
    return (array[top_index]);
}

int main() {
    Stack<int> stack;
    Stack<char> revString;
    string  str;
    int i = 0;

    // Push some elements onto the stack
    stack.push(100);
    stack.push(90);
    stack.push(80);
    stack.push(70);
    stack.push(60);
    stack.push(50);
    stack.push(40);

    // Print and remove elements from the stack
    cout << "Popped element: " << stack.pop() << std::endl;
    cout << "Popped element: " << stack.pop() << std::endl;

    // Peek at the top element
    cout << "Top element: " << stack.top() << std::endl;

    // take a string as an input and reverse it with a stack
    cout<<"Type a string to print in reverse using a stack"<<endl;
    getline(cin, str);
    while(str[i] != '\0'){
        revString.push(str[i++]);
    }
    while(!revString.isEmpty()){
        cout<<revString.pop();
    }
    cout<<endl;
    return 0;
}