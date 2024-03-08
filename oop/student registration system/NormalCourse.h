#ifndef NORMALCOURSE_H
#define NORMALCOURSE_H

#include <iostream>
#include <string>
#include <cstring>
#include "Course.h"
using namespace std;

class NormalCourse : public Course
{
public:
NormalCourse()
{

}
NormalCourse(string n, int l, int c) : Course(n, l, c)
{
    //intialize normal code
    string normalcode;
    normalcode = getname() + "_N" + to_string(getMinStudentLevel());
    setcode(normalcode);
}
string getcode()
{
    return Course :: getcode();
}
};

#endif