#include "NNClassifier.h"

#include <limits>
#include <cmath>

//Stores training data
void NearestNeighborClassifier::train(const vector<vector<double>>& trainingFeatures, const vector<int>& trainingLabels)
{
    //Storing training feature vectors 
    storedTrainingFeatures = trainingFeatures;

    //Storing the corresponding class labels
    storedTrainingLabels = trainingLabels;
}

//Finds closest training instance and returns predicted class label
int NearestNeighborClassifier::test(const vector<double>& testFeatures)
{
    //Initialize min distance to a large number b/c the initial minimum distance must start larger than any 
    //real distance so the first computed distance will replace it as the current closest neighbor
    double closestDistance = numeric_limits<double>::max();

    //Storing the predicted label
    int predictedClassLabel = -1;

    //Go over each stored training vector
    for (size_t i = 0; i < storedTrainingFeatures.size(); ++i)
    {
        //Calculate distance between test instance and training example; Used below to compare to other closer distances
        double currentDistance = computeEuclideanDistance(testFeatures, storedTrainingFeatures[i]);

        //Update NN: checks whether the current training example is closer than any previously seen example
        //If it is the closest, updates closestDistance and predictedClassLabel to match closest neighbor
        if (currentDistance < closestDistance)
        {
            closestDistance = currentDistance;
            predictedClassLabel = storedTrainingLabels[i];
        }
    }

    //Returns predicted class label of nearest neighbor
    return predictedClassLabel;
}

//Euclidean distance is the straight-line distance between two points: d = sqrt[(x-x)^2 + (y-y)^2]
//Subtract the same feature in each vector, square the differences, add them together, 
//then take the square root to get the distance between two points

//Example: x1 = (1.5, 2.5, 3.5), x2 = (4.5, 5.5, 6.5) (note these are standalone numbers and not coordinates)
//d = sqrt[(1.5 - 4.5)^2 + (2.5 - 5.5)^2 + (3.5 - 6.5)^2] 
double NearestNeighborClassifier::computeEuclideanDistance(const vector<double>& featureVector1, const vector<double>& featureVector2)
{
    //Sum of differences
    double sum = 0.0;

    //Computing Euclidean distance (without square rooting)
    for (size_t i = 0; i < featureVector1.size(); ++i)
    {
        //Difference of current feature values
        double featureDifference = featureVector1[i] - featureVector2[i];
        //Square and add
        sum += featureDifference * featureDifference;
    }

    //Return sqrt of sum to get distance
    return sqrt(sum);
}
