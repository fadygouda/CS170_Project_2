#ifndef FEATURESELECTION_H
#define FEATURESELECTION_H
#include <vector>

using namespace std;

void forwardSelection (int total);
void backwardElimination (int total, const vector<vector<double>>& x, const vector<int>& y);

#endif