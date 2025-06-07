#include "Matrix.hpp"
#include "Vector.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;
Matrix::Matrix() {
    mNumRows = 0;
    mNumCols = 0;
    mData = nullptr;
}
Matrix::Matrix(const Matrix& m){
    mNumRows= m.mNumRows;
    mNumCols = m.mNumCols;
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = m.mData[i][j];
        }
    }
}
Matrix::Matrix(int numRows, int numCols) {
    mNumRows = numRows;
    mNumCols = numCols;
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = 0.0;
        }
    }
}
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}
Matrix& Matrix::operator=(const Matrix& m) {
    if (this != &m) {
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;

        mNumRows = m.mNumRows;
        mNumCols = m.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j) {
                mData[i][j] = m.mData[i][j];
            }
        }
    }
    return *this;
}
double& Matrix::operator()(int i, int j) {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
        assert("Matrix indices out of range");
    }
    return mData[i - 1][j - 1];
}

const double& Matrix::operator()(int i, int j) const {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
        assert("Matrix indices out of range");
    }
    return mData[i - 1][j - 1];
}
Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = -mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator+() const {
    return *this;
}
Matrix Matrix::operator+(const Matrix& m) const {
    if (mNumRows != m.mNumRows || mNumCols != m.mNumCols) {
        assert("Matrices must have the same dimensions for addition");
    }
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = mData[i][j] + m.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator-(const Matrix& m) const {
    if (mNumRows != m.mNumRows || mNumCols != m.mNumCols) {
        assert("Matrices must have the same dimensions for subtraction");
    }
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = mData[i][j] - m.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator*(const Matrix& m) const {
    if (mNumCols != m.mNumRows) {
        assert("Matrices must have compatible dimensions for multiplication");
    }
    Matrix result(mNumRows, m.mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < m.mNumCols; ++j) {
            result(i + 1, j + 1) = 0.0;
            for (int k = 0; k < mNumCols; ++k) {
                result(i + 1, j + 1) += mData[i][k] * m.mData[k][j];
            }
        }
    }
    return result;
}
Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1, j + 1) = mData[i][j] * scalar;
        }
    }
    return result;
}
Matrix operator*(double scalar, const Matrix& m) {
    return m * scalar;
}
Vector Matrix::operator*(const Vector& v) const {
    if (mNumCols != v.GetSize()) {
        assert("Matrix and vector dimensions must agree for multiplication");
    }
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        result(i + 1) = 0.0;
        for (int j = 0; j < mNumCols; ++j) {
            result(i + 1) += mData[i][j] * v(j + 1);
        }
    }
    return result;
}
double Matrix::determinant() const {
    if (mNumRows != mNumCols) {
        assert("Determinant is only defined for square matrices");
    }
    int n = mNumRows;
    if (n == 1) {
        return mData[0][0];
    }
    if (n == 2) {
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    }
    double det = 0.0;
    for (int p = 0; p < n; ++p) {
        Matrix subMat(n - 1, n - 1);
        for (int i = 1; i < n; ++i) {
            int colIdx = 0;
            for (int j = 0; j < n; ++j) {
                if (j == p) continue;
                subMat(i, colIdx + 1) = mData[i][j];
                ++colIdx;
            }
        }
        double sign = (p % 2 == 0) ? 1.0 : -1.0;
        det += sign * mData[0][p] * subMat.determinant();
    }
    return det;
}
Matrix Matrix::inverse() const {
    if (mNumRows != mNumCols) {
        throw ("Matrix must be square to compute inverse");
    }
    int n = mNumRows;
    Matrix result(n, n);
    Matrix temp(*this);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                result(i + 1, j + 1) = 1.0;
            } else {
                result(i + 1, j + 1) = 0.0;
            }
        }
    }

    for (int col = 0; col < n; ++col) {
        int maxRow = col;
        double maxVal = abs(temp(col + 1, col + 1));
        for (int row = col + 1; row < n; ++row) {
            if (abs(temp(row + 1, col + 1)) > maxVal) {
                maxVal = abs (temp(row + 1, col + 1));
                maxRow = row;
            }
        }

        if (maxVal < 1e-10) {
            assert("Matrix is singular and cannot be inverted");
        }

        if (maxRow != col) {
            for (int j = 0; j < n; ++j) {
                swap(temp(col + 1, j + 1), temp(maxRow + 1, j + 1));
                swap(result(col + 1, j + 1), result(maxRow + 1, j + 1));
            }
        }

        double pivot = temp(col + 1, col + 1);
        for (int j = 0; j < n; ++j) {
            temp(col + 1, j + 1) /= pivot;
            result(col + 1, j + 1) /= pivot;
        }

        for (int row = 0; row < n; ++row) {
            if (row != col) {
                double factor = temp(row + 1, col + 1);
                for (int j = 0; j < n; ++j) {
                    temp(row + 1, j + 1) -= factor * temp(col + 1, j + 1);
                    result(row + 1, j + 1) -= factor * result(col + 1, j + 1);
                }
            }
        }
    }
    return result;
}
Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result(j + 1, i + 1) = mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::pseudoinverse() const {
    if (mNumRows >= mNumCols) {
        Matrix At = this->transpose();
        Matrix AtA = At * (*this);
        Matrix AtA_inv = AtA.inverse();
        return AtA_inv * At;
    } else {
        Matrix At = this->transpose();
        Matrix AAt = (*this) * At;
        Matrix AAt_inv = AAt.inverse();
        return At * AAt_inv;
    }
}
Matrix Matrix::identity(int size) {
    Matrix result(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                result(i + 1, j + 1) = 1.0;
            } else {
                result(i + 1, j + 1) = 0.0;
            }
        }
    }
    return result;
}