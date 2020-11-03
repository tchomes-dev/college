#import <string>
#import <map>
#import <iostream>
#import <vector>

class Movie {
public:
    Movie();
    Movie(const string name);
    Movie(const string name, const int rating);


private:
    map<const string name, int numReview> movieMap;

};

//constructors
Movie::Movie() {
    movieMap.insert(make_pair(""), map<0, 0.0>));
}
Movie::Movie(string name) {
    movieMap.insert(make_pair(name, );
}
Movie::Movie(const string name, const int rating) {
    movieMap.insert(make_pair(name, map<vector<int>, int sum>));
    movieMap[name].insert(make_pair())
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
Date:   10-29-2020
Name:   Tony Choma
*/