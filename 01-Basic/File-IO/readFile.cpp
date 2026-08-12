#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream readFile("example.txt");

    // Check file openning
    if (!readFile) {
        cerr << "Error file openning" << endl;
        return 1;
    }

    // read file
    string line;
    cout << "Reading file content" << endl;
    cout << "--------------------" << endl;

    // Method-1: line by line
    while (getline(readFile, line)){
        cout << line << endl;
    }

    readFile.close();
    return 0;
}