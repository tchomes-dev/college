/***********************************************
Author: <Tony Choma>
Date: <12-8-2020>
Purpose: <Creates permutations of a user inputted string>
Sources of Help: <cplusplus.com>
Time Spent: <3 hours>
***********************************************/

#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

list<list<string>> generate_permutations(list<string> inputList);
void print_permutations(list<list<string>> permutations);
void remove_duplicates(list<string>& inputList, set<string>& inputSet);

list<list<string>> generate_permutations(list<string> inputList) {
    set<string> s1;
    list<list<string>> output;

    inputList.sort();
    remove_duplicates(inputList, s1);
    do {
        output.push_back(inputList);
    } while (next_permutation(inputList.begin(), inputList.end()));

    return output;
}

void remove_duplicates(list<string>& inputList, set<string>& inputSet) {
    for (string i : inputList) {
        inputSet.insert(i);
    }
    inputList.clear();
    for (string j : inputSet) {
        inputList.push_back(j);
    }
}

void print_permutations(list<list<string>> permutations) {
    int number = 1;

    cout << "Perumtations are:\n";
    for (auto i : permutations) {
        cout << number << ". ";
        for (auto j : i) {
            cout << j << " ";
        }
        number++;
        cout << endl;
    } 
}
int main(int argc, char* argv[]) {
    list<string> inputList;
    string aLine, aString;
    // read in strings from stdin
    cout << "Enter strings, separated by a space:";
    getline(cin, aLine); //read a line from keyboard
    istringstream iss(aLine); //convert aLine to an istringstream obj
        //parse each string
        while (iss >> aString)
        {
            inputList.push_back(aString);
        }

    auto permutations = generate_permutations(inputList);

    // print permutations to stdout
    print_permutations(permutations);

    return 0;
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
Date: 12-8-2020
Name: Tony Choma
*/