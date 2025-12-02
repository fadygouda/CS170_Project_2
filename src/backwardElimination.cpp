#include "../headers/backwardElimination.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

extern double evaluate(const vector<int>& featureSet);

//Helper function to print feature set like {1,2,3}
void printFeatureSet(const vector<int>& s) {
    cout << "{";
    for (size_t i=0; i < s.size(); i++) {
        if (i > 0) cout << ",";
        cout << s[i];
    }
    cout << "}";
}

void backwardElimination(int totalFeatures) {
    //Feature set we are testing 
    vector<int> currentSet;

    //Start with all features because this is backwardElimination
    for (int i=1; i <=totalFeatures; i++) {
        currentSet.push_back(i);
    }

    //Evaluate the accuracy using all features at the start
    double bestOverallAccuracy = evaluate(currentSet);
    //Remember best feature set so far
    vector<int> bestOverallSet = currentSet;

    //Print the initial line
    cout << "Using all features and \"random\" evaluation, I get an accuracy of " << fixed << setprecision(1) << bestOverallAccuracy << "%\n";
    cout << "Beginning search.\n";

    //Remove one feature at each level as long as we have more than 1 feature
    while (currentSet.size() > 1) {
        //Best accuracy found for this level 
        double bestAccuracyThisLevel = -1.0;
        //Reature thats going to be removed
        int featureToRemove = -1;
        //Feature that given bestAccuracyThisLevel
        vector <int> bestSetThisLevel;

        //Removing one feature at a time
        for (size_t i = 0; i < currentSet.size(); i++) {
            //Candidate feature to remove
            int candidate = currentSet[i];
            
            //Starting from current set/Assigning the trial set with currentSet
            vector <int> trialSet = currentSet;

            //Erase feature at index i from trial set
            trialSet.erase(trialSet.begin() + static_cast<long>(i));
            //Evaluate accuracy of trialSet
            double acc = evaluate(trialSet);
            //Print trialSet
            cout << "Using Feature(s) ";
            printFeatureSet(trialSet);
            cout <<" the accuracy is " << fixed << setprecision(1) << acc << "%\n";

            //If the trial set is the best accuracy that was seen, then remember
            if (acc > bestAccuracyThisLevel) {
                bestAccuracyThisLevel = acc;    //new best accuracy
                featureToRemove = candidate;    //remove feature from currentSet
                bestSetThisLevel = trialSet;    //save feature set
            }
        }

        //Warn user if the best accuracy at the level is worse than the best overall accuracy
        if (bestAccuracyThisLevel < bestOverallAccuracy) {
            cout << "(Warning, Accuracy has decreased!)\n";
        } 

        //Print the best feature set at this level
        cout << "Feature set ";
        printFeatureSet(bestSetThisLevel);
        cout << " was best, accuracy is " << fixed << setprecision(1) << bestAccuracyThisLevel << "\n";

        //Removing chosen feature from current set
        currentSet.erase(remove(currentSet.begin(), currentSet.end(), featureToRemove), currentSet.end());

        //Update global best if this level has a better accuracy than before
        if (bestAccuracyThisLevel > bestOverallAccuracy) {
            bestOverallAccuracy = bestAccuracyThisLevel;
            bestOverallSet = bestSetThisLevel;
        } 
    }

    //Print best feature from whole set
    cout << "Finished search! The best feature subset is ";
    printFeatureSet(bestOverallSet);
    cout << ", with an accuracy of " << fixed << setprecision(1) << bestOverallAccuracy << "%\n";
}
