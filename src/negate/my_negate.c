#include "../my_decimal.h"

int my_negate(my_decimal value, my_decimal *result) {
  int status = 0;
  if (_is_decimal_correct(value) && result) {
    value.bits[3] ^= (1u << 31);
    *result = value;
  } else {
    status = 1;
  }

  return status;
}
