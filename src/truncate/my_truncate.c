#include "../my_decimal.h"

int my_truncate(my_decimal value, my_decimal *result) {
  // Инициализируем все биты результата нулями
  for (int i = 0; i < 4; ++i) {
    result->bits[i] = 0;
  }
  // Объявляем переменную для кода ошибки
  int return_status = 0;
  // Проверяем, имеет ли число десятичную часть
  if (my_get_scale(value)) {
    // Переменная для хранения промежуточного результата
    long double new_int = 0.0;
    // Преобразуем десятичное число в число с плавающей точкой
    // и проверяем на возникновение ошибок
    return_status = my_from_decimal_to_double(value, &new_int);
    // Если значение невозможно представить как число с плавающей точкой,
    // то устанавливаем код ошибки и прерываем выполнение функции
    if (return_status != 0 || isnan(new_int) || isinf(new_int)) {
      return_status = 1;
    } else {
      // Отбрасываем дробную часть числа
      new_int = trunc(new_int);
      // Если число отрицательное, устанавливаем соответствующий бит
      // и делаем число положительным
      if (new_int < 0.0) {
        my_set_bit(result, 127, 1);
        new_int *= -1;
      }
      // Преобразуем число в двоичное представление
      for (int i = 0; new_int >= 1 && i < 96; i++) {
        // Вычисляем остаток от деления числа на 2 и устанавливаем
        // соответствующий бит
        my_set_bit(result, i, (int)fmod(new_int, 2));
        // Делим число на 2 для следующего бита
        new_int /= 2;
      }
      // Устанавливаем масштаб числа равным нулю, так как мы отбрасываем
      // десятичную часть
      _set_scale(result, 0);
    }
  } else {
    // Если число не имеет десятичной части, то просто копируем его в result
    for (int i = 0; i < 4; ++i) {
      result->bits[i] = value.bits[i];
    }
  }
  // Возвращаем код ошибки
  return return_status;
}