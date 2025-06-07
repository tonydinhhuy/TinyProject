#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "LinearRegressionPrediction.hpp"
using namespace std;

#define FEATURES 6
#define TOTAL_FEATURES FEATURES + 1
#define SAMPLES 209

// Shuffle indices
void shuffle(int* indices, int n) {
    for (int i = n - 1; i > 0; --i) {    
        int j = rand() % (i + 1);
        swap(indices[i], indices[j]);
    }
}

int main() {
    double features[SAMPLES][FEATURES];  // Input features
    double targets[SAMPLES];             // Target values

    ifstream file("machine.data");
    assert(file && "Error: Cannot open machine.data");

    string line;
    int row = 0;
    while (getline(file, line) && row < SAMPLES) {
        stringstream ss(line);
        string token;
        // Skip first 2 columns
        getline(ss, token, ',');
        getline(ss, token, ',');

        // Read features
        for (int i = 0; i < FEATURES; ++i) {
            getline(ss, token, ',');
            features[row][i] = stod(token);
        }

        // Read target
        getline(ss, token, ',');
        targets[row] = stod(token);
        ++row;
    }
    file.close();

    // Shuffle data
    int indices[SAMPLES];
    for (int i = 0; i < SAMPLES; ++i) indices[i] = i;
    srand(0);
    shuffle(indices, SAMPLES);

    // Split 80% train, 20% test
    int train_size = SAMPLES * 80 / 100;
    int test_size = SAMPLES - train_size;

    // Mean and std for each feature
    double feature_means[FEATURES] = {0};
    double feature_stds[FEATURES] = {0};

    // Compute mean
    for (int j = 0; j < FEATURES; ++j) {
        double sum = 0.0;
        for (int i = 0; i < train_size; ++i) {
            int idx = indices[i];
            sum += features[idx][j];
        }
        feature_means[j] = sum / train_size;
    }
   
    // Compute std
    for (int j = 0; j < FEATURES; ++j) {
        double sum_sq = 0.0;
        for (int i = 0; i < train_size; ++i) {
            int idx = indices[i];
            double diff = features[idx][j] - feature_means[j];
            sum_sq += diff * diff;
        }
        feature_stds[j] = sqrt(sum_sq / train_size);
        if (feature_stds[j] < 1e-7) {
            feature_stds[j] = 1.0;
        }
    }

    // Prepare train and test matrices
    Matrix A_train(train_size, TOTAL_FEATURES);
    Vector b_train(train_size);
    Matrix A_test(test_size, TOTAL_FEATURES);
    Vector b_test(test_size);

    // Fill training data
    for (int i = 0; i < train_size; ++i) {
        int idx = indices[i];
        A_train(i+1, 1)= 1.0; // bias
        for (int j = 0; j < FEATURES; ++j) {
            double scaled_value = (features[idx][j] - feature_means[j]) / feature_stds[j];
            A_train(i+1, j + 2)= scaled_value;
        }
        b_train(i+1)= targets[idx];
    }

    // Fill test data
    for (int i = 0; i < test_size; ++i) {
        int idx = indices[train_size + i];        
        A_test(i+1, 1)= 1.0; // bias
        for (int j = 0; j < FEATURES; ++j) {
            double scaled_value = (features[idx][j] - feature_means[j]) / feature_stds[j];
            A_test(i+1, j + 2)= scaled_value;
        }
        b_test(i+1) =targets[idx];
    }

    // Train and evaluate
    LinearRegression model;
    model.train(A_train, b_train);
    Vector predictions = model.predict(A_test);
    double error = model.rmse(predictions, b_test);

    cout << "Root Mean Squared Error: " << error << "\n\n";
    model.printWeights();

    return 0;
}
