#include <iostream>
#include <vector>
#include "Timer.h"
using namespace std;

#define n 9
#define m 3

//std::string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
//char v[n] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
string v = "123456789";
//string v = "123456789ABCDEFG";
//string v = "123456789ABCDEFGHIJKLMNOP";
//std::string v[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};

//char v[n] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

char s[n][n];
vector<int> store[n][n];

bool notComplete() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (s[r][c] == '0') {
                return true;
            }
        }
    }
    return false;
}

bool repeatRC(int r, int c, char& val) {
    for (int i=0; i<n; i++) {
        if (s[r][i] == val || s[i][c] == val) {
            return true;
        }
    }
    return false;
}

bool repeatB(int r, int c, char& val) {
    for (int q=r; q<r+m; q++) {
        for (int w=c;  w<c+m; w++) {
            if (s[q][w] == val) {
                return true;
            }
        }
    }
    return false;
}

bool valid(int r, int c, char val) {
    if (!repeatRC(r, c, val) && !repeatB(r-r%m, c-c%m, val)) {
        return true;
    }
    return false;
}

void updateStore(){
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            store[i][j].clear();
    }
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (s[i][j] == '0'){
                vector<int>temp;
                for (int k=0; k<n; k++){
                    if (valid(i, j, v[k])){
                        temp.push_back(k);
                    }
                }
                store[i][j] = temp;
            }
}

void reUpdate(int& r, int& c, int& val) {
    int sr = r - r % m;
    int sc = c - c % m;

    for (int i = 0; i < n; i++) {
        if (i != r && s[i][c] == '0') {
            if (valid(i, c, v[val])) {
                store[i][c].push_back(val);
            }
        }

        if (i != c && s[r][i] == '0') {
            if (valid(r, i, v[val])) {
                store[r][i].push_back(val);
            }
        }
    }

    for (int i = sr; i < sr + m; i++) {
        for (int j = sc; j < sc + m; j++) {
            if (i != r && j != c && s[i][j] == '0') {
                if (valid(i, j, v[val])) {
                    store[i][j].push_back(val);
                }
            }
        }
    }
}



void update(int& r, int& c, int &val){
    for (int i=0; i<n; i++){
        if (i!=r && s[i][c] == '0'){
            vector<int>temp;
            for (int j : store[i][c]){
                if (j != val)
                    temp.push_back(j);
            }
            store[i][c] = temp;
        }

        if (i!=c && s[r][i] == '0'){
            vector<int>temp;
            for (int j : store[r][i]){
                if (j != val)
                    temp.push_back(j);
            }
            store[r][i] = temp;
        }
    }
    int sr = r-r%m;
    int sc = c-c%m;
    for (int i=sr; i<sr+m; i++){
        for (int j=sc; j<sc+m; j++){
            if (i!=r && j!=c){
                if (s[i][j] == '0'){
                    vector<int>temp;
                    for (int k : store[i][j]){
                        if (k != val)
                            temp.push_back(k);
                    }
                    store[i][j] = temp;
                }
            }
        }
    }
}

bool getLowest(vector<int> &Low, int &rl, int &cl) {
    bool low = false;
    int trace = n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '0') {
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

void prints(){
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

bool solveSudoku() {
    if (!notComplete()) {
        return true;
    }
    int r, c;
    vector<int> tryValues;
    getLowest(tryValues, r, c);
    for (int tryValue : tryValues) {
        s[r][c] = v[tryValue];
        update(r, c, tryValue);
        if (solveSudoku()) {
            return true;
        }
        s[r][c] = '0';
        reUpdate(r, c, tryValue);
    }
    return false;
}

int main() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> s[i][j];
        }
    }
    Timer <Unit::microseconds >speed;
    updateStore();

    if (solveSudoku()) {
        prints(); cout << endl;
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}
