
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef struct 
{
    uint32_t bits[4];
} my_decimal;

#define my_MAXDEC 7.9228162514264337593543950335e28


/*функция сложения*/
int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);

/*функция вычитания*/
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);

/*функция умножения*/
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);

/*функция деления*/
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);

/* округляет десятичное значение до ближайшего целого*/
int my_round(my_decimal value, my_decimal *result);

/*отбрасывает дробную часть без округления*/
int my_truncate(my_decimal value, my_decimal *result);

/*округление в сторону отрицательной бесконечности*/
int my_floor(my_decimal value, my_decimal *result);

/*Возвращает результат умножения указанного Decimal на -1.*/
int my_negate(my_decimal value, my_decimal *result);

/*Равенство децималов*/
int my_is_equal(my_decimal a, my_decimal b);

/*Неравенство децималов*/
int my_is_not_equal(my_decimal a, my_decimal b);

/*Больше*/
int my_is_greater(my_decimal a, my_decimal b);

/*Больше или равно*/
int my_is_greater_or_equal(my_decimal a, my_decimal b);

/*Меньше*/
int my_is_less(my_decimal a, my_decimal b);

/*Меньше или равно*/
int my_is_less_or_equal(my_decimal a, my_decimal b);

/*преобразователь из float*/
int my_from_float_to_decimal(float src, my_decimal *dst);

/*Из int*/
int my_from_int_to_decimal(int src, my_decimal *dst);

/*В int*/
int my_from_decimal_to_int(my_decimal src, int *dst);

/*В float*/
int my_from_decimal_to_float(my_decimal src, float *dst);

/*возвращает децимал инициализированный нулем*/
my_decimal _init_decimal();

/*возвращает состояние бита на указанной позиции 1 или 0*/
int _find_bit(my_decimal decimal, int elem);

/*устанавливает 1 в указанную позицию*/
void _set_bit(my_decimal *decimal, int elem);

/*проверка децимала на корректность*/
bool _is_decimal_correct(my_decimal decimal);

/*проверяет равен ли децимал нулю*/
bool _is_zero(my_decimal value);

/*выравнивает экспоненты двух децималов*/
void _set_common_exponent(my_decimal *value_1, my_decimal *value_2);

/*Уменьшает экспоненту*/
void _decrease_exponent(my_decimal *value_1, my_decimal *value_2, int diff,
                        int *v1_exponent, int *v2_exponent);

/*умножает децимал на целое число*/
int _muliply_uint(my_decimal *value, uint32_t num);

/*делит мантиссу decimal на любой int, при делении на 0 возвращает 3*/
int _divide_uint(my_decimal *value, uint32_t num, int round_type);

/*функция округления */
void _parse_rounding(my_decimal *result, uint64_t buffer, uint32_t num,
                     int round_type);

/*подсчет количества цифр в числе*/
int count_digits(int n);

/*сдвиг децимала влево*/
int _left_shift(my_decimal *value);

/*побитовое сложение*/
int _binary_addition(int bit1, int bit2, int *remainder);

/*побитовое "не"*/
void _binary_not(my_decimal * value);

/*устанавливает экспаненту*/
void _set_scale(my_decimal * value, int scale);

/*устанавливает знак*/
void _set_sign(my_decimal * value, int sign);

void my_set_bit(my_decimal *dst, int index, int bit);

int my_from_decimal_to_double(my_decimal src, long double *dst);

int my_get_scale(my_decimal dst);