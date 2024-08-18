#include <iostream>
#include <vector>
using namespace std;

#define n 25
#define m 5

// Define the possible values for the Sudoku cells
//string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
//string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G"};
string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};


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

bool repeatRC(string **s, int r, int c, string& val) {
    for (int i=0; i<n; i++) {
        if (s[r][i] == val || s[i][c] == val) {
            return true;
        }
    }
    return false;
}

bool repeatB(string **s, int r, int c, string& val) {
    for (int q=r; q<r+m; q++) {
        for (int w=c;  w<c+m; w++) {
            if (s[q][w] == val) {
                return true;
            }
        }
    }
    return false;
}

bool valid(string **s, int r, int c, string val) {
    if (!repeatRC(s, r, c, val) && !repeatB(s, r-r%m, c-c%m, val)) {
        return true;
    }
    return false;
}

void updateStore(string **s, vector<int> **store){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            store[i][j].clear();
    }
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (s[i][j] == "0"){
                vector<int>temp;
                for (int k=0; k<n; k++){
                    if (valid(s, i, j, v[k])){
                        temp.push_back(k);
                    }
                }
                store[i][j] = temp;
            }
}


bool getLowest(string **s, vector<int> &Low, int &rl, int &cl, vector<int> **store) {
    bool low = false;
    int trace = n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == "0") {
                if (store[i][j].size()<=trace){
                    trace = store[i][j].size();
                    Low = store[i][j];
                    store[i][j].size();
                    rl = i;
                    cl = j;
                    low = true;
                }
                if (trace == 1)
                    return low;
            }
        }
    }
    return low;
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

bool solveSudoku(string **s, vector<int> **store) {
    if (!notComplete(s)) {
        return true;
    }
    int r, c;
    vector<int> tryValues;
    getLowest(s, tryValues, r, c, store);
    for (int tryValue : tryValues) {
        s[r][c] = v[tryValue];
        updateStore(s, store);
        if (solveSudoku(s, store)) {
            //prints(s); cout << "\n" << "\n";
            return true;
        }

        s[r][c] = "0";
    }
    return false;
}

int main() {
    auto **sudoku = new string *[n];

    for (int j = 0; j < n; j++) {
        sudoku[j] = new string[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> sudoku[i][j];
        }
    }

    auto **store = new vector<int> *[n];

    for (int j = 0; j < n; j++) {
        store[j] = new vector<int>[n];
    }

    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++){
            vector<int>temp;
            store[i][j] = temp;
        }

    updateStore(sudoku, store);

    if (solveSudoku(sudoku, store)) {
        prints(sudoku);
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}
