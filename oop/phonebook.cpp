#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/* 
*PhoneBook -  a class that contains 2 private Parrallel
* dynamic arrays and methods on them.
* @names: user names.
* @phones: phone numbers of users.
* @phoneBookSize: size of both dynamic arrays.
*/
class PhoneBook
{
private:

    string* names;
    string* phones;
    int phoneBookSize;
public:

    void setSize(int);
    void copyPB(const PhoneBook&);
    bool addEntry(string ,string);
    void displayAll();
    bool displayEntryAtIndex(int);
    void displayEntryAtIndices(int*);
    int* findByName(string);
    string findByPhone(string);
    bool updateNameAt(string, int);
    bool updatePhoneAt(string, int);
    void clear();
};

/*
* checkphonenum -  a function that checks if the phone number is
* equal zero and all numbers only no letters for special characters.
* the function is called in add entry.
* @phone:  phone number to be checked
*
* Return: the function returns 1 on success and 0 on failing.
*/
bool checkphonenum(string phone)
{
    if (phone.length() != 11)
    {
        return false; 
    }

    for (char digit : phone)
    {
        if (digit < '0' || digit > '9')
        {
            return false;
        }
    }

    return true;
}

// class methods
void PhoneBook::setSize(int size)
{
    phoneBookSize = size;
    names =  new string[phoneBookSize];
    phones =  new string[phoneBookSize];
}
void PhoneBook::copyPB(const PhoneBook &pb)
{
    names =  new string[phoneBookSize];
    phones =  new string[phoneBookSize];
    phoneBookSize = pb.phoneBookSize;

    for (int i = 0; i < phoneBookSize; i++) 
    {
        names[i] = pb.names[i];
        phones[i] = pb.phones[i];
    }
}

bool PhoneBook::addEntry(string name, string phoneNumber)
{
    if (checkphonenum(phoneNumber))
    {
        for (int i = 0; i < phoneBookSize; i++)
        {
            if (names[i].empty() && phones[i].empty())
            {
                names[i] = name;
                phones[i] = phoneNumber;
                return true;
            }
        }
        cout << "Phone book is full. Cannot add more entries." << endl;
        return false;
    }
    cout << "Enter a valid phone number" << endl;
    return false;
}

void PhoneBook::displayAll()
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (names[i] != "")
        {
            cout << "the name and the phone number of " << (i + 1) << " student is: " << endl;
            cout << "Name: " << names[i] << endl;
            cout << "Phone: " << phones[i] << endl;
        }
    }
}

bool PhoneBook::updateNameAt(string str, int index)
{
    if (index > phoneBookSize || str.empty())
        return false;
    names[index] = str;
    return true;
}

bool PhoneBook::updatePhoneAt(string num, int index)
{
    if (index > phoneBookSize || num.empty())
        return false;
    phones[index] = num;
    return true;
}

bool PhoneBook::displayEntryAtIndex(int index)
{
    if (index > phoneBookSize)
        return false;
    cout<<"name:"<<names[index]<<endl;
    cout<<"number:"<<phones[index]<<endl;
    return true;
}

int* PhoneBook::findByName(string name)
{
    int count = 0; 
    int* check = new int[phoneBookSize]; 

    for (int i = 0; i < phoneBookSize; i++)
    {
        if (names[i] == name)
        {
            check[i] = 1; 
            count++;
        }
        else
        {
            check[i] = 0; 
        }
    }

    if (count == 0)
    {
        cout << "No matching entries found." << endl;
    }

    return check;
}

void PhoneBook::displayEntryAtIndices(int* check)
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (check[i] == 1)
        {
            cout << "name: " << names[i] << endl;
            cout << "phone: " << phones[i] << endl;
        }
    }
}

string PhoneBook::findByPhone(string phone)
{
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (phones[i] == phone)
        {
            displayEntryAtIndex(i);
            return names[i]; 
        }
    }
    cout << "No entry found for phone number: " << phone << endl;
    return "";
}

void PhoneBook::clear()
{
    delete[] names;
    delete[] phones;

    names = nullptr;
    phones = nullptr;
}

/*
* Main - Entry Point
*
* Return: O on (success)
*/
int main()
{
    int size, input;
    int *arr;
    PhoneBook Myphonebook, Myphonebook_copy;
    bool flag = true, check, check2;
    string flagstr, name, phonenumber;
    string update;
    bool check3 = true;
    string check4;
    string name_ser;
    string phone_ser;
    int r;

    cout <<"********************************************" << endl;
    cout <<"*                                          *" << endl;
    cout <<"*             WELCOME TO MY PROGRAM        *" << endl;
    cout <<"*                                          *" << endl;
    cout <<"********************************************" << endl;

    // gets phonebook size
    cout<<"Enter the size of phone book: "<<endl;
    cin>> size;
    Myphonebook.setSize(size);

    // fills the phonebook
    for (int i = 0; i < size; i++)
    {
        cout<< "Enter data for Person no." << (i + 1) <<endl;
        cout << "Name:" << endl;
        cin.ignore();
        getline(cin, name);
        cout << "Phone Number:" << endl;
        cin>> phonenumber;
        check = checkphonenum(phonenumber);
        check2 = Myphonebook.addEntry(name, phonenumber);
        if(!check2 && check)
        {
            cout<<"Failed to add entry!, array is full"<<endl;
            break;
        }
        while (!check)
        {
            cout << "Reenter a newphone number" <<endl;
            cin >>phonenumber;
            check = checkphonenum(phonenumber);
            Myphonebook.addEntry(name, phonenumber);
        }
    }

    // this keeps the program running UNTIL USER TYPES 8 "EXIT"
    while (flag)
    {
        cout << "1- Display all phone book\n"
         << "2- Search for entry/entries by name\n"
         << "3- Search for entry/entries by phone\n"
         << "4- Find an entry by index\n"
         << "5- Update name by index\n"
         << "6- Update phone by index\n"
         << "7- Copy phone book to another and display entries of the new phone book\n"
         << "8- Exit" << endl;
        cin>> input;
        switch (input)
        {
        case 1:
            Myphonebook.displayAll();
            break;
        
        case 2:
            while (check3)
            {
                cout<<"Enter Name you want to search: "<<endl;
                cin>>name_ser;
                arr = Myphonebook.findByName(name_ser);
                Myphonebook.displayEntryAtIndices(arr);
                cout << "do you wanna search for another name?"<<endl;
                cin>>check4;
                 if (check4 == "yes" || check4 == "YES" || check4 == "Yes")
                    check3 = true;
                else
                    check3 = false;
            }
            break;

        case 3:
            while (check3)
            {
                cout<<"Enter phone you want to search: "<<endl;
                cin>>phone_ser;
                Myphonebook.findByPhone(phone_ser);
                cout << "do you wanna search for another number?"<<endl;
                cin>>check4;
                 if (check4 == "yes" || check4 == "YES" || check4 == "Yes")
                    check3 = true;
                else
                    check3 = false;
            }
            break;

        case 4:
            cout<<"Enter the index to search"<<endl;
            cin>>r;
            Myphonebook.displayEntryAtIndex(r);
            break;

        case 5:
            cout<<"Enter the index to update the name"<<endl;
            cin>>r;
            cout<<"Enter the name you want to update"<<endl;
            cin.ignore();
            getline(cin, update);
            Myphonebook.updateNameAt(update, r);
            break;

        case 6:
            cout<<"Enter the index to update the phone number"<<endl;
            cin>>r;
            cout<<"Enter the phone number you want to update"<<endl;
            cin.ignore();
            getline(cin, update);
            Myphonebook.updatePhoneAt(update, r);
            break;
            
        case 7:
            Myphonebook_copy.copyPB(Myphonebook);
            Myphonebook_copy.displayAll();
            break;

        case 8:
            Myphonebook.clear();
            break;

        default:
            break;
        }

        if (input == 8)
        {
            cout <<"********************************************" << endl;
            cout <<"*                                          *" << endl;
            cout <<"*     THANK YOU FOR USING MY PROGRAM       *" << endl;
            cout <<"*                                          *" << endl;
            cout <<"********************************************" << endl;
            break;
        }
        else
        {
            cout<< "if you want to continue type yes"<<endl;
            cin>> flagstr;
            if (flagstr == "yes" || flagstr == "YES" || flagstr == "Yes")
                flag = true;
            else
                flag = false;
        }
    }

Myphonebook.clear();
return 0;
}