#include <iostream>
#include <string>
#include <cstring>
#include "Course.h"
#include "SummerCourse.h"
#include "NormalCourse.h"
#include "Student.h"
#include "SpecialStudent.h"
#include "GeneralStudent.h"
using namespace std;

Course* COURSES[] = 
{
new NormalCourse("Math", 1, 2),
new NormalCourse("Programming_1", 1, 3),
new NormalCourse("Technical_Writing", 1, 3), 
new NormalCourse("Electronics", 2, 4),
new NormalCourse("Data_Structures", 2, 3), 
new NormalCourse("OOP", 2, 3),
new NormalCourse("Algorithms", 3, 2),
new NormalCourse("Operating_Systems", 3, 3), 
new NormalCourse("Databases", 3, 3),
new NormalCourse("Machine_Learning", 4, 3),
new NormalCourse("Compilers", 4, 4),
new NormalCourse("Programming_Concepts", 4, 4), 
new SummerCourse("Math", 1, 2),
new SummerCourse("Compilers", 4, 4),
new SummerCourse("Algorithms", 3, 2),
new SummerCourse("OOP", 2, 3)
};
Course* searchCourse(string code);
void printCourseList();

int main()
{
    int users, id, coursesno, level;
    Student **arr = new Student*[users];
    string type, name, coursecode, ask, anothercourse;
    Course *Coursetoregister;
    bool flag = true, flag2;

    cout<<"****************************"<<endl;
    cout<<"* the no. number of users: *"<<endl;
    cout<<"****************************"<<endl;
    cin>>users;
    for(int i = 0; i < users; i++)
    {
        cout<<"*********************************"<<endl;
        cout<<"* enter type Special or General *"<<endl;
        cout<<"*********************************"<<endl;
        cin>>type;
        cout<<"***********************"<<endl;
        cout<<"* enter student name: *"<<endl;
        cout<<"***********************"<<endl;
        cin>>name;
        cout<<"*********************"<<endl;
        cout<<"* enter student id: *"<<endl;
        cout<<"*********************"<<endl;
        cin>>id;
        cout<<"************************"<<endl;
        cout<<"* enter student level: *"<<endl;
        cout<<"************************"<<endl;
        cin>>level;
        while (level < 1 || level > 4)
        {
            cout<<"**************************"<<endl;
            cout<<"* Reenter student level: *"<<endl;
            cout<<"**************************"<<endl;
            cin>>level;
        }
        if(type == "Special" || type == "special")
        {
            arr[i] = new SpecialProgramStudent(name, id);
            arr[i]->setlevel(level);
        }
        else if(type == "General" ||type == "general")
        {
            arr[i] = new GeneralProgramStudent(name, id);
            arr[i]->setlevel(level);
        }
    }
    cout<<"**********************************"<<endl;
    cout<<"* Welcome to registering courses *"<<endl;
    cout<<"**********************************"<<endl;
    for (int i = 0; i < users; i++)
    {
        flag = true;
        cout<<"***************************"<<endl;
        cout<<"* Avaliable courses list: *"<<endl;
        cout<<"***************************"<<endl;
        printCourseList();
        while (flag)
        {
            cout<<"Enter the number of courses for student "<<arr[i]->getname()<< ": "<<endl;
            cin>> coursesno;
            if (coursesno <= 6)
            {
                flag = false;
                for (int j = 0; j < coursesno ;j++)
                {
                    Coursetoregister = nullptr;
                    cout<<"*****************************************************************"<<endl;
                    cout<<"* Enter course code (coursename_Nlevel) or (coursename_Slevel): *"<<endl;
                    cout<<"*****************************************************************"<<endl;
                    cin>>coursecode;
                    Coursetoregister = searchCourse(coursecode);
                    if(Coursetoregister != nullptr)
                    {
                        flag2 = arr[i]->RegisterCourse(Coursetoregister);
                        while(!flag2)
                        {
                            cout<<"do you want to register another course? ans by yes or no:";
                            cin>>anothercourse;
                            if (anothercourse == "YES" || anothercourse == "yes" || anothercourse == "Yes")
                            {
                                break;
                            }
                            else if (anothercourse == "NO" || anothercourse == "no" || anothercourse == "No")
                            {
                                coursesno --;
                                flag2 = true;
                                cout<<" !!!! you now will have "<< coursesno - 1<<" course(s) !!!! "<<endl;
                            }
                            else
                                cout<<"reenter an ans!!"<<endl;
                        }
                    }
                    while (Coursetoregister == nullptr || !flag2)
                    {
                        cout<<"************************"<<endl;
                        cout<<"* Reenter course code *"<<endl;
                        cout<<"************************"<<endl;
                        cin>>coursecode;
                        Coursetoregister = searchCourse(coursecode);
                        if (Coursetoregister != nullptr)
                        {
                            flag2 = arr[i]->RegisterCourse(Coursetoregister);
                        }
                    }
                }
            }
            else
            {
                flag = true;
                cout<<" !!! you can only register up to 6 courses !!!"<<endl;
            }
        }
    }
    cout<<"______________________________________________"<<endl;
    cout<< "Total Number of students:" <<users<<endl;
    for(int i = 0; i < users; i++)
    {
        cout<<"Student Name:"<<arr[i]->getname()<<endl;
        cout<<"ID:"<<arr[i]->getid()<<endl;
        cout<<"Level:"<<arr[i]->getlevel()<<endl;
        cout<<"Registered Courses:"<<endl;
        arr[i]->printRegisteredCourses();
        cout<<"Overall GPA:"<<arr[i]->getTotalGPA()<<endl;
        cout<<"Student Expenses:"<<arr[i]->CalculateExpenses()<<endl;
    }
    return 0;
}

Course* searchCourse(string code)
{
    for(int i = 0; i < 16 ; i++)
    {
        if(COURSES[i]->getcode() == code)
        {
            return COURSES[i];
        }
    }
    cout<<"code not found"<<endl;
    return nullptr;
}
void printCourseList()
{
    for(int i = 0; i < 16 ; i++)
    {
        cout<<"* "<<COURSES[i]->getname()<< ": ";
        cout<<COURSES[i]->getcode()<<endl;
    }
}
