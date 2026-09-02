#include <iostream>

using namespace std;
int main(){
    int score;
    char grade;

    cout << "Enter your score" << endl;
    cin >> score;

    if (score >= 70){
        cout << "Your grade is A" << endl;
    }
    else if (score >= 50){
        cout << "Your grade is B" << endl;
    }
    else if(score >= 40){
        cout << "Your grade is C" << endl;
    }
    else{
        cout << "Your grade is F"<< endl;
    }
}