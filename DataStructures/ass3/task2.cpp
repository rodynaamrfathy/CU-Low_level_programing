#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

struct Variable{
    string name;
    string datatype;
    string value;
};

class IntSLLNode {
public:
    Variable info;
    IntSLLNode *next;
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(string name, string datatype, string value, IntSLLNode *ptr = 0) {
        info.name = name;
        info.datatype = datatype;
        info.value = value;
        next = ptr;
    }
    void update(string value)
    {
        info.value = value;
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

    Variable top();
    void push(string, string, string);
    Variable  pop();
    bool isEmpty();
    void printList();
    void searchUpdate(string, string);
};

void IntSLLStack :: push(string name, string datatype, string value){
    IntSLLNode* newnod = new IntSLLNode(name, datatype, value);
    if(head != 0){
        newnod->next = head;
    }
    head = newnod;
    if(tail == 0){
        tail = head;
    }
    size++;
}

Variable IntSLLStack :: pop(){
    if(head == 0){
        return Variable();
    }
    IntSLLNode* del = head;
    Variable deletedInfo = del->info;
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

Variable IntSLLStack :: top(){
    if(head == 0) {
        return Variable();
    }
    return (head->info);
}

bool IntSLLStack :: isEmpty(){
    return (size == 0);
}

void IntSLLStack :: printList(){
    for (IntSLLNode* p = head ; p != 0 ; p = p->next){
        cout << "\t name: " << p->info.name << ", ";
        cout << "\t datatype:" << p->info.datatype << ", ";
        cout << "\t value:" << p->info.value << endl;
    }
}

void IntSLLStack :: searchUpdate(string name, string value){
    for (IntSLLNode* p = head ; p != 0 ; p = p->next){
        if(p->info.name == name){
            p->update(value);
            return;
        }
    }
}

string* linetoarray(string line) {
    string* array = new string[3]; // Fixed size, change as needed
    int k = 0;
    string element;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != '\t' && line[i] != '=' && line[i] != ' ' && line[i] != ';') {
            element += line[i];
        } else if (!element.empty()) {
            array[k] = element;
            k++;
            element.clear();
        }
    }
    if (!element.empty() && k < 3) {
        array[k] = element;
    }
    return array;
}

void updateFromFile(string line, IntSLLStack &stackOfVariables){
    string name, value, datatype;
    string datatypesList[] = {"int", "float", "double", "char"};

    string *arrayofcode = linetoarray(line);

    for(int j = 0;  j < 4; j++){
        if(datatypesList[j] == arrayofcode[0]){
            cout << "pushing to stack" <<endl;
            stackOfVariables.push(arrayofcode[1], arrayofcode[0], arrayofcode[2]);
            return;
        }
    }
    
    cout << "updating stack" <<endl;
    stackOfVariables.searchUpdate(arrayofcode[0], arrayofcode[1]);
}

int main()
{
    ifstream readCode("code.txt");
    string line;
    IntSLLStack stackOfVariables;

    if(!readCode){
        cout << "file is not found" <<endl;
        return 1;
    }

    while(getline(readCode, line)){
        if(line == "int main()" || line == "{")
            continue;

        updateFromFile(line, stackOfVariables);

        stackOfVariables.printList();
        cout << "----------------------------------------" <<endl;
        if(line == "return 0;" || line == "}")
            break;
    }

    cout << "end of code reached \'return 0;\'" <<endl;
    cout << "----------------------------------------" <<endl;
    stackOfVariables.printList();
    readCode.close();

    return 0;
}