#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main(){
    //open and create file
    ofstream writeBinary("writeBinary.txt", ios :: binary);

    // checking
    if (!writeBinary) {
        cerr << "Error file opening" << endl;
        return 1;
    } 

    struct Student
    {
        /* data */
        char name[50];
        int roll;
        float mark;
    };

    Student s = {"Md Asraful Islam", 51, 75.6};
    writeBinary.write((char*)&s, sizeof(Student));
    writeBinary.close();
    
    cout << "File writing successfully." << endl;
    return 0;
    
}