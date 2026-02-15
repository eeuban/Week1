#include "matrix.h"

Matrix();                              // Default: 0×0 empty matrix
Matrix(size_t rows, size_t cols);     // Zero-initialized matrix of given size
Matrix(size_t rows, size_t cols, double value); // Matrix filled with specified value
Matrix(std::initializer_list<std::initializer_list<double>> list); // Construct from 2D initializer list
Matrix(const Matrix& other);