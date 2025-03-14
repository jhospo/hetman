#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;
const int n = 8;

bool possible(int row, int col, const vector<pair<int, int>> &Queen) {
    for (int i = 0; i < Queen.size(); i++)
        if (Queen[i].first == row || Queen[i].second == col || abs(Queen[i].first - row) == abs(Queen[i].second - col))
            return false;
    return true;
}

bool solve(int col, vector<pair<int, int>> &Queen) {
    if (col == n)
        return true;
    if (col == 0) {
        int RRow = rand() % n;
        Queen.push_back({RRow, col});
        cout << "start: " << RRow << " " << col << endl;
        if (solve(col + 1, Queen))
            return true;
        cout << "back col: " << col << endl;
        Queen.pop_back();
        return false;

    }

    for (int row = 0; row < n; row++) {
        cout << "try: " << row << " " << col << endl;
        if (possible(row, col, Queen)) {
            Queen.push_back({row, col});
            cout << "placed: " << row << " " << col << endl;
            if (solve(col + 1, Queen))
                return true;
            Queen.pop_back();
        }
    }
    cout << "back to: " << col - 1 << endl;
    return false;

}

int main() {
    srand(time(NULL));
    vector<pair<int, int>> Queen;
    if (solve(0, Queen)) {
        cout << "SUKCES";
        for (int i = 0; i < Queen.size(); i++) {
            cout << "(" << Queen[i].first << ", " << Queen[i].second << ") ";
        }
        cout << endl;


    }
    return 0;
}
