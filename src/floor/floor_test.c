#include "../test/test.h"

START_TEST(floor_0) {
  my_decimal val = {{2, 0, 0, 0}};
  my_decimal res;
  ck_assert_int_eq(0, my_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  my_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  my_decimal res = {{0}};
  my_floor(val, &res);
  float fres = 0;
  my_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  my_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  my_decimal res = {{0}};
  _set_scale(&val, 5);
  my_floor(val, &res);
  float fres = 0;
  my_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  my_decimal val = {{2, 0, 0, 0}};
  my_decimal res = {{0}};
  _set_scale(&val, 5);
  my_floor(val, &res);
  float fres = 0;
  my_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(floor_5) {
  my_decimal value_1 = {{7444923, 0, 0, 0}};
  _set_scale(&value_1, 5);
  my_decimal check = {{74, 0, 0, 0}};
  my_decimal result = {0};
  int return_value = my_floor(value_1, &result);
  ck_assert_int_eq(my_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_6) {
  my_decimal value_1 = {{7444923, 0, 0, 0}};
  _set_scale(&value_1, 5);
  _set_bit(&value_1, 127);
  my_decimal check = {{75, 0, 0, 0}};
  _set_bit(&check, 127);
  my_decimal result = {0};
  int return_value = my_floor(value_1, &result);
  ck_assert_int_eq(my_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_7) {
  my_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  my_decimal res_od = {0};
  my_floor(src1, &res_od);
  my_decimal result = {0};
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

Suite *suite_floor(void) {
  Suite *s = suite_create("suite_floor");
  TCase *tc = tcase_create("floor_tc");
  tcase_add_test(tc, floor_0);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);
  suite_add_tcase(s, tc);
  return s;
}