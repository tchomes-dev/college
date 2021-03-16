#pragma once
#include <string>
#include <vector>

using namespace std;

class ED
{
public:
    ED(string dna1, string dna2);
    static int penalty(char a, char b);
    static int min(int a, int b, int c);
    int OptDistance();
    string alignment();
    string spaceFill(string obj);
private:
    vector<vector<int>> matrix;
    string dna1, dna2;
};

