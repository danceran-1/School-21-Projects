#include "s21_matrix_oop.h"

#include <iostream>
#include <stdexcept>
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
    return;
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}
S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  if (rows_ < 1 || cols_ < 1) {
    return;
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  this->matrix_ = other.matrix_;
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different dimensions.");
  } else if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Not allowed dimensions");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return result;
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different dimensions.");
  } else if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Not allowed dimensions");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return result;
}
S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] * number;
    }
  }
  return result;
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrices have incompatible dimensions for multiplication.");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  bool a = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    a = false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        a = false;
      }
    }
  }
  return a;
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;  // Проверка на самоприсвоение
  }

  // Освобождение старой памяти
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  // Копирование значений
  rows_ = other.rows_;
  cols_ = other.cols_;

  // Выделение новой памяти
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different dimensions.");
  } else if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Not allowed dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return *this;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices have different dimensions.");
  } else if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Not allowed dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double number) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= number;
    }
  }
  return *this;
}
S21Matrix &S21Matrix::operator*=(S21Matrix &other) {
  // Создаем результирующую матрицу правильного размера
  S21Matrix result(rows_, other.cols_);

  // Выполняем умножение
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {  // cols_ первой матрицы = rows_ второй
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  // Очищаем текущую матрицу
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  // Присваиваем новые размеры и данные
  rows_ = result.rows_;
  cols_ = result.cols_;

  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = result.matrix_[i][j];
    }
  }

  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range.");
  }
  return matrix_[i][j];
}

bool S21Matrix::EqMatrix(const S21Matrix &other) { return (*this == other); }

void S21Matrix::SumMatrix(const S21Matrix &other) { *this = *this + other; }

void S21Matrix::SubMatrix(const S21Matrix &other) { *this = *this - other; }

void S21Matrix::MulNumber(const double num) { *this = *this * num; }

void S21Matrix::MulMatrix(const S21Matrix &other) { *this = *this * other; }

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}
S21Matrix S21Matrix::GetMinor(int row, int col) {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Minor can only be calculated for square matrices.");
  }

  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Row or column index is out of range.");
  }

  S21Matrix minor(rows_ - 1, cols_ - 1);

  int minor_row = 0, minor_col = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;

    minor_col = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == col) continue;

      minor.matrix_[minor_row][minor_col] = matrix_[i][j];
      minor_col++;
    }
    minor_row++;
  }

  return minor;
}
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square.");
  }

  double determinant = 0.0;

  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(0, j);
      double minorDet = minor.Determinant();
      determinant += pow(-1, j) * matrix_[0][j] * minorDet;
    }
  }

  return (determinant);
}
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square.");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = GetMinor(i, j);
      double detMinor = minor.Determinant();

      result.matrix_[i][j] = (pow(-1, i + j) * detMinor);
    }
  }

  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square.");
  }
  S21Matrix res;

  double det = Determinant();
  if (det == 0) throw std::invalid_argument("Matrix determinant is zero.");
  res = CalcComplements();
  res = res.Transpose();
  res.MulNumber(1 / det);

  return res;
}
int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  } else if (rows != rows_) {
    double **tmp = new double *[rows];
    for (int i = 0; i < rows; i++) {
      tmp[i] = new double[this->cols_];
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (i < this->rows_) {
          tmp[i][j] = matrix_[i][j];
        } else {
          tmp[i][j] = 0;
        }
      }
    }
    for (int i = 0; i < this->rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = tmp;
    rows_ = rows;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  } else if (cols_ != cols) {
    double **tmp = new double *[this->rows_];
    for (int i = 0; i < this->rows_; i++) {
      tmp[i] = new double[cols];
      for (int j = 0; j < cols; j++) {
        if (j < this->cols_) {
          tmp[i][j] = matrix_[i][j];
        } else {
          tmp[i][j] = 0;
        }
      }
    }
    for (int i = 0; i < this->rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = tmp;
    cols_ = cols;
  }
}
