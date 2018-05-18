#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <utility>
#include <iostream>

template <typename T>
class Matrix {
private:
    T** matrix;
    const int kSize;
public:
    explicit Matrix(int size) : kSize(size) {
        matrix = new T*[size];
        for(int i = 0; i < size; ++i) {
            matrix[i] = new T[size];
        }
    }
    void DestructArray() {
        for(int i = 0; i < kSize; ++i) {
            delete[] this->matrix[i];
        }
        delete[] this->matrix;
    }
    ~Matrix() {
        DestructArray();
    }
    const T& value(int row, int column) const {
        return matrix[row][column];
    }
    const int& size() const {
        return kSize;
    }
    void set_value(T value, int row, int column) {
        matrix[row][column] = std::move(value);
    }
    void set_matrix(T** matrix) {
        DestructArray();
        this->matrix = matrix;
    }
    T** get_matrix() {
        return this->matrix;
    }
    void Fill(T value) {
        for(int i = 0; i < kSize; ++i) {
            for(int j = 0; j < kSize; ++j) {
                set_value(value, i, j);
            }
        }
    }
};

#endif //MATRIX_HPP