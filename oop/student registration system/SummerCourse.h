#ifndef SUMMERCOURSE_H
#define SUMMERCOURSE_H

#include <iostream>
#include <string>
#include <cstring>
#include "Course.h"
using namespace std;

class SummerCourse : public Course
{
public:
SummerCourse()
{

}
SummerCourse(string n, int l, int c) : Course(n, l, c)
{
    //intialize normal code
    string summercode;
    summercode = getname() + "_S" + to_string(getMinStudentLevel());
    setcode(summercode);
}
string getcode()
{
    return Course :: getcode();
}
};

#endif