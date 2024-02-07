#include "../my_decimal.h"

int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  if (_is_zero(value_2)) {
    *result = _init_decimal();
    return 3;
  } else if (_is_zero(value_1)) {
    *result = _init_decimal();
    return 0;
  }
  int status = 0;
  my_decimal R = _init_decimal();
  my_decimal ten;
  my_from_float_to_decimal(10, &ten);
  *result = _init_decimal();
  int sign1 = _find_bit(value_1, 127);
  int sign2 = _find_bit(value_2, 127);
  _set_common_exponent(&value_1, &value_2);
  if (_is_zero(value_1) || _is_zero(value_2)) {
    status = (sign1 ^ sign2) ? 2 : 1;
  } else {
    int exp = value_1.bits[3] = value_2.bits[3] = 0;
    for (int i = 95; i >= 0; i--) {
      int bit = _find_bit(value_1, i);
      _left_shift(&R);
      if (bit == 1) {
        _set_bit(&R, 0);
      }
      if (my_is_greater_or_equal(R, value_2) == 1) {
        my_sub(R, value_2, &R);
        _set_bit(result, i);
      }
    }
    while (!_is_zero(R) && exp < 28) {
      my_decimal one;
      my_from_float_to_decimal(1, &one);
      my_mul(R, ten, &R);
      my_mul(*result, ten, result);
      exp++;
      while (my_is_greater_or_equal(R, value_2) == 1) {
        my_sub(R, value_2, &R);
        my_add(*result, one, result);
      }
    }
    result->bits[3] |= exp << 16;
    if ((sign1 ^ sign2) == 1) {
      _set_bit(result, 127);
    }
  }
  return status;
}
