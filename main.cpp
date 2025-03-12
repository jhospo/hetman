#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;
const int n = 8;

bool possible(int row, int col, const vector<pair<int,int>>& Queen) {
    for (int i = 0; i < Queen.size(); i++)
        if (Queen[i].first == row || Queen[i].second == col || abs(Queen[i].first - row) == abs(Queen[i].second - col))
            return false;
    return true;
}

int main() {
    vector<pair<int,int>> Queen;
    Queen.push_back({0, 0});

    if (possible(1, 2, Queen)) {
        cout << "Moozna" << endl;
        Queen.push_back({1, 2});
    } else {
        cout << "Nie" << endl;
    }

    if (possible(1, 1, Queen)) {
        cout << "tak" << endl;
    } else {
        cout << "Nie" << endl;
    }
    for (int i = 0; i < Queen.size(); i++) {
        cout << Queen[i].first << Queen[i].second << endl;
    }

    return 0;
}
