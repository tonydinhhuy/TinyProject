#ifndef LINEAR_SYSTEM_HPP
#define LINEAR_SYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem2 {
protected:
    int mRows, mCols;      // Kích thước hệ phương trình
    Matrix* mpA;     // Ma trận hệ số 
    Vector* mpb;     // Vector vế phải
    
    // Ngăn chặn sao chép
    LinearSystem2(const LinearSystem2& other) = delete;
    LinearSystem2& operator=(const LinearSystem2& other) = delete;
    
public:
    // Constructor
    LinearSystem2(const Matrix& A, const Vector& b);
    
    // Destructor
    ~LinearSystem2();
    
    // Phương thức giải hệ
    Vector SolvewithMoore_Penrose(Matrix& A,  Vector& b) const;
    Vector SolveWithTikhonov( Matrix& A, Vector& b);

};

#endif // LINEAR_SYSTEM_HPP