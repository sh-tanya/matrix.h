#include "../test_includes/s21_tests.h"

START_TEST(test_1) {
  int size = 5;
  double res = 0.0;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = 1.0;

  ck_assert_int_eq(s21_determinant(&m, &res), OK);
  ck_assert_double_eq_tol(res, 0, 1e-6);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_2) {
  int size = 5;
  matrix_t m = {0};
  double res = 0.0;
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;

  ck_assert_int_eq(s21_determinant(&m, &res), OK);
  ck_assert_double_eq_tol(res, 0, 1e-6);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_3) {
  int size = 4;
  matrix_t m = {0};
  double res = 0.0;
  s21_create_matrix(size, size, &m);

  m.matrix[0][0] = 0;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 9;
  m.matrix[0][3] = 1;
  m.matrix[1][0] = 2;
  m.matrix[1][1] = 1;
  m.matrix[1][2] = 1;
  m.matrix[1][3] = 1;
  m.matrix[2][0] = 7;
  m.matrix[2][1] = 1;
  m.matrix[2][2] = 1;
  m.matrix[2][3] = 2;
  m.matrix[3][0] = 1;
  m.matrix[3][1] = 2;
  m.matrix[3][2] = 6;
  m.matrix[3][3] = 1;

  ck_assert_int_eq(s21_determinant(&m, &res), OK);
  ck_assert_double_eq_tol(res, -4, 1e-6);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_4) {
  int size = 3;
  matrix_t m = {0};
  double res = 0.0;
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 3;
  m.matrix[0][1] = 1;
  m.matrix[0][2] = 2;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;
  m.matrix[1][2] = 9;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 0;

  ck_assert_int_eq(s21_determinant(&m, &res), OK);
  ck_assert_double_eq_tol(res, -15, 1e-6);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_5) {
  int size = 2;
  matrix_t m = {0};
  double res = 0.0;
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 3;
  m.matrix[1][0] = 5;
  m.matrix[1][1] = 1;

  ck_assert_int_eq(s21_determinant(&m, &res), OK);
  ck_assert_double_eq_tol(res, -14, 1e-6);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_6) {
  int size = 2;
  matrix_t m = {0};
  double res = 0.0;
  s21_create_matrix(size, size + 1, &m);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size + 1; j++) m.matrix[i][j] = 1.0;

  ck_assert_int_eq(s21_determinant(&m, &res), CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_7) {
  matrix_t m = {0};
  double res = 0.0;

  ck_assert_int_eq(s21_determinant(&m, &res), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_8) {
  int size = 1;
  matrix_t m = {0};
  double res = 0.0;
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  ck_assert_int_eq(s21_determinant(&m, &res), OK);
  ck_assert_double_eq_tol(res, m.matrix[0][0], 1e-6);
  s21_remove_matrix(&m);
}
END_TEST

Suite *suite_determinant(void) {
  Suite *s = suite_create("\033[1;31mdeterminant\033[m");
  TCase *tc = tcase_create("det_tc");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);

  suite_add_tcase(s, tc);

  return s;
}