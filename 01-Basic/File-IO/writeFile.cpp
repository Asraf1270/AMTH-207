#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    // Open or create file
    ofstream writeFile("example.txt");

    // check open
    if (!writeFile) {
        cerr << "Error file opening" << endl;
        return 1;
    }

    // Write to file
    writeFile << "Hello, file I/O" << endl;
    writeFile << "Line 2 : Learning C++" << endl;
    writeFile << "Line 3 : " << 51 << endl;

    // Close file
    writeFile.close();

    cout << "File writting successfully" << endl;
    return 0;

}
