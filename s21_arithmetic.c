#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = CALC_ERROR;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else if (s21_size_eq(A, B)) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    status = OK;
  }

  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = CALC_ERROR;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else if (s21_size_eq(A, B)) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    status = OK;
  }

  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = CALC_ERROR;

  if (A->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
    status = OK;
  }

  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = CALC_ERROR;

  if (A->matrix == NULL || B->matrix == NULL) {
    status = INCORRECT_MATRIX;
  } else if (s21_create_matrix(A->rows, B->columns, result) != OK) {
    status = INCORRECT_MATRIX;
  } else if (s21_size_mul(A, B)) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++)
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    status = OK;
  }

  return status;
}
