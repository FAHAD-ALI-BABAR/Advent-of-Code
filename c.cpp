#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
using namespace std;

// Function to evaluate an expression left-to-right
int evaluateLeftToRight(const vector<int>& numbers, const vector<char>& operators) {
    int result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result;
}

// Recursive function to generate all operator combinations
bool canAchieveTarget(const vector<int>& numbers, int target, vector<char>& currentOperators) {
    if (currentOperators.size() == numbers.size() - 1) {
        // Evaluate the expression with the current operator combination
        int result = evaluateLeftToRight(numbers, currentOperators);
        return result == target;
    }

    // Try adding '+' operator
    currentOperators.push_back('+');
    if (canAchieveTarget(numbers, target, currentOperators)) {
        return true;
    }
    currentOperators.pop_back();

    // Try adding '*' operator
    currentOperators.push_back('*');
    if (canAchieveTarget(numbers, target, currentOperators)) {
        return true;
    }
    currentOperators.pop_back();

    return false;
}

int main() {
    ifstream input("data.txt");
    if (!input) {
        cerr << "Error: Could not open data.txt" << endl;
        return 1;
    }

    string line;
    int totalCalibrationResult = 0;

    while (getline(input, line)) {
        stringstream ss(line);
        int target;
        char colon;
        vector<int> numbers;

        // Parse target and numbers
        ss >> target >> colon;
        int num;
        while (ss >> num) {
            numbers.push_back(num);
        }

        if (numbers.empty()) {
            continue; // Skip lines with no numbers
        }

        // Debug output
        cout << "Processing: Target = " << target << ", Numbers = ";
        for (int n : numbers) cout << n << " ";
        cout << endl;

        // Check if the target can be achieved
        vector<char> operators;
       
    }

    input.close();

    cout << "Total calibration result: " << totalCalibrationResult << endl;

    return 0;
}
