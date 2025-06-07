#include "LinearSystem2.hpp"
#include "LinearSystem.hpp"
#include "Matrix.hpp"
#include <stdexcept>
#include <cmath>

LinearSystem2::LinearSystem2(const Matrix& A, const Vector& b) {
    if (A.GetNumRows() != b.GetSize()) {
        throw std::invalid_argument("Matrix and vector dimensions must agree");
    }
    mRows = A.GetNumRows();
    mCols = A.GetNumCols();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem2::~LinearSystem2() {
    delete mpA;
    delete mpb;
}

// Ordinary Least Squares: x = (A^T A)^(-1) A^T b
Vector LinearSystem2::SolvewithMoore_Penrose(Matrix& A,  Vector& b) const {
    return A.pseudoinverse() * b;
}

Vector LinearSystem2::SolveWithTikhonov(Matrix& A,  Vector& b) {
    Matrix A_t = A.transpose();
    float lambda=0.01;
    if (A.GetNumRows() >= A.GetNumCols()) {
        // over-determined (A^T A + λI)^-1 A^T b
        Matrix ATA = A_t * A;
        int n = A.GetNumCols();
        Matrix lambda_ver = ATA + ATA.identity(n) * lambda;
        return lambda_ver.inverse() * A_t * b;
    } else {
        // under-determined A^T (A A^T + λI)^-1 b
        Matrix AAT = A * A_t;
        int m = A.GetNumCols();
        Matrix lambda_ver = AAT + AAT.identity(m) * lambda;
        return A_t * lambda_ver.inverse() * b;
    }
}