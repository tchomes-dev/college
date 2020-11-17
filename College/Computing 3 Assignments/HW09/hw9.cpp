#include <string>
#include <iostream>

using namespace std;

class Player {
public:
    virtual int getGuess() { return 0; }
};

class HumanPlayer : Player {
public:
    int getGuess();
};

class ComputerPlayer : Player {
public:
    int getGuess();
};


//////////////////////////////////////
// Global functions given in project
//////////////////////////////////////
bool checkForWin(int guess, int answer)
{
    if (answer == guess)
    {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess)
        cout << "Your guess is too high." << endl;
    else
        cout << "Your guess is too low." << endl;
    return false;
}
// The play function takes as input two Player objects.
void play(Player& player1, Player& player2) {
    int answer = 0, guess = 0;
    answer = rand() % 100;
    bool win = false;

    while (!win)
    {
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess();
        win = checkForWin(guess, answer);
        if (win) return;

        cout << "Player 2's turn to guess." << endl;
        guess = player2.getGuess();
        win = checkForWin(guess, answer);
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
Date: 11-17-2020
Name: Tony Choma
*/