# CS170_Project_2

CS170 Project 2 Search

Part 1 includes the implementation of backwardElimination.cpp and forwardSelection.cpp

In Part two we implemented the NN-Classifier functionality which trains, tests and computes the Euclidian Distance for our selected feature set. The CrossValidation employs the NN Classifier to validate the testing and make predictions according to the data on the dataset. Main.cpp loads and parses the data so that the validate function can properly work with the data to make predictions on accuracy.

In Part 3 we tied both Part 1 and Part 2 together by running the forward selection and backward elimnation search algorithms on the given small, large and titanic datasets. We rewrote our evaluate function that both the forward and backward algorithms run as the fitness function instead of generating random numbers as we had it in part 1. It determines which subset is best, which direction to search, when accuracy increases or decreases and what the final best subset is.

Cristian Roberts, Marc Encarnacion and Fady Gouda worked together on this project
