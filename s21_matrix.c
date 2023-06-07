#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = INCORRECT_MATRIX;

  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL)
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
          break;
        }
        status = OK;
      }
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int j = 0; j < A->rows; j++) free(A->matrix[j]);
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
  }
}
