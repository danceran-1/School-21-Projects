#include "s21_matrix.h"

int s21_NUll(matrix_t *matrix) {
  bool x = false;
  if ((matrix != NULL && matrix->matrix != NULL && matrix->rows >= 1 &&
       matrix->columns >= 1)) {
    x = true;
  }
  return x;
}
int s21_eq_size(matrix_t *X, matrix_t *Y) {
  bool x = false;
  if (X->columns == Y->columns && X->rows == Y->rows) {
    x = true;
  }
  return x;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int out = 0;
  if (rows < 1 || columns < 1) {
    out = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < result->rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }

  return out;
}
void s21_remove_matrix(matrix_t *A) {
  if (s21_NUll(A) == true) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int out = FAILURE;

  if ((A->rows >= 1 || A->columns >= 1) || (B->rows >= 1 || B->columns >= 1)) {
    if (s21_NUll(A) == true || s21_NUll(B) == true) {
      if (s21_eq_size(A, B) == true) {
        out = SUCCESS;
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
              out = FAILURE;
            }
          }
        }
      }
    }
  }

  return out;
}

#define S21_MATRIX_OPERATION(A, B, result, op)                         \
  do {                                                                 \
    if ((s21_NUll(A) == true) || (s21_NUll(B) == true)) {              \
      if (s21_eq_size(A, B) == true) {                                 \
        s21_create_matrix(A->rows, A->columns, result);                \
        for (int i = 0; i < A->rows; i++) {                            \
          for (int j = 0; j < A->columns; j++) {                       \
            result->matrix[i][j] = A->matrix[i][j] op B->matrix[i][j]; \
          }                                                            \
        }                                                              \
      } else {                                                         \
        return 2;                                                      \
      }                                                                \
    } else {                                                           \
      return 1;                                                        \
    }                                                                  \
  } while (0)

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  S21_MATRIX_OPERATION(A, B, result, +);
  return 0;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  S21_MATRIX_OPERATION(A, B, result, -);
  return 0;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int out = 0;
  if (s21_NUll(A) == true) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }

  } else {
    out = 1;
  }
  return out;
}
int s21_transpose(matrix_t *A, matrix_t *result) {
  int out = 0;
  if (s21_NUll(A) == true) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    out = 1;
  }
  return out;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int out = 0;

  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    out = 1;
  } else if (A->columns != B->rows) {
    out = 1;
  } else {
    if (s21_create_matrix(A->rows, B->columns, result) != 0) {
      out = 1;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }

  return out;
}

void s21_calc_minor(matrix_t *A, matrix_t *minor, int row, int col) {
  if (A == NULL || minor == NULL || A->matrix == NULL ||
      minor->matrix == NULL) {
    return;
  }

  int minor_row = 0, minor_col = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;

    minor_col = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;

      if (minor_row < minor->rows && minor_col < minor->columns) {
        minor->matrix[minor_row][minor_col] = A->matrix[i][j];
      }
      minor_col++;
    }
    minor_row++;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int out = 0;
  *result = 0.0;

  if (A->rows != A->columns) {
    out = 2;
  } else if (A->matrix == NULL) {
    out = 1;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      matrix_t minor;
      int create_status =
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

      if (create_status != 0) {
        s21_remove_matrix(&minor);
        out = 1;
      } else {
        for (int j = 0; j < A->columns; j++) {
          s21_calc_minor(A, &minor, 0, j);

          double det_minor = 0.0;
          s21_determinant(&minor, &det_minor);

          *result += pow(-1, j) * A->matrix[0][j] * det_minor;
        }

        s21_remove_matrix(&minor);
      }
    }
  }

  return out;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int out = 0;
  if (A->matrix == NULL || A->rows < 2 || A->columns < 2) {
    out = 1;
    if (A->rows == 1 && A->columns == 1 && A->matrix[0][0] != NAN) {
      s21_create_matrix(A->rows, A->columns, result);
      result->matrix[0][0] = A->matrix[0][0];
      out = 0;
    }
  } else if (A->rows != A->columns) {
    out = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    matrix_t minor;
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_calc_minor(A, &minor, i, j);

        double det_minor;
        s21_determinant(&minor, &det_minor);

        result->matrix[i][j] = pow(-1, i + j) * det_minor;
      }
    }

    s21_remove_matrix(&minor);
  }

  return out;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int matrix_status = 0;
  if (s21_NUll(A)) {
    double det = 0.0;
    if (A->rows == A->columns) {
      s21_determinant(A, &det);
      if (det != 0) {
        matrix_t tmp_calc = {0};
        matrix_status = s21_calc_complements(A, &tmp_calc);
        if (matrix_status == 0) {
          matrix_t tmp_trans = {0};
          matrix_status = s21_transpose(&tmp_calc, &tmp_trans);
          if (matrix_status == 0) {
            s21_mult_number(&tmp_trans, 1 / det, result);
          }
          s21_remove_matrix(&tmp_trans);
        }
        s21_remove_matrix(&tmp_calc);
      } else {
        matrix_status = 1;
      }
    } else {
      matrix_status = 2;
    }
  } else {
    matrix_status = 1;
  }
  return matrix_status;
}
