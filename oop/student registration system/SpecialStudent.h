#ifndef SPECIALSTUDENT_H
#define SPECIALSTUDENT_H

#include <iostream>
#include <string>
#include <cstring>
#include "Course.h"
#include "Student.h"
using namespace std;

class SpecialProgramStudent : public Student
{
public:
SpecialProgramStudent() : Student()
{

}
SpecialProgramStudent(string n, int i) : Student(n, i)
{

}
bool RegisterCourse(Course *course)
{
    Student :: RegisterCourse(course);
    return true;
}
float CalculateExpenses()
{
    int totalcredithours = 0;
    for(int i = 0; i < noOfCourses; i++)
    {
        totalcredithours += courselist[i]->getCreditHours();
    }
    return totalcredithours * 500;
}
};

#endif