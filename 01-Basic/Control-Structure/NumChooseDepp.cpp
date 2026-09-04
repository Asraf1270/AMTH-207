#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess, attempts = 0;
    
    cout << "🎯 Guess the number (1-100): " <<endl;
    
    do {
        cin >> guess;
        attempts++;
        
        if (guess == secret) {
            cout << "🎉 Correct! You got it in " << attempts << " attempts!" << endl;
        }
        else if (abs(guess - secret) <= 5)
        {
            if(guess < secret){
                cout << "Guess very close! Try little higher" << endl;
            }
            else{
                cout << "Guess very close! Try little lower" << endl;
            }
        }
        
        else if (guess > secret)
        {
            /* code */
            cout << "📉 Too high! Try again: " << endl;
        }
        
        else {
            cout << "📈 Too low! Try again: " << endl;
        }
    } while (guess != secret);
    
    return 0;
}