#include "../headers/CrossValidation.h"
#include <iostream>
#include <chrono>
#include <iomanip>


CrossValidation::CrossValidation(NearestNeighborClassifier& classifier, const std::vector<std::vector<double>>& x, const std::vector<int>& y, const std::vector<int>& featureSubset) : classifier(classifier), x(x), y(y), featureSubset(featureSubset) {}

double CrossValidation::validate() {
    int correctPredictions = 0;
    int totalPredictions = x.size();

    for (int i = 0; i < totalPredictions; ++i) {

        auto start = chrono::high_resolution_clock::now();

        std::vector<std::vector<double>> train_x = x;
        std::vector<int> train_y = y;
        std::vector<double> test_x;
        
        train_x.erase(train_x.begin() + i);
        train_y.erase(train_y.begin() + i);

        for (int feature : featureSubset) {
            int colIndex = feature;
            test_x.push_back(x[i][colIndex]);
        }

        std::vector<std::vector<double>> filtered_train_x;
        for (const auto& row : train_x) {
            std::vector<double> filtered_row;
            for (int feature : featureSubset) {
                int colIndex = feature;
                filtered_row.push_back(row[colIndex]);
            }
            filtered_train_x.push_back(filtered_row);
        }

        classifier.train(filtered_train_x, train_y);

        int predicted = classifier.test(test_x);
        if (predicted == y[i]) {
            ++correctPredictions;
        }

        auto end = chrono::high_resolution_clock::now();
        double stepTime = chrono::duration<double, std::milli>(end - start).count();

        cout << "Step " << i << ": true=" << y[i] << ", predicted=" << predicted <<", time=" << fixed << setprecision(3) << stepTime << " ms\n";
    }
    return static_cast<double>(correctPredictions) / totalPredictions;
}
