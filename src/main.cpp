#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <unordered_map>

// header files
#include "../headers/backwardElimination.h"
#include "../headers/forwardSelection.h"

// part 2 headers
#include "../headers/NNClassifier.h"
#include "../headers/CrossValidation.h"


using namespace std;

vector<vector<double>> globalX;
vector<int> globalY;

NearestNeighborClassifier globalNN;

double evaluate(const vector<int>& featureSet) {
    if (featureSet.empty()) {
        if (globalY.empty()) return 0.0;

        unordered_map<int,int> freq;
        for (int label : globalY) {
            freq[label]++;
        }
        int maxCount = 0;
        for (const auto& p : freq) {
            if (p.second > maxCount) {
                maxCount = p.second;
            }
        }
        double defRate = maxCount / static_cast<double>(globalY.size());
        return defRate * 100.0;
    }

    CrossValidation cv(globalNN, globalX, globalY, featureSet);
    double acc = cv.validate();
    return acc * 100.0;
} 

// Load dataset. we have small and large dataset





void loadDataset(const string& filename, vector<vector<double>>& X, vector<int>& y) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Error: could not open " << filename << "\n";
        exit(1);
    }
    string fileContent((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());

    for (char &c : fileContent) {
        if (c == '\r') c = '\n';
    }
    stringstream all(fileContent);

    string line;
    while (getline(all, line)) {
        if(line.empty()) continue;

        stringstream ss(line);

        double labelDouble;
        if (!(ss >> labelDouble)) continue;
        
        int label = static_cast<int>(labelDouble);
        y.push_back(label);

        vector<double> row;
        row.push_back(labelDouble);

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

    for (int j = 1; j < d; j++) {
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

    cout << "Welcome to our Feature Selection Algorithm! \n";
    cout << "Select which dataset you would like to use:\n";
    cout << "Select a dataset:\n";
    cout << "1. Small dataset\n";
    cout << "2. Large dataset\n";
    cout << "3. Titanic dataset\n";
    cout << "Enter choice ";

    int datasetChoice;
    cin >> datasetChoice;

    string filename;
    if(datasetChoice == 1) {
        filename = "src/small-test-dataset-2-2.txt";
    } else if (datasetChoice == 2) {
        filename = "src/large-test-dataset-2.txt";
    } else if (datasetChoice == 3) {
        filename = "src/titanic-clean-2.txt";
    } else {
        cout << "Invalid choice, exiting...\n";
        return 0;
    }

    loadDataset(filename, globalX, globalY);

    int totalFeatures = globalX[0].size() - 1;
    cout << "\nThis dataset has " << totalFeatures << " features (not including the class attribute), with " << globalX.size() << " instances.\n";
    normalizeData(globalX);

    cout << "\nType the number of the algorithm you would like to run.\n";
    cout << "1. Forward Selection\n";
    cout << "2. Backward Elimination\n";
    cout << "Enter your selection: ";

    int selection;
    cin >> selection;

    cout << endl;

    if (selection == 1) {
        forwardSelection(totalFeatures);
    }
    else if (selection == 2) {
        backwardElimination(totalFeatures);
    }
    else {
        cout << "Invalid choice, exiting...\n";
    }

    return 0;

    // part 2 main implementation below

    // vector<vector<double>> X;
    // vector<int> y;

    
    // cout << "Enter your choice: ";

    

    // loadDataset(filename, X, y);
    // normalizeData(X);

    // cout << "Dataset loaded with " << X.size() << " instances and " << X[0].size()-1 << " features.\n";
    // cout << "Enter feature indices to evaluate (1-based, end with -1): ";

    // vector <int> featureSubset;
    // int f;
    // while (cin >> f && f!= -1) {
    //     featureSubset.push_back(f);
    // }

    // NearestNeighborClassifier nn;
    // CrossValidation validator(nn, X, y, featureSubset);

    // double acc = validator.validate();

    // cout << "\nUsing feature(s) { ";
    // for (int v: featureSubset) cout << v << " ";
    // cout <<"} accuracy = " << fixed << setprecision(4) << acc << endl;

    return 0;
}