#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// header files
// #include "../headers/backwardElimination.h" for part 1
// #include "../headers/forwardSelection.h" for part 1

// part 2 headers
#include "../headers/NNClassifier.h"
#include "../headers/Validator.h"


using namespace std;

// evaluate function for part 1
// double evaluate(const vector<int>& featureSet) {
//     return (rand() % 1000) / 10.0;
// } 

// Load dataset. we have small and large dataset

void loadDataset(const string& filename, vector<vector<double>>& X, vector<int>& y) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open " << filename << "\n";
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        int label;
        ss >> label;
        y.push_back(label);

        vector<double> row;
        double val;
        while (ss >> val) {
            row.push_back(val);
        }
        X.push_back(row);
    }
}

// Normalize the data to mean 0, std 1

void normalizeData(vector<vector<double>>& X) {
    if (X.empty()) return;

    int n = X.size();
    int d = X[0].size();

    for (int j = 0; j < d; j++) {
        double mean = 0.0;
        for (int i = 0; i < n; i++) {
            mean += X[i][j];
        }
        mean /=n;

        double var = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = X[i][j] - mean;
            var += diff * diff;
        }
        var /=n;

        double stddev = sqrt(var);
        if (stddev == 0) stddev = 1.0;

        for (int i = 0; i < n; i++) {
            X[i][j] = (X[i][j] - mean) / stddev;
        }
    }
}

int main() {
    // part 1 code
    // srand(time(0));

    // cout << "Welcome to our Feature Selection Algorithm! \n";
    // cout << "Please enter the total number of features: ";

    // int totalFeatures;
    // cin >> totalFeatures;

    // cout << "\nType the number of the algorithm you would like to run.\n";
    // cout << "1. Forward Selection\n";
    // cout << "2. Backward Elimination\n";
    // cout << "Enter your selection: ";

    // int selection;
    // cin >> selection;

    // cout << endl;

    // if (selection == 1) {
    //     forwardSelection(totalFeatures);
    // }
    // else if (selection == 2) {
    //     backwardElimination(totalFeatures);
    // }
    // else {
    //     cout << "Invalid choice, exiting...\n";
    // }

    // return 0;

    // part 2 main implementation below

    vector<vector<double>> X;
    vector<int> y;

    cout << "Select a dataset:\n";
    cout << "1. Small dataset\n";
    cout << "2. Large dataset\n";
    cout << "Enter your choice: ";

    int datasetChoice;
    cin >> datasetChoice;

    string filename;
    if(datasetChoice == 1) {
        filename = "small-test-dataset-2-2.txt";
    } else if (datasetChoice == 2) {
        filename = "large-test=dataset-2.txt";
    } else {
        cout << "Invalid choice, exiting...\n";
        return 0;
    }

    loadDataset(filename, X, y);
    normalizeData(X);

    cout << "Dataset loaded with " << X.size() << " instances and " << X[0].size() << " features.\n";
    cout << "Enter feature indices to evaluate (1-based, end with -1): ";

    vector <int> featureSubset;
    int f;
    while (cin >> f && f!= -1) {
        featureSubset.push_back(f);
    }

    NearestNeighborClassifier nn;
    Validator validator(nn, X, y, featureSubset);

    double acc = validator.validate();

    cout << "\nUsing feature(s) { ";
    for (int v: featureSubset) cout << v << " ";
    cout <<"} accuracy = " << fixed << setprecision(4) << acc << endl;

    return 0;
}