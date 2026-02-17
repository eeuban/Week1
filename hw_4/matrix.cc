#include "matrix.h"
#include <vector>
#include <initializer_list>
#include <math.h>

void Matrix::print(){

    std::cout << "[";
    for(int i = 0; i < this->rows(); i++){
        std::cout << "[";
        for(int z = 0; z < this->cols(); z++){
            std::cout << this->at(i, z);
            if(z != this->cols()-1) std::cout << ",";
        }
        std::cout << "]";
        if(i != this->rows()-1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

Matrix::Matrix(){
    data = new std::vector<double>;
    num_rows = num_cols = 0;
}

Matrix::Matrix(size_t rows, size_t cols){
    //if(rows < 1 || cols < 1) throw std::invalid_argument("Dimensions cant be less than 1.\n");
    data = new std::vector<double>(rows * cols);
    this->num_rows = rows;
    this->num_cols = cols;
}

Matrix::Matrix(size_t rows, size_t cols, double value){
    //if(rows < 1 || cols < 1) throw std::invalid_argument("Dimensions cant be less than 1.\n");
    data = new std::vector<double>(rows * cols, value);
    this->num_rows = rows;
    this->num_cols = cols;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) : Matrix(){ // Construct from 2D initializer list

    int expected_col = 0;
    bool notfirst = false; 
    for(const auto& row : list){    // const becaues initalizerlist are immutable.
        expected_col = num_cols;
        for(const auto& col : row){
            data->push_back(col);
        }
        num_cols = row.size();
        if(expected_col != num_cols && notfirst) throw std::invalid_argument("columns are not same size.\n");
        notfirst = true;
    }
    num_rows = list.size();
}

Matrix::Matrix(const Matrix& other){
    *this = other;
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other){
    if(this == &other) return *this;    // If Matices are each other.

    delete data;                        // Deallocate memory.
    data = new std::vector<double>;
    for(int i = 0; i < other.rows(); i++){
        for(int z = 0; z < other.cols(); z++){
            data->push_back(other.at(i,z));
        }
    }
    num_rows = other.rows();
    num_cols = other.cols();

    return *this;
}

size_t Matrix::rows() const{
 return num_rows;
}

size_t Matrix::cols() const{
 return num_cols;
}

double& Matrix::operator()(size_t row, size_t col){
    if(col * num_cols + row > data->size() || col * num_cols + row < 0)
        throw std::out_of_range("accessing index out of bounds.");
    return (*data)[row * num_cols + col];
}

const double& Matrix::operator()(size_t row, size_t col) const{
    return (*data)[row * cols() + col];
}

const double& Matrix::at(size_t row, size_t col) const{
    return data->at(row * cols() + col);
}

double& Matrix::at(size_t row, size_t col){
    if(row * num_cols + col > data->size() || row * num_cols + col < 0)
        throw std::out_of_range("accessing index out of bounds.");
    return data->at(row * num_cols + col);
}

bool Matrix::operator==(const Matrix& other) const{
    if (this->isEmpty() || other.isEmpty()) throw std::logic_error("Cannot compare empty matrices");
    if (this->num_rows != other.rows() || this->num_cols != other.cols())
        return false;
    
    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            if(this->at(i, z) != other.at(i,z)) return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const{
    if (this->isEmpty() || other.isEmpty()) throw std::logic_error("Cannot compare empty matrices");
    if (this->num_rows != other.rows() || this->num_cols != other.cols())
        return true;
    
    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            if(this->at(i, z) != other.at(i,z)) return true;
        }
    }
    return false;
}

bool Matrix::isEmpty() const{
    if(num_rows == 0 && num_cols == 0) return true; else return false;
}

bool Matrix::isSquare() const{
    if(num_rows == num_cols) return true; else return false;
}

Matrix Matrix::operator+(const Matrix& other) const{
    if (this->isEmpty() || other.isEmpty()) throw std::logic_error("Cannot add matrix to empty matrix");
    if (this->num_rows != other.num_rows || this->num_cols != other.num_cols)
        throw std::invalid_argument("Dimensions of Matrices must be equal.\n");

    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            result.data->push_back(this->at(i, z) + other.at(i, z));
        }
    }

    result.num_rows = other.rows();
    result.num_cols = other.cols();
    
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other){
    *this = *this + other;
    return *this;
}

Matrix Matrix::operator-(const Matrix& other) const{
    if (this->isEmpty() || other.isEmpty()) throw std::logic_error("Cannot add matrix to empty matrix");
    if (this->num_rows != other.num_rows || this->num_cols != other.num_cols)
        throw std::invalid_argument("Dimensions of Matrices must be equal.\n");

    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            result.data->push_back(this->at(i, z) - other.at(i, z));
        }
    }

    result.num_rows = other.rows();
    result.num_cols = other.cols();
    
    return result;
}

Matrix& Matrix::operator-=(const Matrix& other){
    *this = *this - other;
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const{
    if (this->isEmpty() || other.isEmpty()) throw std::logic_error("Cannot add matrix to empty matrix");
    if (this->num_cols != other.num_rows || other.num_cols != this->num_rows)
        throw std::invalid_argument("1st matrcies number of columns must be equal \
                                to 2nd matrices number of rows.\n");

    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int y = 0; y < other.num_cols; y++){
            double sum = 0.0;
            for(int z = 0; z < this->num_cols; z++){
                double product = this->at(i, z) * other.at(z, y);
                sum += product;
            }
            result.data->push_back(sum);
        }
    }

    result.num_rows = this->rows();
    result.num_cols = other.cols();
    
    return result;
}

Matrix& Matrix::operator*=(const Matrix& other){
    *this = *this * other;
    return *this;
}

Matrix Matrix::operator*(double scalar) const{
    if (this->isEmpty()) throw std::logic_error("Cannot add matrix to empty matrix");
    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            result.data->push_back(scalar * this->at(i, z));
        }
    }

    result.num_rows = this->rows();
    result.num_cols = this->cols();
    
    return result;
}

Matrix& Matrix::operator*=(double scalar){
    *this = *this * scalar;
    return *this;
}

Matrix operator*(double scalar, const Matrix& m){
    // overloaded * should catch error.
    return m * scalar;
}

Matrix Matrix::operator/(double scalar) const{
    if (this->isEmpty()) throw std::logic_error("Cannot add matrix to empty matrix");
    if(scalar == 0 ) throw std::overflow_error("Cannot divide by zero");
    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            result.data->push_back(this->at(i, z) / scalar);
        }
    }

    result.num_rows = this->rows();
    result.num_cols = this->cols();
    
    return result;
}

Matrix& Matrix::operator/=(double scalar){
    *this = *this / scalar;
    return *this;
}

Matrix Matrix::operator-() const{
    if (this->isEmpty()) throw std::logic_error("Cannot add matrix to empty matrix");
    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            result.data->push_back(-this->at(i, z));
        }
    }

    result.num_rows = this->rows();
    result.num_cols = this->cols();

    return result;
}

Matrix Matrix::identity(size_t n){
    Matrix result;

    result.num_rows = result.num_cols = n;

    for(int i = 0; i < n; i++){
        for(int z = 0; z < n; z++){
            if(i == z)
                result.data->push_back(1.0);
            else
                result.data->push_back(0.0);
        }
    }
    return result;
}
Matrix Matrix::zeros(size_t rows, size_t cols){
    Matrix result;

    for(int i = 0; i < rows; i++){
        for(int z = 0; z < cols; z++){
            result.data->push_back(0.0);
        }
    }

    result.num_rows = rows;
    result.num_cols = cols;

    return result;
}

Matrix Matrix::ones(size_t rows, size_t cols){
    Matrix result;

    for(int i = 0; i < rows; i++){
        for(int z = 0; z < cols; z++){
            result.data->push_back(1.0);
        }
    }

    result.num_rows = rows;
    result.num_cols = cols;

    return result;
}

Matrix Matrix::diagonal(const std::vector<double>& diag){
    if(diag.size() < 1) throw std::invalid_argument("Diagnal has to be greater than 1");

    Matrix result;

    result.num_rows = diag.size();
    result.num_cols = diag.size();

    for(int i = 0; i < result.num_rows; i++){
        for(int z = 0; z < result.num_cols; z++){
            if(i == z)
                result.data->push_back(diag[i]);
            else
                result.data->push_back(0.0);
        }
    }


    return result;
}

Matrix Matrix::transpose() const{

    Matrix result;

    for(int i = 0; i < this->num_cols; i++){
        for(int z = 0; z < this->num_rows; z++){
            result.data->push_back(this->at(z, i));
        }
    }

    result.num_rows = this->cols();
    result.num_cols = this->rows();

    return result;
}

void Matrix::fill(double value){

    for(int i = 0; i < this->num_cols; i++){
        for(int z = 0; z < this->num_rows; z++){
            (*this)(i, z) = value;
        }
    }
}
double Matrix::trace() const{
if(!this->isSquare()) throw std::logic_error("Has to be a square Matrix.");

    double result = 0;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            if(i == z) result += this->at(i, z);
        }
    }

    return result;
}
Matrix Matrix::diagonal() const{
    if(!this->isSquare()) throw std::logic_error("Has to be a square Matrix.");

    Matrix result;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            if(i == z) result.data->push_back(this->at(i, z));
        }
    }

    result.num_rows = this->rows();
    result.num_cols = 1;

    return result;
}

double Matrix::norm() const{

    double sum = 0.0;

    for(int i = 0; i < this->num_rows; i++){
        for(int z = 0; z < this->num_cols; z++){
            sum += pow(this->at(i, z), 2);
        }
    }

    return sqrt(sum);
}