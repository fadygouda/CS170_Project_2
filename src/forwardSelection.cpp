#include <iostream>
#include <vector> 
#include <cmath>
#include <algorithm>
#include <iomanip>
#include "../headers/forwardSelection.h"
using namespace std;



extern double evaluate(const vector<int>& featureSet);

double roundUp (double x) {
    return floor (x * 10 + 0.5) / 10;
}

void forwardSelection (int totalFeatures) {

    vector<int> best_features; // best feature found so far
    vector<int> emptySet; // starting empty set
    double best_accuracy = evaluate(emptySet); // Make initial evaluation with no features our best accuracy to start

    cout << "\nRunning Forward Selection...\n";
    cout << "Using no features and \"random\" evaluation, I get an accuracy of " << fixed << setprecision(1) << roundUp(best_accuracy) << "%\n";
    cout << "\nBeginning search.\n";

    double bestOverallAccuracy = best_accuracy;
    vector<int> bestOverallSet = best_features;

    for (int step = 0; step < totalFeatures; step++) {
        int curr_bestFeature = -1; // best feature to add during the step
        double curr_bestAccuracy = -1.0;

        for (int feature = 1; feature <= totalFeatures; feature++) { // for adding feature not already in the current set 
            if (find(best_features.begin(), best_features.end(), feature) == best_features.end()) { // if feature is already found in set, skip
                // a candidate feature to add and evaluate to see if we should keep 
                vector<int> temp_features = best_features;
                temp_features.push_back(feature);
                double accuracy = evaluate(temp_features);

                cout << "Using feature(s) { ";
                for (int f : temp_features) cout << f << " ";
                cout << "} accuracy is " << roundUp(accuracy) << "%\n";

                // if accuracy is the best we have seen, keep it

                if (accuracy > curr_bestAccuracy) {
                    curr_bestFeature = feature;
                    curr_bestAccuracy = accuracy;
                }
            }
        }

        if (curr_bestFeature == -1) {
            cout << "(No improvement in accuracy, stopping search.)\n";
            break;
        }

        if (curr_bestAccuracy < best_accuracy) {
            cout << "(Warning, Accuracy has decreaed!)\n";
        }
        // add best new feature to feature set 
        best_features.push_back(curr_bestFeature);
        best_accuracy = curr_bestAccuracy;


        cout << "\nFeature set {";
        for (int f : best_features) cout << f << " ";
        cout << "} was best,  accuracy is " << roundUp(best_accuracy) << "%\n"; 
        // check if this is the best overall accuracy we have seen
        if (best_accuracy > bestOverallAccuracy) {
            bestOverallAccuracy = best_accuracy;
            bestOverallSet = best_features;
        }
    }

    //printing final outcome
    cout << "\nFinished search! The best feature subset is { ";
    for (int f : bestOverallSet) cout << f << " ";
    cout << "}, which has an accuracy of " << roundUp(bestOverallAccuracy) << "%\n";
}