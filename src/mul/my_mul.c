#include "../my_decimal.h"

int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  int status = 0;
  my_decimal mulBuffer = value_2;
  mulBuffer.bits[3] = 0;
  my_decimal zero = _init_decimal();
  *result = _init_decimal();
  int sign1 = _find_bit(value_1, 127);
  int sign2 = _find_bit(value_2, 127);
  int exp1 = (value_1.bits[3] >> 16) & 0xFF;
  int exp2 = (value_2.bits[3] >> 16) & 0xFF;
  if (my_is_equal(value_1, zero) || my_is_equal(value_2, zero)) {
    status = 0;
  } else {
    my_decimal resultBuffer;
    for (int i = 0; i < 96 && status == 0; i++) {
      int bit = _find_bit(value_1, i);
      if (bit == 1) {
        resultBuffer = *result;
        resultBuffer.bits[3] = 0;
        *result = _init_decimal();
        status = my_add(mulBuffer, resultBuffer, result);
      }
      _left_shift(&mulBuffer);
    }
    result->bits[3] |= (exp1 + exp2) << 16;
    if ((sign1 ^ sign2) == 1) {
      _set_bit(result, 127);
    }
    if (_find_bit(*result, 127) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}