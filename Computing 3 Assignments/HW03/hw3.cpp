/***********************************************
Author: <Tony Choma>
Date: <9-20-2020>
Purpose: <program that can create and modify point objects>
Sources of Help: <N/A>
Time Spent: <Insert how much time you spent
on the assignment here>
***********************************************/
#include <iostream>
#include <math.h>

using namespace std;

class Point {
    private:
        int xCoor = 0;
        int yCoor = 0;
       
    public:
        //getters and setters for the x coordinate and y coordinate
        //----------------------
        int getX() {
            return xCoor;
        }
        int getY() {
            return yCoor;
        }
        void setX(int x) {
            xCoor = x;
        }
        void setY(int y) {
            yCoor = y;
        }
        //----------------------

        //function that moves a point specified by the parameters
        //parameters move the point by how many units in a direction
        void move(int x, int y) {
            setX(getX() + x);
            setY(getY() + y);
        }
        //rotates a point by 90 degrees clockwise
        void rotateClockwise() {
            float x = getX();
            float y = getY();
            float s = sin(-90.0*(3.14/180.0));
            float c = cos(-90.0*(3.14/180.0));
            
            setX(round(x * c - y * s));
            setY(round(x * s + y * c));
        }
        //prints the where the point is currently
        void printPoint() {
            cout << "(" << getX() << ", " << getY() << ")" << endl;
        }
};

int main(int argv, char argc[]) {
    Point point;
    //tests rotating 360 degrees
    point.setX(1);
    point.setY(2);
    for (int i = 0; i < 4; i++) {
        point.rotateClockwise();
        point.printPoint();
    }
    //tests moving a point at (5,-4) by (-5, 4) to the origin
    point.setX(5);
    point.setY(-4);
    point.move(-5, 4);
    point.printPoint();
    //tests moving the point (3, 4) by (1, 1)
    point.setX(3);
    point.setY(4);
    point.move(1, 1);
    point.printPoint();
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