#include <iostream>
#include <vector>
using namespace std;

#define n 9
#define m 3

bool notComplete(int **s) {
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (s[r][c] == 0)
                return true;
    return false;
}

bool repeatRC(int **s, int r, int c, int l) {
    for (int i = 0; i < n; i++)
        if (s[r][i] == l || s[i][c] == l)
            return true;
    return false;
}

bool repeatB(int **s, int r, int c, int l) {
    for (int q = r; q < r + m; q++)
        for (int w = c; w < c + m; w++)
            if (s[q][w] == l)
                return true;
    return false;
}

bool valid(int **s, int r, int c, int i) {
    if (!repeatRC(s, r, c, i) && !repeatB(s, r - r % m, c - c % m, i))
        return true;
    return false;
}

bool getLowest(int **s, vector<int>& Low, int& rl, int& cl) {
    bool low = false;
    int trace = 26;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == 0) {
                vector<int> tempLow;
                int p = 0;
                for (int k = 1; k <= n; k++) {
                    if (valid(s, i, j, k)) {
                        tempLow.push_back(k);
                        p++;
                    }
                }
                if (p < trace && p != 0) {
                    Low = tempLow;
                    trace = p;
                    rl = i;
                    cl = j;
                    low = true;
                }
            }
        }
    }
    return low;
}

bool solveSudoku(int **s) {
    if (!notComplete(s))
        return true;
    int r, c;
    vector<int> tryValues;
    if (getLowest(s, tryValues, r, c)) {
        for (int i = 0; i < tryValues.size(); i++) {
            s[r][c] = (tryValues[i]);
            if (solveSudoku(s))
                return true;
            s[r][c] = 0; // Reset the cell if the current placement doesn't lead to a solution
        }
    }
    return false;
}

void prints(int **s){
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
    int **sudoku = new int *[n];

    int z;
    for (int j = 0; j < n; j++) {
        sudoku[j] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> z;
            cin.ignore();
            sudoku[i][j] = z;
        }
    }

    if (solveSudoku(sudoku)) {
        prints(sudoku);
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}
