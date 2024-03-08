#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <cstring>
#include "Course.h"
using namespace std;

class Student
{
protected:
string name;
int id;
Course *courselist[6];
int noOfCourses, level;
double grades[6];
public:
Student()
{
    for(int i = 0; i < 6; i++)
        *courselist = nullptr;
    noOfCourses = 0;
}
Student(string n, int i)
{
    name = n;
    id = i;
    for(int i = 0; i < 6; i++)
        *courselist = nullptr;
    noOfCourses = 0;
}
void setlevel(int l)
{
    if (l < 5 && l > 0)
        level = l;
    else
        cout<<"enter a valid level" <<endl;
}
int getlevel()
{
    return level;
}
virtual bool RegisterCourse(Course *course)
{
    if(noOfCourses == 6)
    {
        cout<<"you cannot add more course"<<endl;
        return false;
    }
    courselist[noOfCourses] = new Course();
    courselist[noOfCourses]->setname(course->getname());
    courselist[noOfCourses]->setCreditHours(course->getCreditHours());
    courselist[noOfCourses]->setMinStudentLevel(course->getMinStudentLevel());
    courselist[noOfCourses]->setcode(course->getcode());
    cout<<"Enter the grade of the course\t"<<courselist[noOfCourses]->getname()<<endl;
    cin>>grades[noOfCourses];
    noOfCourses++;
    return true;
}
virtual float CalculateExpenses() = 0;
void printRegisteredCourses()
{
    for(int i = 0; i < noOfCourses; i++)
    {
        cout<<"COURSE "<< i+1 <<":"<<endl;
        cout<<courselist[i];
        cout<<"Grade:"<<grades[i]<<endl;
    }
}
double getTotalGPA()
{
    int totalcredithours = 0;
    double totalGPA;
    for(int i = 0; i < noOfCourses; i++)
    {
        totalcredithours += courselist[i]->getCreditHours();
        totalGPA += (getCourseGPA(grades[i]) * courselist[i]->getCreditHours());
    }
    totalGPA /= totalcredithours;
    return totalGPA;
}
string getname()
{
    return name;
}
int getid()
{
    return id;
}
double getCourseGPA(double percentage)
{
    if (percentage <= 100 && percentage >= 98)
    {
        return 4.00;
    }
    else if (percentage <= 97 && percentage >= 93)
    {
        return 4.00;
    }
    else if (percentage <= 92 && percentage >= 90)
    {
        return 3.70;
    }
    else if (percentage <= 89 && percentage >= 87)
    {
        return 3.30;
    }
    else if (percentage <= 86 && percentage >= 83)
    {
        return 3.00;
    }
    else if (percentage <= 82 && percentage >= 80)
    {
        return 2.70;
    }
    else if (percentage <= 79 && percentage >= 77)
    {
        return 2.30;
    }
    else if (percentage <= 76 && percentage >= 73)
    {
        return 2.00;
    }
    else if (percentage <= 72 && percentage >= 70)
    {
        return 1.70;
    }
    else if (percentage <= 69 && percentage >= 67)
    {
        return 1.30;
    }
    else if (percentage <= 66 && percentage >= 63)
    {
        return 1.00;
    }
    else if (percentage <= 62 && percentage >= 60)
    {
        return 0.70;
    }
    else if (percentage < 60)
    {
        return 0.00;
    }
    else
        return 0;
    return 0;
}
};

#endif