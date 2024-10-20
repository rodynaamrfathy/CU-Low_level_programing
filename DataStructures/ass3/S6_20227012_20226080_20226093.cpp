#include <iostream>
#include <fstream>
using namespace std;

//TASK 1
class Patient {
public:
    string name;
    int age;
    string condition;
    int priority;

    Patient(){
        this->name="" ;
        this->age=0;
        this->condition="";
        this->priority=0;
    }

    Patient (string name,int age,int priority) {
        this->name=name;
        this->age=age;
        this->condition="";
        this->priority=priority;
    }
};

class Node {
public:
    Patient patient;
    Node* next;

    Node(Patient p,Node* n=0){
        patient=p ;
        next=n;
    }
};

class PriorityQueue {
public:
    Node* front;

    PriorityQueue (){
       front=0;
    }

    void ConditionOfPatient (Node* node) {
        if (node->patient.priority == 3) {
        node->patient.condition = "critical";}
        else if (node->patient.priority == 2) {
        node->patient.condition = "urgent";}
        else {
        node->patient.condition = "normal";}
    }

    void AddPatient (Patient p) {
        Node* newnode=new Node(p);
        ConditionOfPatient(newnode);
        if (front==NULL || front->patient.priority < p.priority) {
            newnode->next=front ;
            front=newnode ;}
        else{
           Node* current=front;
           while(current->next != NULL && current->next->patient.priority >= p.priority) {
             current=current->next;
        }
        newnode->next=current->next;
        current->next=newnode;}

    }

    void ProcessPatient () {
        if(front == NULL)
            cout<<"there are no patients to remove"<<endl;
        else{
        Node* delptr=front;
        front=front->next;
        cout<<"processing patient..."<< endl;
        cout <<"processing patient: "<<delptr->patient.name<<" (priority: "<<delptr->patient.priority<<
        ")"<<endl;
        delete delptr;
        Display();}
    }

   void UpdatePatient(Patient p, int priority) {

     Node* current = front;
     Node* previous = NULL;

    while (current != NULL && current->patient.name != p.name) {
        previous = current;
        current = current->next;
    }

    if (current->patient.priority == priority) {
        cout << current->patient.name << "'s condition is still the same" << endl;
        return;
    }

    current->patient.priority = priority;
    ConditionOfPatient(current);

    if (previous != NULL) {
        previous->next = current->next;
    } else {
        front = current->next;
    }

    Node* current_point = front;
    Node* previous_point = NULL;

    while (current_point != NULL && current_point->patient.priority >= priority) {
       previous_point = current_point;
        current_point = current_point->next;
    }

    if (previous_point == NULL) {
        current->next = front;
        front = current;
    } else {
        previous_point->next = current;
        current->next = current_point;
           }

     cout<<"Priority of patient " <<current->patient.name<<" updated to "<<current->patient.priority<<endl;
     Display();


    }

    int SizeOfQueue () {
        Node* current=front;
        int counter=0;
        while(current != NULL) {
            counter++;
            current=current->next;
        }
        cout << "the size of the queue is " <<counter<<endl;
        return counter;
    }

    void Display () {
        if(front == NULL)
            cout<<"there are no patients to display"<<endl;
        else{
        Node* current=front;
        cout<<"Current Patients in the Queue:"<<endl;
        while(current != NULL) {
            cout <<"Name: " <<current->patient.name << ", Age: " <<current->patient.age<<
            ", Condition: "<<current->patient.condition<<", Priority: "<<current->patient.priority<<endl ;
            current=current->next;

        } }
    }

    string FrontName () {
        if(front == NULL){
            string error="The queue is empty";
            throw error;}
        return front->patient.name;
    }


};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//TASK 2
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
        cout << "\t datatype:" << p->info.datatype << ",  ";
        cout << "\t value:" << p->info.value << endl;
    }
}

void IntSLLStack :: searchUpdate(string name, string value){
    IntSLLStack tempStack;
    bool found = false;

    while (!isEmpty()) {
        Variable var = pop();
        if (var.name == name) {
            var.value = value;
            found = true;
        }
        tempStack.push(var.name, var.datatype, var.value);
    }
    
   
    if (!found) {
        while (!tempStack.isEmpty()) {
            Variable var = tempStack.pop();
            push(var.name, var.datatype, var.value);
        }
        return;
    }
    
   
    while (!tempStack.isEmpty()) {
        Variable var = tempStack.pop();
        push(var.name, var.datatype, var.value);
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

    string datatypesList[] = {"int", "float", "double", "char"};

    string *arrayofcode= linetoarray(line);

    for(int j = 0;  j < 4; j++){
        if(datatypesList[j] == arrayofcode[0]){
            cout << "pushing to stack" <<endl;
            stackOfVariables.push(arrayofcode[1], arrayofcode[0], arrayofcode[2]);
            stackOfVariables.printList();
            cout << "----------------------------------------" <<endl;
            return;
        }

    }
    if(arrayofcode[0] == "return" || arrayofcode[0] == " " )
    {
        return;
    }    
      cout << "updating stack" <<endl;
      stackOfVariables.searchUpdate(arrayofcode[0], arrayofcode[1]);
      stackOfVariables.printList();
      cout << "----------------------------------------" <<endl;
    


}

void printVariable(Variable var)
{
    cout << "\t name: " << var.name << ", ";
    cout << "\t datatype:" << var.datatype << ",  ";
    cout << "\t value:" << var.value << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int TASK;
    cout<<"enter 1 to run task 1 or 2 to run task2"<<endl;
    cin>>TASK;
    if(TASK == 2)
    {
        ifstream readCode("code.txt");
        string line;
        IntSLLStack stackOfVariables;
        Variable var;

        if(!readCode){
            cout << "file is not found" <<endl;
            return 1;
        }
    
        while(getline(readCode, line)){
            if(line == "int main()" || line == "{")
                continue;

            if(line == "return 0;" || line == "}")
                break;

            updateFromFile(line, stackOfVariables);
            
        }

        cout << "end of code reached \'return 0;\'" <<endl;
        cout << "----------------------------------------" <<endl;

        while(!stackOfVariables.isEmpty())
        {
            var = stackOfVariables.pop();
            printVariable(var);
        }
        cout << "Stack is popped" <<endl;
        cout << "----------------------------------------" <<endl;
        readCode.close();
    }
    if (TASK == 1)
    {
         int number;
        string name;
        int age;
        int priority;
        PriorityQueue q;
        cout<<"enter the number of patients: " ;
        cin>>number;
        Patient p[number];
        for(int i=0;i<number;i++) {
            cout<<"enter patient: "<<i+1<<endl;
            cout<<"name: " ;
            cin>>name;
            cout<<"age: " ;
            cin>>age ;
            cout<<"priority(1,2,3): " ;
            cin>>priority ;
            cout<<endl;
            p[i]=Patient(name,age,priority);
            q.AddPatient(p[i]);
        }
        for(int i=0;i<number;i++) {
                cout <<"patient "<<p[i].name<<" added to the queue"<< endl;
            }
            cout<<endl;
            q.Display();
            cout<<endl;
            int n;
            while(n != 0){
            cout<<"Enter:"<<endl;
            cout<<"0 to exit or 1 to remove patient or 2 to update patient or 3 to get the size of the queue or 4 to get the front name : ";
            cin>> n;
            switch(n){
            case 0:{
                cout<<"the program exited";
                return 0;}
            case 1: {
                q.ProcessPatient();
                cout<<endl;
                break;}
            case 2: {
                cout<<"enter the name of the patient and his updated priority: ";
                string NameOfThePatient;
                int PriorityOfThePatient;
                cin>>NameOfThePatient;
                cin>>PriorityOfThePatient;
                Patient* target=NULL;
                for(int i=0;i<number;i++) {
                    if(NameOfThePatient == p[i].name)
                        target = &p[i];}
                if (target != NULL)
                    q.UpdatePatient(*target,PriorityOfThePatient);
                else
                    cout << "Patient "<< NameOfThePatient << " isnot found in the queue" << endl;
                cout<<endl;
                break;}
            case 3: {
                q.SizeOfQueue();
                cout<<endl;
                break;}
            case 4: { try{
                cout<<"Front Patient Name: " << q.FrontName()<<endl ;
                cout<<endl;}
                catch(string e) {
                cout<<e<<endl ;
                cout<<endl;}
                break;}
            default:
                cout<<"wrong choice"<<endl;
                cout<<endl;
                }
                }
    }
    return 0;
}