#ifndef GENERALSTUDENT_H
#define GENERALSTUDENT_H

#include <iostream>
#include <string>
#include <cstring>
#include "Course.h"
#include "Student.h"
using namespace std;

class GeneralProgramStudent : public Student
{
public:
GeneralProgramStudent() : Student()
{}
GeneralProgramStudent(string n, int i) : Student(n, i)
{

}
bool RegisterCourse(Course *course)
{
    //int l = getlevel();
    if (level >= course->getMinStudentLevel())
    {
        Student :: RegisterCourse(course);
    }
    else
    {
        cout<<"this course is not available for you and won't be registred"<<endl;
        return false;
    }
    return true;
}
float CalculateExpenses()
{
    int l = getlevel();
    return l * 1000;
}
};

#endif