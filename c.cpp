#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to check if an "X-MAS" exists starting at (row, col)
bool checkXMAS(const vector<string>& grid, int row, int col) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Check bounds for the X shape
    if (row - 1 < 0 || row + 1 >= rows || col - 1 < 0 || col + 1 >= cols)
        return false;

    // Check the X-MAS pattern in both orientations
    return ((grid[row - 1][col - 1] == 'M' && grid[row][col] == 'A' && grid[row + 1][col + 1] == 'S' &&
             grid[row - 1][col + 1] == 'M' && grid[row + 1][col - 1] == 'S') ||
            (grid[row - 1][col - 1] == 'S' && grid[row][col] == 'A' && grid[row + 1][col + 1] == 'M' &&
             grid[row - 1][col + 1] == 'S' && grid[row + 1][col - 1] == 'M'));
}

// Function to count all occurrences of "X-MAS" in the grid
int countXMAS(const vector<string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (checkXMAS(grid, row, col)) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    ifstream inputFile("data.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open file data.txt" << endl;
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    int totalOccurrences = countXMAS(grid);
    cout << "Total occurrences of \"X-MAS\": " << totalOccurrences << endl;

    return 0;
}