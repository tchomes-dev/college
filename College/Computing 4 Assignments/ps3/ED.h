#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

class ED
{
public:
    ED(string dna1, string dna2);
    static int penalty(char a, char b);
    static int min(int a, int b, int c);
    int OptDistance();
    void alignment();
    void output();
    void initialize();
private:
    int** matrix;
    int** mismatch_matrix;
    int _opt;
    int numCols, numRows;
    string dna1, dna2, aligned1, aligned2, cost;
};

