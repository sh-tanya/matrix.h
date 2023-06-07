#include "../test_includes/s21_tests.h"

START_TEST(test_1_sum) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};
  matrix_t check = {0};
  int row = 3, col = 3;
  s21_create_matrix(row, col, &mtrx1);
  s21_create_matrix(row, col, &mtrx2);
  s21_create_matrix(row, col, &check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      mtrx1.matrix[i][j] = s21_random(-100000.0, 100000.0);
      mtrx2.matrix[i][j] = s21_random(-100000.0, 100000.0);
      check.matrix[i][j] = mtrx1.matrix[i][j] + mtrx2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&mtrx1, &mtrx2, &mtrx3), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &mtrx3), SUCCESS);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
  s21_remove_matrix(&mtrx3);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2_sum) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};
  ck_assert_int_eq(s21_sum_matrix(&mtrx1, &mtrx2, &mtrx3), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_3_sum) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};

  int row1 = 10, col1 = 11, row2 = 10, col2 = 10;
  s21_create_matrix(row1, col1, &mtrx1);
  s21_create_matrix(row2, col2, &mtrx2);

  ck_assert_int_eq(s21_sum_matrix(&mtrx1, &mtrx2, &mtrx3), CALC_ERROR);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
  s21_remove_matrix(&mtrx3);
}
END_TEST

START_TEST(test_1_sub) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};
  matrix_t check = {0};
  int row = 3, col = 3;
  s21_create_matrix(row, col, &mtrx1);
  s21_create_matrix(row, col, &mtrx2);
  s21_create_matrix(row, col, &check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      mtrx1.matrix[i][j] = s21_random(-100000.0, 100000.0);
      mtrx2.matrix[i][j] = s21_random(-100000.0, 100000.0);
      check.matrix[i][j] = mtrx1.matrix[i][j] - mtrx2.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&mtrx1, &mtrx2, &mtrx3), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &mtrx3), SUCCESS);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
  s21_remove_matrix(&mtrx3);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2_sub) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};
  ck_assert_int_eq(s21_sub_matrix(&mtrx1, &mtrx2, &mtrx3), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_3_sub) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};

  int row1 = 10, col1 = 11, row2 = 10, col2 = 10;
  s21_create_matrix(row1, col1, &mtrx1);
  s21_create_matrix(row2, col2, &mtrx2);

  ck_assert_int_eq(s21_sub_matrix(&mtrx1, &mtrx2, &mtrx3), CALC_ERROR);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
  s21_remove_matrix(&mtrx3);
}
END_TEST

Suite *suite_sum_sub(void) {
  Suite *s = suite_create("\033[1;31madding_subtracting\033[m");
  TCase *tc = tcase_create("add_sub_tc");

  tcase_add_loop_test(tc, test_1_sum, 0, 100);
  tcase_add_test(tc, test_2_sum);
  tcase_add_test(tc, test_3_sum);
  tcase_add_loop_test(tc, test_1_sub, 0, 100);
  tcase_add_test(tc, test_2_sub);
  tcase_add_test(tc, test_3_sub);

  suite_add_tcase(s, tc);

  return s;
}