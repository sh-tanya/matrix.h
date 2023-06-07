#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = CALC_ERROR;

  if (A->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
    status = OK;
  }

  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = CALC_ERROR, mem_flag = 0;
  double determinant = 0.0;

  if (A->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else if (A->columns == A->rows) {
    mem_flag = 1;
    if (A->rows == 1) {
      result->matrix[0][0] = 1;
    } else {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor = {0};
          s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
          s21_get_matrix(i, j, A, &minor);
          s21_determinant(&minor, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&minor);
        }
    }
    status = OK;
  }
  if (status == CALC_ERROR && mem_flag == 0) s21_remove_matrix(result);
  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = CALC_ERROR;
  *result = 0.0;

  if (A->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (A->columns == A->rows) {
    *result = s21_get_determinant(A);
    status = OK;
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = CALC_ERROR, flag = 0;
  double det = 0.0;
  matrix_t comp = {0}, transposed = {0};

  if (A->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    status = CALC_ERROR;
  } else {
    flag = s21_determinant(A, &det);
    if (fabs(det) < 1e-6 || flag != OK) {
      status = CALC_ERROR;
    } else if (s21_calc_complements(A, &comp) != OK) {
      status = INCORRECT_MATRIX;
    } else if (s21_transpose(&comp, &transposed) != OK) {
      status = INCORRECT_MATRIX;
    } else {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->rows; j++)
          result->matrix[i][j] = transposed.matrix[i][j] / det;

      s21_remove_matrix(&transposed);
      s21_remove_matrix(&comp);
      status = OK;
    }
  }
  return status;
}