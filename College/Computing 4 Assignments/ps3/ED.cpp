#include "ED.h"

ED::ED(string dna1, string dna2) {
    this->dna1 = dna1;
    this->dna2 = dna2;
    this->numCols = dna1.size()+1;
    this->numRows = dna2.size()+1;
    initialize();
    this->_opt = OptDistance();
    alignment();
    output();
}
void ED::initialize() {
    matrix = new int* [dna1.size()+1];
    for (int i = 0; i < dna1.size()+1; ++i) {
        matrix[i] = new int[dna2.size()+1];
    }

    mismatch_matrix = new int* [dna1.size()];
    for (int i = 0; i < dna1.size(); ++i) {
        mismatch_matrix[i] = new int[dna2.size()];
    }
    
    for (int i = 0; i < dna1.size() + 1; ++i) {
        for (int j = 0; j < dna2.size() + 1; ++j) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < dna1.size(); ++i) {
        for (int j = 0; j < dna2.size(); ++j) {
            mismatch_matrix[i][j] = 0;
        }
    }

    //set match/mismatch values
    for (int i = 0; i < dna1.size(); ++i) {
        for (int j = 0; j < dna2.size(); ++j) {
            mismatch_matrix[i][j] = penalty(dna1[i], dna2[j]);
        }
    }
    //set gap values
    for (int i = 0; i < dna1.size() + 1; ++i) {
        matrix[i][0] = i * 2;
    }
    for (int j = 0; j < dna2.size() + 1; ++j) {
        matrix[0][j] = j * 2;
    }
}

int ED::penalty(char a, char b) {
    return (a != b);
}

int ED::min(int a, int b, int c) {
    if (a < b && a < c) {
        return a;
    }
    else if (b < a && b < c) {
        return b;
    }
    else {
        return c;
    }
}

int ED::OptDistance() {
    for (int i = 1; i < dna1.size()+1; ++i) {
        for (int j = 1; j < dna2.size()+1; ++j) {
                matrix[i][j] = min(matrix[i - 1][j - 1] + mismatch_matrix[i - 1][j - 1],
                    matrix[i - 1][j] + 2,
                    matrix[i][j - 1] + 2);
        }
    }
    return matrix[numCols-1][numRows-1];
}

void ED::alignment() {
    int i = dna1.size();
    int j = dna2.size();

    while (i > 0 && j > 0) {
        if (i > 0 && j > 0 && matrix[i][j] == matrix[i - 1][j - 1] + mismatch_matrix[i - 1][j - 1]) {
            aligned1 += dna1[i - 1];
            aligned2 += dna2[j - 1];
            cost += to_string(penalty(dna1[i - 1], dna2[j - 1]));
            i--;
            j--;
        }
        else if (i > 0 && matrix[i][j] == matrix[i - 1][j] + 2) {
            aligned1 += dna1[i - 1];
            aligned2 += '-';
            cost += '2';
            i--;
        }
        else {
            aligned1 += '-';
            aligned2 += dna2[j - 1];
            cost += '2';
            j--;
        }
    }
}

void ED::output() {
    cout << setw(4) << "-" << setw(3);
    for (int i = 0; i < dna2.size(); i++) {
        cout << dna2[i] << setw(3);
    }
    cout << "\n";
    int x = 0;
    cout << "-" << setw(3);
    for (int i = 0; i < dna2.size()+1; i++) {
        cout << matrix[0][i] << setw(3);
    }
    cout << "\n";
    for (int i = 1; i < dna1.size() + 1; ++i) {
        for (int j = 0; j < dna2.size() + 1; ++j) {
            if ((j == 0) && x < dna1.size()) cout << dna1[x++] << setw(3);
            cout << matrix[i][j] << setw(3);
        }
        cout << "\n";
    }

    cout << "Edit Distance = " << _opt << "\n";
    for (int i = 0; i < aligned1.size(); i++) {
        cout << aligned1[i] << setw(3) << aligned2[i] << setw(3) << cost[i] << "\n";
    }
}

