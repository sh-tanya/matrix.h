#include "../test_includes/s21_tests.h"

START_TEST(test_1) {
  matrix_t mtrx = {0}, result = {0}, check = {0};
  int row = rand() % 100 + 1;
  int col = rand() % 100 + 1;
  double rand_val = 0.0;
  s21_create_matrix(row, col, &mtrx);
  s21_create_matrix(col, row, &check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      rand_val = s21_random(-1000.0, 1000.0);
      mtrx.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  s21_transpose(&mtrx, &result);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), 1);
  ck_assert_int_eq(mtrx.rows, result.columns);
  ck_assert_int_eq(mtrx.columns, result.rows);
  s21_remove_matrix(&mtrx);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2) {
  matrix_t mtrx = {0}, result = {0};
  ck_assert_int_eq(s21_transpose(&mtrx, &result), INCORRECT_MATRIX);
}

START_TEST(test_3) {
  matrix_t mtrx = {0}, result = {0};
  int row = 0;
  int col = 0;
  s21_create_matrix(row, col, &mtrx);

  ck_assert_int_eq(s21_transpose(&mtrx, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&mtrx);
}
END_TEST

Suite *suite_transpose(void) {
  Suite *s = suite_create("\033[1;31mtranspose_matrix\033[m");
  TCase *tc = tcase_create("transpose_tc");

  tcase_add_loop_test(tc, test_1, 0, 100);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);

  return s;
}