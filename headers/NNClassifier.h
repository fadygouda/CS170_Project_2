#ifndef NNCLASSIFIER_H
#define NNCLASSIFIER_H

#include <vector>
using namespace std;

//Stores training data in memory and classifies new points by 
//finding the closest training instance using Euclidean distance
class NearestNeighborClassifier
{

public:
    //Saves the training dataset and labels
    //X = feature vectors for all training examples
    //Y = class labels that represent each vector
    void train(const vector<vector<double>>& trainingFeatures, const vector<int>& trainingLabels);

    //Predict the class label for 1 test sample
    //x = feature vector that is tested and returns the predicted class label (1 or 2)
    int test(const vector<double>& testFeatures);

private:
    //storing feature vectors from training data
    vector<vector<double>> storedTrainingFeatures;

    //storing corresponding class labels
    vector<int> storedTrainingLabels;

    //computing Euclidean distance
    double computeEuclideanDistance(const vector<double>& featureVector1, const vector<double>& featureVector2);


};

#endif
