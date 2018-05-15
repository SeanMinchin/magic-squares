#ifndef MAGIC_SQUARES_HPP
#define MAGIC_SQUARES_HPP

#include "matrix.hpp"

class InputManager {
private:
    static bool IsValid(int size);
public:
    static int DefineSquareMatrixSize();
};

class MagicSquare {
private:
    Matrix<int> magic_square;
    const int kSize;
    int magic_square_count;
    void CheckSums();
    void Print();
public:
    explicit MagicSquare(int size);
    const int& size() const;
    void ApplySiameseMethod();
    void ApplyTorusMethod();
    void Reflect();
    void Rotate();
    void DisplayData();
};

#endif //MAGIC_SQUARES_HPP