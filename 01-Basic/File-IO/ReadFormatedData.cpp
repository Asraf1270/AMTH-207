#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Open file
    ifstream readFile("inputReadForData.txt");

    if(!readFile){
        cerr << "Error file opening. " << endl;
    }

    // Read from file
    string name;
    int weight;
    float height;

    readFile >> name >> weight >> height;

    // Output the data
    cout << "Name : " << name << endl;
    cout << "weight :" << weight << endl;
    cout << "Height : " << height << endl;

    // close file
    readFile.close();
    return 0;
}