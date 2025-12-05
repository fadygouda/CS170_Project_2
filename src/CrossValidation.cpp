#include "../headers/CrossValidation.h"
#include <iostream>
#include <chrono>
#include <iomanip>


CrossValidation::CrossValidation(NearestNeighborClassifier& classifier, const std::vector<std::vector<double>>& x, const std::vector<int>& y, const std::vector<int>& featureSubset) : classifier(classifier), x(x), y(y), featureSubset(featureSubset) {}

double CrossValidation::validate() {
    int correctPredictions = 0;
    int totalPredictions = static_cast<int>(x.size());

    if (totalPredictions == 0 || featureSubset.empty()) {
        return 0.0;
    }

    std::vector<std::vector<double>> train_x;
    std::vector<int> train_y;
    std::vector<double> test_x;

    train_x.reserve(totalPredictions - 1);
    train_y.reserve(totalPredictions -1);
    test_x.reserve(featureSubset.size());

    for (int i = 0; i < totalPredictions; ++i) {

        // auto start = chrono::high_resolution_clock::now(); trace for part 2

        train_x.clear();
        train_y.clear();
        test_x.clear();

        for (int feature : featureSubset) {
            int colIndex = feature;
            test_x.push_back(x[i][colIndex]);
        }

        for (int j = 0; j < totalPredictions; j++) {
            if (j == i) continue;

            std::vector<double> filtered_row;
            filtered_row.reserve(featureSubset.size());

            for (int feature : featureSubset) {
                int colIndex = feature;
                filtered_row.push_back(x[j][colIndex]);
            }

            train_x.push_back(filtered_row);
            train_y.push_back(y[j]);
        }

        classifier.train(train_x, train_y);
        int predicted = classifier.test(test_x);

        if (predicted == y[i]) {
            correctPredictions++;
        }


        // trace for part 2 below
        // auto end = chrono::high_resolution_clock::now();
        // double stepTime = chrono::duration<double, std::milli>(end - start).count();
        // cout << "Step " << i << ": true=" << y[i] << ", predicted=" << predicted <<", time=" << fixed << setprecision(3) << stepTime << " ms\n";
    }
    return static_cast<double>(correctPredictions) / totalPredictions;
}
