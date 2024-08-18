#include <iostream>
#include <vector>
using namespace std;

#define n 16
#define m 4

// Define the possible values for the Sudoku cells
//string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
std::string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G"};
//std::string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};

bool notComplete(string **s) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (s[r][c] == "0") {
                return true;
            }
        }
    }
    return false;
}

bool repeatRC(string **s, int r, int c, string val) {
    for (int i = 0; i < n; i++) {
        if (s[r][i] == val || s[i][c] == val) {
            return true;
        }
    }
    return false;
}

bool repeatB(string **s, int r, int c, string val) {
    for (int q = r; q < r + m; q++) {
        for (int w = c; w < c + m; w++) {
            if (s[q][w] == val) {
                return true;
            }
        }
    }
    return false;
}

bool valid(string **s, int r, int c, string val) {
    if (!repeatRC(s, r, c, val) && !repeatB(s, r - r % m, c - c % m, val)) {
        return true;
    }
    return false;
}

bool getLowest(string **s, vector<int> &Low, int &rl, int &cl) {
    bool low = false;
    int trace = n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == "0") {
                vector<int> tempLow;
                for (int k = 0; k < n; k++) {
                    if (valid(s, i, j, v[k])) {
                        tempLow.push_back(k);
                    }
                }
                if (!tempLow.empty() && tempLow.size() < trace) {
                    Low = tempLow;
                    trace = tempLow.size();
                    rl = i;
                    cl = j;
                    low = true;
                }
            }
        }
    }
    return low;
}

bool solveSudoku(string **s) {
    if (!notComplete(s)) {
        return true;
    }
    int r, c;
    vector<int> tryValues;
    if (!getLowest(s, tryValues, r, c)) {
        return false;
    }
    for (int i = 0; i < tryValues.size(); i++) {
        s[r][c] = v[tryValues[i]];
        if (solveSudoku(s)) {
            return true;
        }
        s[r][c] = "0"; // Backtrack if the current placement doesn't lead to a solution
    }
    return false;
}

void prints(string **s){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << s[i][j];
            if (j!=n-1)
                cout << " ";
        }
        if (i!=n-1)
            cout << "\n";
    }
}


int main() {
    string **sudoku = new string *[n];

    for (int j = 0; j < n; j++) {
        sudoku[j] = new string[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> sudoku[i][j];
        }
    }

    if (solveSudoku(sudoku)) {
        prints(sudoku);
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}
