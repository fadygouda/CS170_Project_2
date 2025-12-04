#include "../headers/CrossValidation.h"
#include <iostream>
#include <chrono>
#include <iomanip>


CrossValidation::CrossValidation(NearestNeighborClassifier& classifier, const std::vector<std::vector<double>>& x, const std::vector<int>& y, const std::vector<int>& featureSubset) : classifier(classifier), x(x), y(y), featureSubset(featureSubset) {}

//this is LEAVES ONE OUT CROSS VALIDATION
// will return accuracy based on correct predictions / total predictions
double CrossValidation::validate() {

    int correctPredictions = 0;
    // we are using static cast for the size_t to int conversion to avoid potential warnings
    int totalPredictions = static_cast<int>(x.size());

    if (totalPredictions == 0 || featureSubset.empty()) {
        return 0.0;
    }

    std::vector<std::vector<double>> train_x; // input rows
    std::vector<int> train_y; // labels 
    std::vector<double> test_x; // single test row

    // .reserve to optimize memory allocations and reserve memory
    train_x.reserve(totalPredictions - 1);
    train_y.reserve(totalPredictions -1);
    test_x.reserve(featureSubset.size());

    // looping over each instance to use as 1 instance
    for (int i = 0; i < totalPredictions; ++i) {

        // auto start = chrono::high_resolution_clock::now(); trace for part 2

        // prepare train and test sets
        train_x.clear();
        train_y.clear();
        test_x.clear();

        // extract feature values for each test instance 
        for (int feature : featureSubset) {
            int colIndex = feature;
            test_x.push_back(x[i][colIndex]);
        }

        // building training set including all rows but the test instance
        for (int j = 0; j < totalPredictions; j++) {
            if (j == i) continue; // skip the test instance

            // extract only selected feature columns from row j
            std::vector<double> filtered_row;
            filtered_row.reserve(featureSubset.size());


            // looping through each feature index we want to include 
            // we use this "filter" to really just keep only a reduced version of each sample 
            for (int feature : featureSubset) {
                int colIndex = feature;
                filtered_row.push_back(x[j][colIndex]);
            }

            train_x.push_back(filtered_row);
            train_y.push_back(y[j]);
        }

        // train classifier on remaining rows 
        classifier.train(train_x, train_y);
        // predict label for test row i 
        int predicted = classifier.test(test_x);
        // if prediction is correct, increment correct count
        if (predicted == y[i]) {
            correctPredictions++;
        }

        // trace for part 2 below
        // auto end = chrono::high_resolution_clock::now();
        // double stepTime = chrono::duration<double, std::milli>(end - start).count();
        // cout << "Step " << i << ": true=" << y[i] << ", predicted=" << predicted <<", time=" << fixed << setprecision(3) << stepTime << " ms\n";
    }
    //percentage of correct predictions
    return static_cast<double>(correctPredictions) / totalPredictions;
}
