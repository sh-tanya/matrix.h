#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;

  if (!s21_size_eq(A, B) || A->matrix == NULL || B->matrix == NULL) {
    status = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-06) status = FAILURE;
  }
  return status;
}