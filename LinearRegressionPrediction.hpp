#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "Matrix.hpp"

class LinearRegression {
private:
    Vector weights;
    bool trained;

public:
    LinearRegression();
    void train(const Matrix& A, const Vector& b);
    Vector predict(const Matrix& A) const;
    double rmse(const Vector& predictions, const Vector& targets) const;
    void printWeights() const;
};

#endif
