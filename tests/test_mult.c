#include "../test_includes/s21_tests.h"

START_TEST(test_1_nm) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx3 = {0};
  matrix_t check = {0};
  int row = 10, col = 10;
  double num = s21_random(-1000.0, 1000.0);
  s21_create_matrix(row, col, &mtrx1);
  s21_create_matrix(row, col, &check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      mtrx1.matrix[i][j] = s21_random(-100000.0, 100000.0);
      check.matrix[i][j] = mtrx1.matrix[i][j] * num;
    }
  }
  ck_assert_int_eq(s21_mult_number(&mtrx1, num, &mtrx3), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &mtrx3), SUCCESS);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx3);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2_nm) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  double num = s21_random(-1000.0, 1000.0);
  ck_assert_int_eq(s21_mult_number(&mtrx1, num, &mtrx2), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_1_mm) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};
  matrix_t check = {0};
  int row1 = 4, col1 = 3, row2 = 3, col2 = 5;
  s21_create_matrix(row1, col1, &mtrx1);
  s21_create_matrix(row2, col2, &mtrx2);
  s21_create_matrix(row1, col2, &check);
  for (int i = 0; i < row1; i++) {
    for (int j = 0; j < col1; j++) {
      mtrx1.matrix[i][j] = s21_random(-10000.0, 10000.0);
    }
  }
  for (int i = 0; i < row2; i++) {
    for (int j = 0; j < col2; j++) {
      mtrx2.matrix[i][j] = s21_random(-10000.0, 10000.0);
    }
  }
  for (int i = 0; i < row1; i++) {
    for (int j = 0; j < col2; j++) {
      for (int k = 0; k < col1; k++)
        check.matrix[i][j] += mtrx1.matrix[i][k] * mtrx2.matrix[k][j];
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&mtrx1, &mtrx2, &mtrx3), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &mtrx3), SUCCESS);
  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
  s21_remove_matrix(&mtrx3);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_2_mm) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};

  int row1 = 4, col1 = 4, row2 = 5, col2 = 5;
  s21_create_matrix(row1, col1, &mtrx1);
  s21_create_matrix(row2, col2, &mtrx2);

  for (int i = 0; i < row1; i++) {
    for (int j = 0; j < col1; j++) {
      mtrx1.matrix[i][j] = s21_random(-10000.0, 10000.0);
    }
  }
  for (int i = 0; i < row2; i++) {
    for (int j = 0; j < col2; j++) {
      mtrx2.matrix[i][j] = s21_random(-10000.0, 10000.0);
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&mtrx1, &mtrx2, &mtrx3), CALC_ERROR);

  s21_remove_matrix(&mtrx1);
  s21_remove_matrix(&mtrx2);
  s21_remove_matrix(&mtrx3);
}
END_TEST

START_TEST(test_3_mm) {
  matrix_t mtrx1 = {0};
  matrix_t mtrx2 = {0};
  matrix_t mtrx3 = {0};
  ck_assert_int_eq(s21_mult_matrix(&mtrx1, &mtrx2, &mtrx3), INCORRECT_MATRIX);
}
END_TEST

Suite *suite_mult(void) {
  Suite *s = suite_create("\033[1;31mmultiplication\033[m");
  TCase *tc = tcase_create("mult_tc");

  tcase_add_loop_test(tc, test_1_nm, 0, 100);
  tcase_add_test(tc, test_2_nm);
  tcase_add_loop_test(tc, test_1_mm, 0, 100);
  tcase_add_test(tc, test_2_mm);
  tcase_add_test(tc, test_3_mm);

  suite_add_tcase(s, tc);

  return s;
}