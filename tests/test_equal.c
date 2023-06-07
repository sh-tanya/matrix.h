#include "../test_includes/s21_tests.h"

START_TEST(test_1) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  int row = 3, col = 3;
  s21_create_matrix(row, col, &mtrx1);
  s21_create_matrix(row, col, &mtrx2);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      mtrx1.matrix[i][j] = 1.0;
      mtrx2.matrix[i][j] = 1.0;
      ck_assert_double_eq_tol(mtrx1.matrix[i][j], mtrx2.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&mtrx1, &mtrx2), 1);
  ck_assert_int_eq(mtrx1.rows, row);
  ck_assert_int_eq(mtrx2.columns, col);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
}
END_TEST

START_TEST(test_2) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  int row1 = 3, col1 = 3, row2 = 4, col2 = 3;
  ;
  s21_create_matrix(row1, col1, &mtrx1);
  s21_create_matrix(row2, col2, &mtrx2);
  ck_assert_int_eq(s21_eq_matrix(&mtrx1, &mtrx2), 0);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
}
END_TEST

START_TEST(test_3) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  int row = 10, col = 10;
  s21_create_matrix(row, col, &mtrx1);
  s21_create_matrix(row, col, &mtrx2);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      mtrx1.matrix[i][j] = s21_random(DBL_MIN, DBL_MAX);
      mtrx2.matrix[i][j] = s21_random(DBL_MIN, DBL_MAX);
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&mtrx1, &mtrx2), 0);
  ck_assert_int_eq(mtrx1.rows, row);
  ck_assert_int_eq(mtrx2.columns, col);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
}
END_TEST

START_TEST(zero_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
}

START_TEST(zero_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(0, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *suite_eq_matrix(void) {
  Suite *s = suite_create("\033[1;31mequal_matrix\033[m");
  TCase *tc = tcase_create("equal_tc");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_loop_test(tc, test_3, 0, 100);

  tcase_add_test(tc, zero_matrix);
  tcase_add_test(tc, zero_matrix_1);

  suite_add_tcase(s, tc);

  return s;
}