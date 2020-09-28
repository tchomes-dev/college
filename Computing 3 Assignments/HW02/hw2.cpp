/***********************************************
Author: <Tony Choma>
Date: <9-19-2020>
Purpose: <Reads a file and replaces each instance of the word "dislike" with "love">
Sources of Help: <stackoverflow>
Time Spent: <1 hour>
***********************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string replaceWord(string line);

int main(int argv, char args[]) {
    string line;
    //assumes file is in the project folder
    ifstream file("input.txt");
    //if statement to check if file can be opened or not
    if (file.is_open()) {
        //while loop gets the current line until there isn't one
        while (getline(file, line)) {
            //calls replaceWord() which returns a new string and then prints the new string to console
            cout << replaceWord(line) << '\n';
        }
        //closes file
        file.close();
    }
    else cout << "Failed to read file";
}
//function that takes in the current string and finds the targeted word and then replaces it with the desired word.
//then returns the new line with the desired word 
string replaceWord(string line) {
    while (line.find("dislike") != string::npos)
        line.replace(line.find("dislike"), 7, "love");
    return line;
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
Date: 9-20-2020
Name: Tony Choma
*/