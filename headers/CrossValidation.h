#ifndef CROSSVALIDATION_H
#define CROSSVALIDATION_H

#include "NNClassifier.h"
#include <vector>

class CrossValidation {
    private:
        NearestNeighborClassifier& classifier;
        const std::vector<std::vector<double> >& x;
        const std::vector<int>& y;
        const std::vector<int>& featureSubset;

    public:
        CrossValidation(NearestNeighborClassifier& classifier, const std::vector<std::vector<double> >& x, const std::vector<int>& y, const std::vector<int>& featureSubset);
        double validate();

};

#endif