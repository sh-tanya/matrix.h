#include "../test_includes/s21_tests.h"

START_TEST(test_1) {
  matrix_t mtrx = {0};
  int row = 3, col = 3;
  ck_assert_int_eq(s21_create_matrix(row, col, &mtrx), OK);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      mtrx.matrix[i][j] = 0;
      ck_assert_double_eq_tol(0, mtrx.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(mtrx.rows, row);
  ck_assert_int_eq(mtrx.columns, col);
  s21_remove_matrix(&mtrx);
}
END_TEST

START_TEST(test_2) {
  const int rows = 0;
  const int cols = 10;
  matrix_t mtrx = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &mtrx), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_3) {
  const int rows = 10;
  const int cols = 0;

  matrix_t mtrx = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &mtrx), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_create_matrix(void) {
  Suite *s = suite_create("\033[1;31mcreate_matrix\033[m");
  TCase *tc = tcase_create("create_tc");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);

  return s;
}