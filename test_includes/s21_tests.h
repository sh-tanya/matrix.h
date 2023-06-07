#ifndef SRC_TESTS_INCLUDES_S21_TESTS_H_
#define SRC_TESTS_INCLUDES_S21_TESTS_H_

#include <check.h>
#include <locale.h>
#include <stdio.h>
#include <unistd.h>

#include "../s21_matrix.h"

Suite *suite_create_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_sum_sub(void);
Suite *suite_mult(void);
Suite *suite_transpose(void);
Suite *suite_complement(void);
Suite *suite_determinant(void);
Suite *suite_inverse(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_INCLUDES_S21_TESTS_H_