#include "LinearRegressionPrediction.hpp"
#include "LinearSystem2.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
using namespace std;

LinearRegression::LinearRegression()
    : weights(),  // Start with empty weights
      trained(false) {}

void LinearRegression::train(const Matrix& A, const Vector& b) {
    assert(A.GetNumRows() == b.GetSize() && "Number of rows in A must match size of b.");
    Matrix A_copy = A;
    Vector b_copy = b;
    LinearSystem2 sys(A_copy, b_copy);
    weights = sys.SolveWithTikhonov(A_copy, b_copy);
    trained = true;
}

Vector LinearRegression::predict(const Matrix& A) const {
    assert(trained && "Model is not trained.");
    assert(A.GetNumCols() == weights.GetSize() && "Feature size mismatch in prediction.");
    return A * weights;
}

double LinearRegression::rmse(const Vector& predictions, const Vector& targets) const {
    int n = predictions.GetSize();
    assert(n == targets.GetSize() && n != 0 && "Size mismatch or empty vectors in RMSE calculation.");
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = predictions(i+1) - targets(i+1);
        sum += diff * diff;
    }
    return sqrt(sum / n);
}

void LinearRegression::printWeights() const {
    if (!trained) {
        cout << "Model is not trained.\n";
        return;
    }
    cout << "Weights:\n";
    cout << fixed << setprecision(6);
    for (int i = 0; i < weights.GetSize(); i++)
        cout << "w" << i << ": " << weights(i+1) << "\n";
}
