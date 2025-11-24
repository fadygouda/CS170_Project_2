#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// header files

using namespace std;

double evaluate(const vector<int>& featureSet) {
    return (rand() % 1000) / 10.0;
}

int main() {
    srand(time(0));

    cout << "Welcome to our Feature Selection Algorithm! \n";
    cout << "Please enter the total number of features: ";

    int totalFeatures;
    cin >> totalFeatures;

    cout << "\nType the number of the algorithm you would like to run.\n";
    cout << "1. Forward Selection\n";
    cout << "2. Backward Elimination\n";
    cout << "Enter your selection: ";

    int selection;
    cin >> selection;

    cout << endl;

    if (selection == 1) {
        forwardSelection(totalFeatures);
    }
    else if (choice == 2) {
        backwardElimination(totalFeatures);
    }
    else {
        cout << "Invalid choice, exiting...\n";
    }

    return 0;


}