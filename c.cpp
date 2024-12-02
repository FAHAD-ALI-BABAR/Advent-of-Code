#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath> // For abs()

using namespace std;

// Function to check if a report is safe
bool isSafe(const vector<int>& levels) {
    if (levels.size() < 2) return false;

    bool increasing = true, decreasing = true;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];

        // Check if the difference is out of the acceptable range
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }

        // Check if not strictly increasing or decreasing
        if (diff < 0) increasing = false;
        if (diff > 0) decreasing = false;
    }

    // Return true only if all levels are either increasing or decreasing
    return increasing || decreasing;
}

// Function to check if a report is safe with the Problem Dampener
bool isSafeWithDampener(const vector<int>& levels) {
    if (isSafe(levels)) return true; // If already safe, no need to remove a level

    for (size_t i = 0; i < levels.size(); ++i) {
        vector<int> modifiedLevels;
        for (size_t j = 0; j < levels.size(); ++j) {
            if (j != i) {
                modifiedLevels.push_back(levels[j]);
            }
        }
        if (isSafe(modifiedLevels)) {
            return true; // Safe after removing one level
        }
    }

    return false; // Not safe even with the Problem Dampener
}

int main() {
    // File path to read the data from
    string filePath = "data.txt";
    ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file " << filePath << endl;
        return 1;
    }

    string line;
    int safeCount = 0;
    vector<vector<int>> reports;

    // Read each line and process the levels
    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<int> levels;
        int num;

        while (iss >> num) {
            levels.push_back(num);
        }

        if (isSafeWithDampener(levels)) {
            ++safeCount;
        }

        reports.push_back(levels);
    }

    inputFile.close();

    // Output the results
    cout << "Total safe reports with Problem Dampener: " << safeCount << endl;

    return 0;
}
