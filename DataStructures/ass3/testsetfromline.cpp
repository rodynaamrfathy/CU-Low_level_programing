#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

/*void setfromline(string line,string &data,string delimiter){
    bool foundDelimiter;
    for(int i = 0; line[i] != '\0'; i++){
        foundDelimiter = false;
        for(int j = 0; delimiter[j] != '\0'; j++){
            if(line[i] == delimiter[j]){
                foundDelimiter = true;
                break;
            }
        }
        if (!foundDelimiter) {
           data += line[i];
        }
        else
            break;  
    }
}
int main(){
    string data;
    setfromline("x = 9", data, "\" = ");
    cout << "Data: \"" << data << endl;
    setfromline("x = 9", data, "\" = ");
    cout << "Data: \"" << data << endl;
}*/


#include <iostream>
#include <string>

using namespace std;

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

int main() {
    string line = "\t x = 10;"; // Example input line
    string* result = linetoarray(line);
    for (int i = 0; i < 3; i++) {
        cout << result[i] << endl;
    }
    delete[] result; // Don't forget to free the memory
    return 0;
}
