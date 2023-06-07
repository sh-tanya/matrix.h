#include "../test_includes/s21_tests.h"

START_TEST(test_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  double det = 0.0;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 8;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 10;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 5;
  s21_determinant(&A, &det);

  C.matrix[0][0] = -60 / det;
  C.matrix[0][1] = -28 / det;
  C.matrix[0][2] = 80 / det;
  C.matrix[1][0] = -75 / det;
  C.matrix[1][1] = 39 / det;
  C.matrix[1][2] = -48 / det;
  C.matrix[2][0] = 6 / det;
  C.matrix[2][1] = -86 / det;
  C.matrix[2][2] = -8 / det;

  s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_2) {
  matrix_t m = {0};
  matrix_t result = {0};

  if (s21_create_matrix(1, 1, &m) == OK) {
    m.matrix[0][0] = 5.0;
    ck_assert_int_eq(s21_inverse_matrix(&m, &result), OK);
    ck_assert_double_eq_tol(result.matrix[0][0], (1.0 / m.matrix[0][0]), 1e-6);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_3) {
  matrix_t m = {0};
  matrix_t result = {0};

  if (s21_create_matrix(1, 1, &m) == OK) {
    ck_assert_int_eq(s21_inverse_matrix(&m, &result), CALC_ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_4) {
  matrix_t m = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_inverse_matrix(&m, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_5) {
  const int size = 2;
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&m, &result), CALC_ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_6) {
  matrix_t m = {0};
  matrix_t result = {0};

  if (s21_create_matrix(1, 4, &m) == OK) {
    ck_assert_int_eq(s21_inverse_matrix(&m, &result), CALC_ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_7) {
  matrix_t m = {0};
  matrix_t expected = {0};
  matrix_t result = {0};

  if (s21_create_matrix(3, 3, &m) == OK &&
      s21_create_matrix(3, 3, &expected) == OK) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;

    ck_assert_int_eq(s21_inverse_matrix(&m, &result), OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);

    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
  }
}
END_TEST

Suite *suite_inverse(void) {
  Suite *s = suite_create("\033[1;31minverse\033[m");
  TCase *tc = tcase_create("inverse_tc");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);

  suite_add_tcase(s, tc);
  return s;
}