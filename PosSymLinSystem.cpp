#include "PosSymLinSystem.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>

// Constructor checks symmetry
PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b)
{
    if (!IsSymmetric()) {
        throw std::invalid_argument("Matrix must be symmetric for PosSymLinSystem.");
    }
}

// Conjugate Gradient Solver for symmetric positive definite systems
Vector PosSymLinSystem::Solve() const
{
    const Matrix& A = *mpA;
    const Vector& b = *mpb;
    Vector x(mSize); // Initial guess: zero vector
    Vector r = b - A * x;
    Vector p = r;
    double rs_old = r * r;

    constexpr double tol = 1e-10;
    const double tol_sq = tol * tol;
    const int max_iter = std::min(1000, static_cast<int>(mSize) * 10);

    for (int i = 0; i < max_iter; ++i) {
        Vector Ap = A * p;
        double denom = p * Ap;
        if (std::abs(denom) < tol) {
            // Matrix may not be positive definite
            break;
        }
        double alpha = rs_old / denom;

        x = x + alpha * p;
        r = r - alpha * Ap;

        double rs_new = r * r;
        if (rs_new < tol_sq) {
            return x;
        }

        double beta = rs_new / rs_old;
        p = r + beta * p;
        rs_old = rs_new;
    }

    return x;
}

// Check if the matrix is symmetric
bool PosSymLinSystem::IsSymmetric() const
{
    constexpr double tolerance = 1e-10;
    for (std::size_t i = 1; i <= static_cast<std::size_t>(mSize); ++i) {
        for (std::size_t j = i + 1; j <= static_cast<std::size_t>(mSize); ++j) {
            if (std::abs((*mpA)(i, j) - (*mpA)(j, i)) > tolerance) {
                return false;
            }
        }
    }
    return true;
}