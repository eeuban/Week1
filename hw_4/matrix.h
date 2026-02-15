# ifndef MATRIX
# define MATRIX

#include <iostream>
#include <stdexcept>
#include <assert.h>

class Matrix{
    public:

    // Constructors
    Matrix();                              // Default: 0×0 empty matrix
    Matrix(size_t rows, size_t cols);     // Zero-initialized matrix of given size
    Matrix(size_t rows, size_t cols, double value); // Matrix filled with specified value
    Matrix(std::initializer_list<std::initializer_list<double>> list); // Construct from 2D initializer list
    Matrix(const Matrix& other);           // Copy constructor (deep copy)

    bool isEmpty() const;
    bool isSquare() const;

    size_t rows() const;
    size_t cols() const;

    // Static Factory Methods
    static Matrix identity(size_t n);                        // n×n identity matrix
    static Matrix zeros(size_t rows, size_t cols);
    static Matrix ones(size_t rows, size_t cols);
    static Matrix diagonal(const std::vector<double>& diag); // Diagonal matrix from vector

    // Matrix Operations
    Matrix transpose() const;           // Returns M^T
    double trace() const;               // Sum of diagonal (square matrices only, throw std::logic_error)
    Matrix diagonal() const;            // Extract diagonal as column vector
    void fill(double value);            // Fill entire matrix with value
    double norm() const;                // Frobenius norm: sqrt(sum of all elements squared)

    // Comparision Operators
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    // Compound Assignment Operators
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    // Arithmic Operators
    Matrix operator+(const Matrix& other) const;  // Addition
    Matrix operator-(const Matrix& other) const;  // Subtraction
    Matrix operator*(const Matrix& other) const;  // Matrix multiplication
    Matrix operator*(double scalar) const;        // Scalar multiplication
    friend Matrix operator*(double scalar, const Matrix& m); // Scalar * matrix
    Matrix operator/(double scalar) const;        // Scalar division
    Matrix operator-() const;                     // Unary negation

    // Element Access
    double& operator()(size_t row, size_t col);              // Non-const access
    const double& operator()(size_t row, size_t col) const;  // Const access
    double& at(size_t row, size_t col);                      // With bounds checking (throw std::out_of_range)
    const double& at(size_t row, size_t col) const;

    // Assignment Operator
    Matrix& operator=(const Matrix& other); // Copy assignment

    private:

    std::vector<double> data;   // Where elements are stored row-major order
};


# endif