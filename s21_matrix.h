#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <float.h>
#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum status { OK = 0, INCORRECT_MATRIX = 1, CALC_ERROR = 2 };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// s21_matrix.c
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
// s21_comparison.c
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// s21_arithmetic.c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// s21_transform.c
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
// s21_extra.c
double s21_random(double A, double B);
int s21_size_eq(matrix_t *A, matrix_t *B);
int s21_size_mul(matrix_t *A, matrix_t *B);
void s21_get_matrix(int row, int col, matrix_t *A, matrix_t *result);
double s21_get_determinant(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_