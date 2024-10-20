#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

void setfromline(const string& line, string& data, const string& delimiters) {
    // Finds the first non-delimiter character to start the value
    size_t start = line.find_first_not_of(delimiters);
    if (start == string::npos) return; // No valid start

    // Finds the first delimiter after the valid start to end the value
    size_t end = line.find_first_of(delimiters, start);
    if (end == string::npos) {
        data = line.substr(start);
    } else {
        data = line.substr(start, end - start);
    }
}

struct Variable {
    string name;
    string datatype;
    string value;
};

class IntSLLNode {
public:
    Variable info;
    IntSLLNode* next;
    
    IntSLLNode() : next(nullptr) {}
    
    IntSLLNode(const string& name, const string& datatype, const string& value, IntSLLNode* ptr = 0) {
        info.name = name;
        info.datatype = datatype;
        info.value = value;
        next = ptr;
    }
    
    void update(const string& value) {
        info.value = value;
    }
};

class IntSLLStack {
private:
    IntSLLNode* head;
    IntSLLNode* tail;
    int size;

public:
    IntSLLStack() : head(nullptr), tail(nullptr), size(0) {}

    Variable top() {
        if (head == nullptr) {
            return Variable();
        }
        return head->info;
    }

    void push(const string& name, const string& datatype, const string& value) {
        IntSLLNode* newNode = new IntSLLNode(name, datatype, value);
        if (head != nullptr) {
            newNode->next = head;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
        size++;
    }

    Variable pop() {
        if (head == nullptr) {
            return Variable();
        }
        IntSLLNode* del = head;
        Variable deletedInfo = del->info;
        if (head == tail) {
            tail = head = 0;
        } else {
            head = head->next;
        }
        delete del;
        size--;
        return deletedInfo;
    }

    bool isEmpty() {
        return (size == 0);
    }

    void printList() {
        for (IntSLLNode* p = head; p != 0; p = p->next) {
            cout << "\tname: " << p->info.name << ", ";
            cout << "\tdatatype: " << p->info.datatype << ", ";
            cout << "\tvalue: " << p->info.value << endl;
        }
    }

    void searchUpdate(const string& name, const string& value) {
        for (IntSLLNode* p = head; p != 0; p = p->next) {
            if (p->info.name == name) {
                p->update(value);
                return;
            }
        }
        // If not found, push as a new variable with unknown datatype
        push(name, "unknown", value);
    }
};

void updateFromFile(const string& line, IntSLLStack& stackOfVariables) {
    string delimiters = " =;";
    string name, value, datatype;

    setfromline(line, datatype, delimiters);

    const string datatypesList[] = {"int", "float", "double", "char"};

    // Check if the first extracted data is a known datatype
    bool isDatatype = false;
    for (const auto& dt : datatypesList) {
        if (datatype == dt) {
            isDatatype = true;
            break;
        }
    }

    if (isDatatype) {
        setfromline(line, name, delimiters); // Extract the variable name
        setfromline(line, value, delimiters); // Extract the variable value
        stackOfVariables.push(name, datatype, value); // Push to stack
    } else {
        name = datatype; // First data might be the name if not a datatype
        setfromline(line, value, delimiters); // Get value
        stackOfVariables.searchUpdate(name, value); // Update in stack
    }
}

int main() {
    ifstream readCode("code.txt");
    if (!readCode) {
        cout << "File not found" << endl;
        return 1;
    }

    string line;
    IntSLLStack stackOfVariables;

    while (getline(readCode, line)) {
        if (line == "int main()" || line == "{") {
            continue; // Skip unnecessary lines
        }

        updateFromFile(line, stackOfVariables);

        stackOfVariables.printList(); // Print current stack

        if (line == "return 0;" || line == "}") {
            break; // End loop if it's the end of the main function
        }
    }

    cout << "End of code reached 'return 0;'" << endl;
    cout << "----------------------------------------" << endl;

    stackOfVariables.printList(); // Print final stack state

    readCode.close(); // Close the file

    return 0;
}