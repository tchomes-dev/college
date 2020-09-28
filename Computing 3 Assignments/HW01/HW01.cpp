/***********************************************
    Author: <Tony Choma>
    Date: <9-15-2020>
    Purpose: <A number guessing game that generates a random number from 1 - 1000 using a random seed>
    Sources of Help: <stackoverflow>
    Time Spent: <2 hours>
***********************************************/

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int calcRandNum(int mini, int max);
void setup(int &mini, int &max, int &guesses);
bool game(int& random, int& mini, int& max, int &guesses);

int main() {
    int minimum = 0;
    int maximum = 0;
    int guesses = 0;
    int random = 0;
    bool b = true;
    //while loop that keeps the game running until user exits
    while (b) {
        setup(minimum = 0, maximum = 0, guesses = 0);
        random = calcRandNum(minimum, maximum);
        b = game(random, minimum, maximum, guesses);
    }
}
//random number calculation. takes in min and max parameters for the calculation
int calcRandNum(int mini, int max) {
    return mini + (rand() % static_cast<int>(max - mini + 1));
}
//initial setup for the game. it has parameters so that they can be set
void setup(int& mini, int& max, int &guesses) {
    bool b = true;
    //sets minimum
    while (b) {
        cout << "Please enter the minimum number, a positive integer: ";
        cin >> mini;
        if (mini < 1) {
            cout << "Oops! Not a positive integer!" << endl;
            continue;
        }
        if (max > 998) {
            cout << "Oops! Too big! Pick a smaller number." << endl;
            continue;
        }
        b = false;
    }
    b = true;
    //sets maximum
    while (b) {
        cout << "Please enter the maximum number, which is greater than the minimum and less than 1000: ";
        cin >> max;
        if (max <= mini) {
            cout << "Oops! The max has to be greater than the minimum." << endl;
            continue;
        }
        if (max > 999) {
            cout << "Oops! Too big!" << endl;
            continue;
        }
        b = false;
    }
    b = true;
    //sets number of guesses
    while (b) {
        cout << "Please enter the number of guesses allowed (less than 10): ";
        cin >> guesses;
        if (guesses < 1 || guesses > 9) {
            cout << "Oops! Should be less than 10 and greater than 0." << endl;
            continue;
        }
        b = false;
    }
}
//game function that returns a boolean to determine if the player wants to play again or not. takes the rest of the parameters that were set in functions setup() and calcRandNum() and uses them for the game
bool game(int& random, int& mini, int& max, int& guesses) {
    bool b = true;
    int guess = 0;
    int numGuesses = 0;
    while (b) {
        cout << "Now, I have a number between " << mini << " and " << max
            << ". Can you guess my number? Please type your first guess. ";
        cin >> guess;
        numGuesses++;

        while (guesses) {
            if (numGuesses == guesses) {
                cout << "Sorry, you can't guess any more. The number is: " << random << ".";
                break;
            }
            if (guess == random) {
                cout << "Excellent! You guessed the number!" << endl;
                break;
            }
            if (guess > random) {
                cout << "Too high! Try again. " << endl;
            }
            if (guess < random) {
                cout << "Too low! Try again. " << endl;
            }
            cout << "? ";
            cin >> guess;
            numGuesses++;
        }

        char input;
        cout << "Would you like to play again (y or n)? ";
        cin >> input;
        if (input == 'y') {
            guesses = 0;
            return true;
        }
        else if (input == 'n') {
            b = false;
            return false;
        }
    }

}

/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 9-15-2020
Name: Tony Choma
*/