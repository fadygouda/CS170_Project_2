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
    if (featureSet.empty()) { // when 0 features are present
        if (globalY.empty()) return 0.0;

        // count occurences of each class label (1's and 2's)
        unordered_map<int,int> classFrequency;
        for (int label : globalY) {
            classFrequency[label]++;
        }

        int maxCount = 0; // find most common class
        for (const auto& entry : classFrequency) {
            int count = entry.second;
            if (count > maxCount) {
                maxCount = count;
            }
        }
        double defaultAccuracy = maxCount / static_cast<double>(globalY.size());
        return defaultAccuracy * 100.0; // predicts the most common class, either 1 or 2.
    }

    CrossValidation cv(globalNN, globalX, globalY, featureSet);
    double acc = cv.validate();
    return acc * 100.0;
} 

// Load dataset. we have small and large dataset





void loadDataset(const string& filename, vector<vector<double>>& X, vector<int>& y) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open " << filename << "\n";
        exit(1);
    }

    string line;
    while (getline(file, line)) {
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

    int numRows = X.size(); // number of data points
    int numColumns = X[0].size(); // total number of columns in data set (label + features)


    for (int col = 1; col < numColumns; col++) { // loop through every column starting at 1 to skip the class label column
        // compute mean
        double mean = 0.0;
        for (int row = 0; row < numRows; row++) {
            mean += X[row][col];
        }
        mean /= numRows;

        // compute the variance
        double variance = 0.0;
        for (int row = 0; row < numRows; row++) {
            double diff = X[row][col] - mean;
            variance += diff * diff;
        }
        variance /= numRows;

        // compute std
        double stddev = sqrt(variance); 
        if (stddev == 0) stddev = 1.0;

        for (int row = 0; row < numRows; row++) {
            X[row][col] = (X[row][col] - mean) / stddev;
        }
    }
}

void checkNormalizationEffect(const string& filename) {
    vector<vector<double>> Xraw;
    vector<int>Y;

    loadDataset(filename, Xraw, Y);

    vector<vector<double>> Xnorm = Xraw;
    normalizeData(Xnorm);

    vector<int> allFeatures;
    for (int col = 1; col < static_cast<int>(Xraw[0].size()); col++) {
        allFeatures.push_back(col);
    }

    NearestNeighborClassifier nnRaw, nnNorm;
    CrossValidation cvRaw(nnRaw, Xraw, Y, allFeatures);
    CrossValidation cvNorm(nnNorm, Xnorm, Y, allFeatures);

    double accRaw = cvRaw.validate() * 100.0;
    double accNorm = cvNorm.validate() * 100.0;

    cout <<"\n-- Normalization check --\n";
    cout << "Dataset: " << filename << "\n";
    cout << "Unnormalized accuracy (ALL FEATURES): " << fixed << setprecision(1) << accRaw << "%\n";
    cout <<" Normalized accuracy (ALL FEATURES): " << fixed << setprecision(1) << accNorm << "%\n";
}

int main() {
    // part 1 code
    srand(time(0));

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
        filename = "src/titanic_clean_generated.txt";
    } else {
        cout << "Invalid choice, exiting...\n";
        return 0;
    }

    loadDataset(filename, globalX, globalY);

    checkNormalizationEffect(filename);

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
}