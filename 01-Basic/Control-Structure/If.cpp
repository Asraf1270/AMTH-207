#include <iostream>

using namespace std;

int main(){
    int age;
    cout << "Enter you age" << endl;
    cin >> age;
    if(age < 18){
        cout << "You are an teeneger" << endl;
    }
    else{
        cout << "You are an adult" << endl;
    }

    return 0;
}