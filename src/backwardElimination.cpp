#include "../headers/backwardElimination.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

extern double evaluate(const vector<int>& featureSet);

void printFeatureSet(const vector<int>& s) {
    cout << "{";
    for (size_t i=0; i < s.size(); i++) {
        if (i > 0) cout << ",";
        cout << s[i];
    }
    cout << "}";
}

void backwardElimination(int totalFeatures) {
    vector<int> currentSet;
    for (int i=1; i <=totalFeatures; i++) {
        currentSet.push_back(i);
    }

    double bestOverallAccuracy = evaluate(currentSet);
    vector<int> bestOverallSet = currentSet;

    cout << "Using all features and \"random\" evaluation, I get an accuracy of "
        << fixed << setprecision(1) << bestOverallAccuracy << "%\n";
    cout << "Beginning search.\n";

    while (currentSet.size() > 1) {
        double bestAccuracyThisLevel = -1.0;
        int featureToRemove = -1;
        vector <int> bestSetThisLevel;

        for (size_t i = 0; i < currentSet.size(); i++) {
            int candidate = currentSet[i];

            vector <int> trialSet = currentSet;
            trialSet.erase(trialSet.begin() + static_cast<long>(i));

            double acc = evaluate(trialSet);

            cout << "Using Feature(s) ";
            printFeatureSet(trialSet);
            cout <<" the accuracy is " << fixed << setprecision(1) << acc << "%\n";


            if (acc > bestAccuracyThisLevel) {
                bestAccuracyThisLevel = acc;
                featureToRemove = candidate;
                bestSetThisLevel = trialSet;
            }
        }

        if (bestAccuracyThisLevel < bestOverallAccuracy) {
            cout << "(Warning, Accuracy has decreased!)\n";
        } 

        cout << "Feature set ";
        printFeatureSet(bestSetThisLevel);
        cout << " was best, accuracy is " << fixed << setprecision(1) << bestAccuracyThisLevel << "\n";

        currentSet.erase(remove(currentSet.begin(), currentSet.end(), featureToRemove), currentSet.end());

        if (bestAccuracyThisLevel > bestOverallAccuracy) {
            bestOverallAccuracy = bestAccuracyThisLevel;
            bestOverallSet = bestSetThisLevel;
        } 
    }

    cout << "Finished search! The best feature subset is ";
    printFeatureSet(bestOverallSet);
    cout << ", with an accuracy of " << fixed << setprecision(1) << bestOverallAccuracy << "%\n";
}
