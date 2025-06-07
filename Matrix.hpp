#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <iostream>
#include "Vector.hpp"
using namespace std;
class Matrix {
    private:
        int mNumRows;
        int mNumCols;
        double** mData;
    public:
    // Constructors and destructor
    Matrix();
    Matrix(const Matrix& m);
    Matrix(int numRows, int numCols);
    ~Matrix();
    int GetNumRows() const { return mNumRows; }
    int GetNumCols() const { return mNumCols; }
    double GetData(int r, int c) const { return mData[r][c]; }
    //Round bracket operator
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
    //Assignment operator
    Matrix& operator=(const Matrix& m);
    //Unary operator
    Matrix operator-() const;
    Matrix operator+() const;
    //Binary operators
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& m);
    Vector operator*(const Vector& v) const;
    //Determinant 
    double determinant() const;
    //Inverse
    Matrix inverse() const;
    //Moore-Penrose Pseudoinverse
    Matrix transpose() const;
    Matrix pseudoinverse() const;
    Matrix identity (int size);
};

#endif