#include <iostream>
#include <vector> 
#include <cmath>
using namespace std;

extern double evaluate(const vector<int>& featureSet);

double roundUp (double x) {
    return floor (x * 10 + 0.5) / 10;
}

void forwardSelection (int totalFeatures) {
    cout << "\nRunning Forward Selection...\n";
    cout << "Using no features and \"random\" evaluation, I get an accuracy of 55.4%\n";
    cout << "\nBeginning search.\n";

    vector<int> best_features;
    double best_accuracy;

    for (int step = 0; step < totalFeatures; step++) {
        int curr_bestFeature = -1; 
        double curr_bestAccuracy = best_accuracy;

        for (int feature = 1; feature <= totalFeatures; feature++) {
            if (find(best_features.begin(), best_features.end(), feature) == best_features.end()) {
                vector<int> temp_features = best_features;
                temp_features.push_back(feature);
                double accuracy = evaluate(temp_features);

                cout << "Using feature(s) { ";
                for (int f : temp_features) cout << f << " ";
                cout << "} accuracy is " << roundUp(accuracy) << "%\n";

                if (accuracy > curr_bestAccuracy) {
                    curr_bestFeature = feature;
                    curr_bestAccuracy = accuracy;
                }
            }
        }
        if (curr_bestFeature != 1) {
            best_features.push_back(curr_bestFeature);
            best_accuracy = curr_bestAccuracy;
            cout << "\nFeature set {";
            for (int f : best_features) cout << f << " ";
            cout << "} was best,  accuracy is " << roundUp(best_accuracy) << "%\n"; 
        } else {
            cout << "No improvement is accuracy, stopping search.\n"; 
            break;
        }
    }
    cout << "\nFinished search! The best feature subset is { ";
    for (int f : best_features) cout << f << " ";
    cout << "}, which has an accuracy of " << roundUp(best_accuracy) << "%\n";
}