#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream input("data.txt");
    if (!input) {
        cerr << "Error: Could not open data.txt" << endl;
        return 1;
    }

    vector<string> map;
    string line;
    while (getline(input, line)) {
        map.push_back(line);
    }
    input.close();

    int emptyPositionCount = 0;

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            // Count empty cells (positions) that can be chosen for obstruction
            if (map[i][j] == '.') {
                ++emptyPositionCount;
            }
        }
    }

    cout << "Total different positions available for placing an obstruction: " << emptyPositionCount << endl;

    return 0;
}
