#ifndef VECTOR_HPP
#define VECTOR_HPP


#include <iostream>
using namespace std;
class Vector {
    private:
        int mSize;
        double* mData;
    public:
    //constructors and destructor
    Vector();
    Vector(int size);
    Vector(const Vector& v);
    ~Vector();
    int GetSize() const;
    //assignment operator
    Vector& operator=(const Vector& v);
    //unary operator
    Vector operator-() const;
    Vector operator+() const;
    //binary operator
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(double scalar) const;
    friend Vector operator*(double scalar, const Vector& v);
    double operator*(const Vector& v) const; //Dot product
    //Square bracket operator
    double& operator[](int index);
    const double& operator[](int index) const;
    //Round bracket operator
    double& operator()(int index);
    const double& operator()(int index) const;

};
#endif