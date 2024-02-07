#include "../test/test.h"

START_TEST(test_itd_1) {
  my_decimal a = {0};
  int src = INT_MAX;
  my_from_int_to_decimal(src, &a);
  ck_assert_int_eq(a.bits[0], INT_MAX);
}
END_TEST

START_TEST(test_itd_2) {
  my_decimal a = {0};
  int src = INT_MIN;
  my_from_int_to_decimal(src, &a);
  int test = _find_bit(a, 127);
  ck_assert_int_eq(a.bits[0], INT_MAX);
  ck_assert_int_eq(test, 1);
}
END_TEST

START_TEST(test_itd_3) {
  my_decimal a = {0};
  int src = -123456;
  my_from_int_to_decimal(src, &a);
  int test = _find_bit(a, 127);
  ck_assert_int_eq(a.bits[0], 123456);
  ck_assert_int_eq(test, 1);
}
END_TEST

START_TEST(test_itd_4) {
  my_decimal a = {0};
  int src = 123456;
  my_from_int_to_decimal(src, &a);
  ck_assert_int_eq(a.bits[0], 123456);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

START_TEST(test_itd_5) {
  int src = 123456;
  int status = my_from_int_to_decimal(src, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

Suite *suite_itd(void) {
  Suite *s = suite_create("suite_itd");
  TCase *tc = tcase_create("itd_tc");
  tcase_add_test(tc, test_itd_1);
  tcase_add_test(tc, test_itd_2);
  tcase_add_test(tc, test_itd_3);
  tcase_add_test(tc, test_itd_4);
  tcase_add_test(tc, test_itd_5);

  suite_add_tcase(s, tc);
  return s;
}