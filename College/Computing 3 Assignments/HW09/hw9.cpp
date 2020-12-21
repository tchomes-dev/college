#include <string>
#include <iostream>
#include <time.h>

using namespace std;

int random(int min, int max);

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return is_base_of<Base, T>::value;
}

class Player {
public:
    virtual int getGuess() { return 0; }
    virtual void setUpper(int upper) { return; }
    virtual void setLower(int lower) { return; }
};

class HumanPlayer : public Player {
public:
    int getGuess();
};

class ComputerPlayer : public Player {
public:
    int getGuess();
    void setUpper(int guess) { upperBound = guess - 1 ; }
    void setLower(int guess) { lowerBound = guess + 1; }
private:
    int upperBound = 100;
    int lowerBound = 0;
};

int HumanPlayer::getGuess() {
    int input;
    cout << "Enter a number: \n";
    cin >> input;
    return input;
}

int ComputerPlayer::getGuess() {
    int answer = random(lowerBound, upperBound);
    cout << "The computer guesses : " << answer << endl;
    return answer;
}

//////////////////////////////////////
// Global functions given in project
//////////////////////////////////////
bool checkForWin(int guess, int answer, Player& player)
{
    if (answer == guess)
    {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess) {
        player.setUpper(guess);
        cout << "Your guess is too high." << endl;
    }
    else {
        player.setLower(guess);
        cout << "Your guess is too low." << endl;
    }
    return false;
}
// The play function takes as input two Player objects.
void play(Player& player1, Player& player2) {
    int answer = 0, guess1 = 0, guess2 = 0, highLow1 = 0, highLow2 = 0;
    srand(time(0));
    answer = rand() % 100;
    bool win = false;
    while (!win)
    {
        cout << "Player 1's turn to guess." << endl;
        guess1 = player1.getGuess();
        win = checkForWin(guess1, answer, player2);
        if (win) return;
  
        cout << "Player 2's turn to guess." << endl;
        guess2 = player2.getGuess();
        win = checkForWin(guess2, answer, player2);
    }
}

int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

int main(int argv, char argc[]) {
    HumanPlayer human1;
    HumanPlayer human2;
    ComputerPlayer comp1;
    ComputerPlayer comp2;

    play(human1, human2);
    play(human1, comp1);
    play(comp1, comp2);
    play(comp2, comp1);
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