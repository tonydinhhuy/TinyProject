#include "Vector.hpp"
#include <cassert>
using namespace std;
Vector::Vector(){
    mSize = 0;
    mData = nullptr;
}
Vector::Vector(int size){
    mSize = size;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = 0.0;
    }
}
Vector::Vector(const Vector& v) {
    mSize = v.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = v.mData[i];
    }
}
Vector::~Vector() { 
    delete[] mData;
}
int Vector::GetSize() const {
    return mSize;
}
Vector& Vector::operator=(const Vector& v) {
    delete[] mData;
    mSize = v.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = v.mData[i];
    }
    return *this;
}
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = -mData[i];
    }
    return result;
}
Vector Vector::operator+() const {
    return *this;
}
Vector Vector::operator+(const Vector& v) const {
    assert(mSize == v.mSize && "Vectors must be of the same size for addition.");
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + v.mData[i];
    }
    return result;
}
Vector Vector::operator-(const Vector& v) const {
    assert(mSize == v.mSize && "Vectors must be of the same size for subtraction.");
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - v.mData[i];
    }
    return result;
}
Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] * scalar;
    }
    return result;
}
Vector operator*(double scalar, const Vector& v) {
    return v * scalar;
}
double Vector::operator*(const Vector& v) const { // Dot product
    assert(mSize == v.mSize && "Vectors must be of the same size for dot product.");
    double result = 0.0;
    for (int i = 0; i < mSize; ++i) {
        result += mData[i] * v.mData[i];
    }
    return result;
}
double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize && "Index out of bounds.");
    return mData[index];
}
const double& Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize && "Index out of bounds.");
    return mData[index];
}
double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize && "Index out of bounds.");
    return mData[index-1];
}
const double& Vector::operator()(int index) const {
    assert(index >= 1 && index <= mSize && "Index out of bounds.");
    return mData[index-1];
}
