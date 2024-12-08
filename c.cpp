#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

int main() {
    map<char, vector<pair<int, int>>> antennas;
    int rows, cols;
    cin >> rows >> cols;
    vector<string> grid(rows);

    // Reading the grid
    for (int i = 0; i < rows; i++) {
        cin >> grid[i];
    }

    // Parse antennas
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char ch = grid[i][j];
            if (isalnum(ch)) {
                antennas[ch].emplace_back(i, j);
            }
        }
    }

    // Find antinodes
    map<pair<int, int>, bool> antinodes;
    for (const auto& entry : antennas) {
        const auto& positions = entry.second;
        int size = positions.size();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                auto pos1 = positions[i];
                auto pos2 = positions[j];
                int x1 = pos1.first, y1 = pos1.second;
                int x2 = pos2.first, y2 = pos2.second;

                int mx = (x1 + x2) / 2;
                int my = (y1 + y2) / 2;

                // Ensure midpoint is integer
                if ((x1 + x2) % 2 == 0 && (y1 + y2) % 2 == 0) {
                    antinodes[{mx, my}] = true;
                }
            }
        }
    }

    cout << "Total unique antinode locations: " << antinodes.size() << endl;
    return 0;
}
