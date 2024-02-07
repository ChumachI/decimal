#include "../my_decimal.h"

// Функция my_round округляет десятичное значение до ближайшего целого и
// сохраняет результат в формате my_decimal.
int my_round(my_decimal value, my_decimal *result) {
  // Инициализация result нулями
  for (int i = 0; i < 4; ++i) {
    result->bits[i] = 0;
  }
  long double to_round = 0.0;
  // Конвертируем десятичное значение в long double
  int return_status = my_from_decimal_to_double(value, &to_round);
  // Проверяем, была ли ошибка при конвертации, или значение является NaN или
  // Inf
  if (return_status != 0 || isnan(to_round) || isinf(to_round)) {
    // В случае ошибки устанавливаем код ошибки и прерываем выполнение функции
    return_status = 1;
  } else {
    // Округляем значение до ближайшего целого
    to_round = round(to_round);
    // Если значение отрицательное, устанавливаем знаковый бит в result и
    // делаем число положительным для дальнейшей обработки
    if (to_round < 0.0) {
      my_set_bit(result, 127, 1);
      to_round *= -1;
    }
    // Разбиваем значение на биты и записываем их в result
    for (int i = 0; to_round >= 1 && i < 96; i++) {
      my_set_bit(result, i, (int)fmod(to_round, 2));
      to_round /= 2;
    }
    // Устанавливаем масштаб в 0, так как мы округлили число до целого
    _set_scale(result, 0);
  }
  // Возвращаем код ошибки. В случае успеха, возвращается 0
  return return_status;
}
