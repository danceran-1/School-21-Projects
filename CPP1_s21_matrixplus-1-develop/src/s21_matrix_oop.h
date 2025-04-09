#include <math.h>

#include <iomanip>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix(int rows = 1, int cols = 1);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  S21Matrix &operator*=(S21Matrix &other);
  double &operator()(int i, int j);
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix GetMinor(int row, int col);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);

  void setValue(int row, int col, double value) {
    if (row >= rows_ || col >= cols_)
      throw std::out_of_range("Index out of range");
    matrix_[row][col] = value;
  }
  void print() const {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};