#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <cstring>
using namespace std;


class Course
{
private:
    string name, code;
    int MinStudentLevel, CreditHours;
public:
    Course()
    {

    }
    Course(string name, int MinStudentLevel, int CreditHours)
    {
        this->name = name;
        this->MinStudentLevel = MinStudentLevel;
        this->CreditHours = CreditHours;
    }
    string getname()
    {
        return name;
    }
    virtual string getcode()
    {
        return code;
    }
    int getMinStudentLevel()
    {
        return MinStudentLevel;
    }
    int getCreditHours()
    {
        return CreditHours;
    }
    void setcode(string c)
    {
        code = c;
    }
    void setname(string n)
    {
        name = n;
    }
    void setMinStudentLevel(int num)
    {
        MinStudentLevel = num;
    }
    void setCreditHours(int num)
    {
        CreditHours = num;
    }
    friend ostream& operator<<(ostream &out, const Course &obj);
};

ostream& operator<<(ostream &out, Course* obj)
{
    out<< "\t" <<"Course name:"<<obj->getname()<<endl;
    out<< "\t"<<"Course code:"<<obj->getcode()<<endl;
    out<< "\t"<<"Course MinStudentLevel:"<< obj->getMinStudentLevel()<<endl;
    out<< "\t"<<"Course CreditHours:"<< obj->getCreditHours()<<endl;
    return out;
}

#endif