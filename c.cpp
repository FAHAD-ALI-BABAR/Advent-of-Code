#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to check if an update is valid based on the rules
bool isValidUpdate(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules) {
    unordered_map<int, int> position;
    for (int i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    for (const auto& rule : rules) {
        int x = rule.first;
        const unordered_set<int>& ySet = rule.second;
        if (position.find(x) != position.end()) {
            for (int y : ySet) {
                if (position.find(y) != position.end() && position[x] > position[y]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to reorder an update based on the rules
vector<int> reorderUpdate(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules) {
    vector<int> reordered = update;

    sort(reordered.begin(), reordered.end(), [&](int a, int b) {
        // Custom comparator based on the rules
        if (rules.find(a) != rules.end() && rules.at(a).count(b)) {
            return true;
        }
        if (rules.find(b) != rules.end() && rules.at(b).count(a)) {
            return false;
        }
        return a > b; // Default to descending order if no direct rule applies
    });

    return reordered;
}

int main() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open data.txt" << endl;
        return 1;
    }

    unordered_map<int, unordered_set<int>> rules;
    vector<vector<int>> updates;
    string line;
    bool readingRules = true;

    // Read the input from the file
    while (getline(file, line)) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }

        if (readingRules) {
            stringstream ss(line);
            string xStr, yStr;
            getline(ss, xStr, '|');
            getline(ss, yStr);
            int x = stoi(xStr);
            int y = stoi(yStr);
            rules[x].insert(y);
        } else {
            stringstream ss(line);
            vector<int> update;
            string page;
            while (getline(ss, page, ',')) {
                update.push_back(stoi(page));
            }
            updates.push_back(update);
        }
    }

    file.close();

    int sumOfMiddlePages = 0;
    int sumOfFixedMiddlePages = 0;

    for (const auto& update : updates) {
        if (isValidUpdate(update, rules)) {
            int middleIndex = update.size() / 2;
            sumOfMiddlePages += update[middleIndex];
        } else {
            vector<int> fixedUpdate = reorderUpdate(update, rules);
            int middleIndex = fixedUpdate.size() / 2;
            sumOfFixedMiddlePages += fixedUpdate[middleIndex];
        }
    }

    cout << "Sum of middle page numbers (valid updates): " << sumOfMiddlePages << endl;
    cout << "Sum of middle page numbers (fixed updates): " << sumOfFixedMiddlePages << endl;

    return 0;
}
