#include "s21_matrix.h"

double s21_random(double A, double B) {
  double div = B / (B - A);
  return A + (rand() / div);
}

int s21_size_eq(matrix_t *A, matrix_t *B) {
  return (A->columns == B->columns && A->rows == B->rows) ? 1 : 0;
}

int s21_size_mul(matrix_t *A, matrix_t *B) {
  return (A->columns == B->rows) ? 1 : 0;
}

void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result) {
  int i_res = 0, j_res = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      j_res = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != col) result->matrix[i_res][j_res++] = A->matrix[i][j];
      }
      i_res++;
    }
  }
}

double s21_get_determinant(matrix_t *A) {
  double det = 0.0, sign = 1.0;
  if (A->rows == 1) {
    det = A->matrix[0][0];
  } else if (A->rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    matrix_t temp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
    for (int i = 0; i < A->rows; i++) {
      s21_get_matrix(0, i, A, &temp);
      sign = (i % 2) ? -1.0 : 1.0;
      det += sign * A->matrix[0][i] * s21_get_determinant(&temp);
    }
    s21_remove_matrix(&temp);
  }
  return det;
}