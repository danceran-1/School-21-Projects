#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1
#define POSITIVE_INFINITY_ERR 1
#define NEGATIVE_INFINITY_ERR 2
#define NAN_RESULT_ERR 3
#define POSITIVE 0
#define NEGATIVE 1
#define EPSILON 1e-04
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX - 1)
#define TOO_SMALL 1E-28
#define TOO_BIG 79228162514264337593543950335.0
#define MAX_32INT 0b11111111111111111111111111111111

#define ARRAY_SIZE 3
#define MAX_INDEX (32 * ARRAY_SIZE - 1)
#define INIT_ZERO_S21_DECIMAL \
  {                           \
    { 0, 0, 0, 0 }            \
  }

typedef struct {
  int bits[ARRAY_SIZE + 1];
} s21_decimal;

#define LONG_ARRAY_SIZE (2 * ARRAY_SIZE)
#define MAX_LONG_INDEX (32 * LONG_ARRAY_SIZE - 1)
#define INIT_ZERO_s21_buffer \
  {                          \
    { 0, 0, 0, 0, 0, 0, 0 }  \
  }

typedef struct {
  int bits[LONG_ARRAY_SIZE + 1];
} s21_buffer;

void s21_extend(s21_decimal *source, s21_buffer *destination);
int s21_normalize_and_round(s21_buffer *source, s21_decimal *destination);
int s21_is_long_greater_than_max(s21_buffer *value);
int s21_is_long_less_than_min(s21_buffer *value);
int s21_check_for_overflow(s21_buffer *value);
int s21_is_long_less_than_min(s21_buffer *value);
int s21_is_long_greater_than_max(s21_buffer *value);

void s21_mul_long_by_ten(s21_buffer *value);
int s21_div_long_by_ten(s21_buffer *value);

int s21_get_bit(s21_decimal *value, int index);
int s21_set_bit(s21_decimal *value, int index);
int s21_reset_bit(s21_decimal *value, int index);
int s21_get_sign(s21_decimal *value);
int s21_set_sign(s21_decimal *value, int sing);
void s21_inverse_sign(s21_decimal *value);
int s21_get_scale(s21_decimal *value);
int s21_set_scale(s21_decimal *value, int scale);

int s21_is_invalid(s21_decimal *value);
int s21_is_valid(s21_decimal *value);
int s21_is_overflow(s21_decimal *result);
void s21_copy(s21_decimal *source, s21_decimal *distination);

int s21_get_long_bit(s21_buffer *value, int index);
int s21_set_long_bit(s21_buffer *value, int index);
int s21_reset_long_bit(s21_buffer *value, int index);
int s21_get_long_sign(s21_buffer *value);
int s21_set_long_sign(s21_buffer *value, int sing);
void s21_inverse_long_sign(s21_buffer *value);
int s21_get_long_scale(s21_buffer *value);
int s21_set_long_scale(s21_buffer *value, int scale);

void s21_copy_long(s21_buffer *source, s21_buffer *destination);
void s21_reset_long_only_bits(s21_buffer *value);
int s21_is_long_zero(s21_buffer *value);
int s21_is_not_long_zero(s21_buffer *value);
int s21_equalize_long_scale(s21_buffer *first, s21_buffer *second);
int s21_shift_long_bits_to_left(s21_buffer *value, int shift);
int s21_shift_long_bits_to_right(s21_buffer *value, int shift);
int s21_compare_only_long_bits(s21_buffer *first, s21_buffer *second);
int s21_get_top_long_bit_index(s21_buffer *value);

void s21_add_long_bits_ignore_scale(s21_buffer *first, s21_buffer *second,
                                    s21_buffer *result);
void s21_sub_long_bits_ignore_scale(s21_buffer *first, s21_buffer *second,
                                    s21_buffer *result);
int s21_integer_div_long_ignore_scale(s21_buffer *value, s21_buffer *divider,
                                      s21_buffer *result,
                                      s21_buffer *remainder);

void s21_reset(s21_decimal *value);
int s21_has_long_bits(s21_buffer *value);
int s21_is_not_max_value_ignore_scale(s21_buffer *value);
void s21_increase_long_by_one(s21_buffer *value);
int s21_parse_int(char *string, char off_symbol, int *result);

int s21_truncate_to_integer(s21_decimal *source, s21_decimal *destination);
void s21_increase_by_one(s21_decimal *value);

int s21_compare(s21_decimal *value_1, s21_decimal *value_2);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int srs, s21_decimal *dst);
int s21_from_float_to_decimal(float srs, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
