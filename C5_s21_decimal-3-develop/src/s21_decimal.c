#include "s21_decimal.h"

int s21_get_bit(s21_decimal *value, int index) {
  if (index < 0 || index > MAX_INDEX) {
    return 0;
  }

  int integer = value->bits[index / 32];

  return (integer & 1u << (index % 32)) > 0 ? 1 : 0;
}

int s21_set_bit(s21_decimal *value, int index) {
  if (index < 0 || index > MAX_INDEX) {
    return ERROR;
  }

  value->bits[index / 32] |= 1u << (index % 32);

  return OK;
}

int s21_reset_bit(s21_decimal *value, int index) {
  if (index < 0 || index > MAX_INDEX) {
    return ERROR;
  }

  value->bits[index / 32] &= ~(1u << (index % 32));

  return OK;
}

int s21_get_sign(s21_decimal *value) {
  int integer = value->bits[ARRAY_SIZE];

  return (integer & 1u << 31) > 0 ? NEGATIVE : POSITIVE;
}

int s21_set_sign(s21_decimal *value, int sing) {
  if (sing != POSITIVE && sing != NEGATIVE) {
    return ERROR;
  }

  if (sing == NEGATIVE) {
    value->bits[ARRAY_SIZE] |= 1u << 31;
  } else {
    value->bits[ARRAY_SIZE] &= ~(1u << 31);
  }

  return OK;
}

void s21_inverse_sign(s21_decimal *value) {
  value->bits[ARRAY_SIZE] ^= 1u << 31;
}

int s21_get_scale(s21_decimal *value) {
  int integer = value->bits[ARRAY_SIZE];

  return (integer >> 16) & (0b11111111);
}

int s21_set_scale(s21_decimal *value, int scale) {
  if (scale < 0 || scale > 28) {
    return ERROR;
  }

  int sign = s21_get_sign(value);
  value->bits[ARRAY_SIZE] = scale << 16;
  s21_set_sign(value, sign);

  return OK;
}

int s21_get_long_bit(s21_buffer *value, int index) {
  if (index < 0 || index > MAX_LONG_INDEX) {
    return 0;
  }

  int integer = value->bits[index / 32];

  return (integer & 1u << (index % 32)) > 0 ? 1 : 0;
}

int s21_set_long_bit(s21_buffer *value, int index) {
  if (index < 0 || index > MAX_LONG_INDEX) {
    return ERROR;
  }

  value->bits[index / 32] |= 1u << (index % 32);

  return OK;
}

int s21_reset_long_bit(s21_buffer *value, int index) {
  if (index < 0 || index > MAX_LONG_INDEX) {
    return ERROR;
  }

  value->bits[index / 32] &= ~(1u << (index % 32));

  return OK;
}

int s21_get_long_sign(s21_buffer *value) {
  int integer = value->bits[LONG_ARRAY_SIZE];

  return (integer & 1u << 31) > 0 ? NEGATIVE : POSITIVE;
}

int s21_set_long_sign(s21_buffer *value, int sing) {
  if (sing != POSITIVE && sing != NEGATIVE) {
    return ERROR;
  }

  if (sing == NEGATIVE) {
    value->bits[LONG_ARRAY_SIZE] |= 1u << 31;
  } else {
    value->bits[LONG_ARRAY_SIZE] &= ~(1u << 31);
  }

  return OK;
}

void s21_inverse_long_sign(s21_buffer *value) {
  value->bits[LONG_ARRAY_SIZE] ^= 1u << 31;
}

int s21_get_long_scale(s21_buffer *value) {
  int integer = value->bits[LONG_ARRAY_SIZE];

  return (integer >> 16) & (0b11111111);
}

int s21_set_long_scale(s21_buffer *value, int scale) {
  if (scale < 0 || scale > 56) {
    return ERROR;
  }

  int sign = s21_get_long_sign(value);
  value->bits[LONG_ARRAY_SIZE] = scale << 16;
  s21_set_long_sign(value, sign);

  return OK;
}

int s21_is_invalid(s21_decimal *value) {
  if (value == NULL) {
    return TRUE;
  }

  int scale = s21_get_scale(value);

  return scale < 0 || scale > 28 ? TRUE : FALSE;
}

int s21_is_valid(s21_decimal *value) {
  return s21_is_invalid(value) == TRUE ? FALSE : TRUE;
}

void s21_copy(s21_decimal *source, s21_decimal *distination) {
  for (int i = 0; i <= ARRAY_SIZE; i++) {
    distination->bits[i] = source->bits[i];
  }
}
void s21_copy_long(s21_buffer *source, s21_buffer *destination) {
  for (int i = 0; i <= LONG_ARRAY_SIZE; i++) {
    destination->bits[i] = source->bits[i];
  }
}

void s21_reset_long_only_bits(s21_buffer *value) {
  for (int i = 0; i < LONG_ARRAY_SIZE; i++) {
    value->bits[i] = 0;
  }
}

int s21_is_long_zero(s21_buffer *value) {
  int result = TRUE;

  for (int i = 0; i < LONG_ARRAY_SIZE && result == TRUE; i++) {
    if (value->bits[i] != 0) {
      result = FALSE;
    }
  }

  return result;
}

int s21_is_not_long_zero(s21_buffer *value) {
  return s21_is_long_zero(value) == TRUE ? FALSE : TRUE;
}

int s21_equalize_long_scale(s21_buffer *first, s21_buffer *second) {
  int first_scale = s21_get_long_scale(first);
  int second_scale = s21_get_long_scale(second);
  int difference = first_scale - second_scale;
  s21_buffer *pointer = NULL;
  int delta = 0;

  if (difference > 0) {
    delta = difference;
    s21_set_long_scale(second, second_scale + delta);
    pointer = second;
  } else if (difference < 0) {
    delta = -difference;
    s21_set_long_scale(first, first_scale + delta);
    pointer = first;
  }

  for (int i = 0; i < delta; i++) {
    s21_mul_long_by_ten(pointer);
  }

  return difference;
}

int s21_shift_long_bits_to_left(s21_buffer *value, int shift) {
  int top_bit_index = s21_get_top_long_bit_index(value);

  if (shift == 0 || top_bit_index == -1) {
    return OK;
  } else if (shift < 0 || shift > MAX_LONG_INDEX - top_bit_index) {
    return ERROR;
  }

  s21_buffer value_copy = INIT_ZERO_s21_buffer;
  s21_copy_long(value, &value_copy);
  s21_reset_long_only_bits(value);

  for (int i = 0; i <= top_bit_index; i++) {
    if (s21_get_long_bit(&value_copy, i) == 1) {
      s21_set_long_bit(value, i + shift);
    }
  }

  return OK;
}

int s21_shift_long_bits_to_right(s21_buffer *value, int shift) {
  int top_bit_index = s21_get_top_long_bit_index(value);

  if (shift == 0 || top_bit_index == -1) {
    return OK;
  } else if (shift < 0 || shift > MAX_LONG_INDEX - top_bit_index) {
    return ERROR;
  }

  s21_buffer value_copy = INIT_ZERO_s21_buffer;
  s21_copy_long(value, &value_copy);
  s21_reset_long_only_bits(value);

  for (int i = shift; i <= top_bit_index; i++) {
    if (s21_get_long_bit(&value_copy, i) == 1) {
      s21_set_long_bit(value, i - shift);
    }
  }

  return OK;
}

int s21_compare_only_long_bits(s21_buffer *first, s21_buffer *second) {
  int difference = 0;
  int first_top_bit_index = s21_get_top_long_bit_index(first);
  int second_top_bit_index = s21_get_top_long_bit_index(second);

  if (first_top_bit_index > second_top_bit_index) {
    difference = 1;
  } else if (first_top_bit_index < second_top_bit_index) {
    difference = -1;
  } else {
    for (int i = first_top_bit_index; i >= 0 && difference == 0; i--) {
      difference = s21_get_long_bit(first, i) - s21_get_long_bit(second, i);
    }
  }

  return difference;
}

int s21_get_top_long_bit_index(s21_buffer *value) {
  int result = -1;
  int index = MAX_LONG_INDEX;

  for (int i = LONG_ARRAY_SIZE - 1; i >= 0 && value->bits[i] == 0; i--) {
    index -= 32;
  }

  for (; index >= 0 && result == -1; index--) {
    if (s21_get_long_bit(value, index) == 1) {
      result = index;
    }
  }

  return result;
}
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_invalid(&value_1) || s21_is_invalid(&value_2) || result == NULL) {
    return NAN_RESULT_ERR;
  }

  int sign_1 = s21_get_sign(&value_1);
  int sign_2 = s21_get_sign(&value_2);

  if ((sign_1 == POSITIVE && sign_2 == NEGATIVE) ||
      (sign_1 == NEGATIVE && sign_2 == POSITIVE)) {
    s21_decimal *minuend = (sign_1 == POSITIVE) ? &value_1 : &value_2;
    s21_decimal *subtrahend = (sign_1 == POSITIVE) ? &value_2 : &value_1;
    s21_set_sign(subtrahend, POSITIVE);
    return s21_sub(*minuend, *subtrahend, result);
  }

  s21_buffer first = INIT_ZERO_s21_buffer;
  s21_extend(&value_1, &first);
  s21_buffer second = INIT_ZERO_s21_buffer;
  s21_extend(&value_2, &second);

  s21_equalize_long_scale(&first, &second);

  s21_buffer sum = INIT_ZERO_s21_buffer;
  s21_add_long_bits_ignore_scale(&first, &second, &sum);
  s21_set_long_scale(&sum, s21_get_long_scale(&first));
  s21_set_long_sign(&sum, sign_1);

  return s21_normalize_and_round(&sum, result);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_invalid(&value_1) || s21_is_invalid(&value_2) || result == NULL) {
    return NAN_RESULT_ERR;
  }

  if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) {
    s21_inverse_sign(&value_2);
    return s21_add(value_1, value_2, result);
  }

  s21_buffer first = INIT_ZERO_s21_buffer;
  s21_buffer second = INIT_ZERO_s21_buffer;
  s21_extend(&value_1, &first);
  s21_extend(&value_2, &second);

  s21_equalize_long_scale(&first, &second);

  s21_buffer difference = INIT_ZERO_s21_buffer;
  s21_set_long_scale(&difference, s21_get_long_scale(&first));
  s21_set_long_sign(&difference, s21_get_long_sign(&first));

  if (s21_compare_only_long_bits(&first, &second) >= 0) {
    s21_sub_long_bits_ignore_scale(&first, &second, &difference);
  } else {
    s21_sub_long_bits_ignore_scale(&second, &first, &difference);
    s21_inverse_long_sign(&difference);
  }

  return s21_normalize_and_round(&difference, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_invalid(&value_1) || s21_is_invalid(&value_2) || result == NULL) {
    return NAN_RESULT_ERR;
  }

  s21_buffer first = INIT_ZERO_s21_buffer;
  s21_extend(&value_1, &first);

  s21_buffer second = INIT_ZERO_s21_buffer;
  s21_extend(&value_2, &second);

  s21_buffer composition = INIT_ZERO_s21_buffer;
  s21_buffer temp_sum = INIT_ZERO_s21_buffer;

  int top_bit_index = s21_get_top_long_bit_index(&second);

  for (int i = 0, shift = 0; i <= top_bit_index; i++) {
    if (s21_get_long_bit(&second, i) == 1) {
      s21_shift_long_bits_to_left(&first, shift);

      s21_add_long_bits_ignore_scale(&composition, &first, &temp_sum);

      s21_copy_long(&temp_sum, &composition);
      shift = 0;
    }

    shift++;
  }

  s21_set_long_scale(&composition,
                     s21_get_long_scale(&first) + s21_get_long_scale(&second));
  s21_set_long_sign(&composition,
                    s21_get_long_sign(&first) ^ s21_get_long_sign(&second));

  return s21_normalize_and_round(&composition, result);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_invalid(&value_1) || s21_is_invalid(&value_2) || result == NULL) {
    return NAN_RESULT_ERR;
  }

  s21_buffer value = INIT_ZERO_s21_buffer;
  s21_extend(&value_1, &value);

  s21_buffer divider = INIT_ZERO_s21_buffer;
  s21_extend(&value_2, &divider);

  s21_buffer quotient = INIT_ZERO_s21_buffer;

  int quotient_scale =
      s21_get_long_scale(&value) - s21_get_long_scale(&divider);

  for (; quotient_scale < 0; quotient_scale++) {
    s21_mul_long_by_ten(&value);
  }

  s21_buffer remainder = INIT_ZERO_s21_buffer;

  int status = s21_integer_div_long_ignore_scale(&value, &divider, &quotient,
                                                 &remainder);

  if (status == OK) {
    while (s21_is_not_long_zero(&remainder) && quotient_scale < 28) {
      s21_mul_long_by_ten(&remainder);
      s21_buffer next_quotient = INIT_ZERO_s21_buffer;
      s21_buffer buffer = INIT_ZERO_s21_buffer;
      s21_copy_long(&remainder, &buffer);

      s21_integer_div_long_ignore_scale(&buffer, &divider, &next_quotient,
                                        &remainder);

      s21_buffer quotient_sum = INIT_ZERO_s21_buffer;
      s21_mul_long_by_ten(&quotient);
      s21_add_long_bits_ignore_scale(&quotient, &next_quotient, &quotient_sum);
      s21_copy_long(&quotient_sum, &quotient);
      quotient_scale++;
    }

    s21_set_long_scale(&quotient, quotient_scale);
    s21_set_long_sign(&quotient,
                      s21_get_long_sign(&value) ^ s21_get_long_sign(&divider));
    status = s21_normalize_and_round(&quotient, result);
  }

  return status;
}

int s21_normalize_and_round(s21_buffer *source, s21_decimal *destination) {
  int status = OK;
  int last_discarded_digit = 0;
  int sum_of_discarded_digits = 0;
  int scale = s21_get_long_scale(source);

  while ((s21_has_long_bits(source) && scale > 0) || scale > 28) {
    last_discarded_digit = s21_div_long_by_ten(source);

    sum_of_discarded_digits += last_discarded_digit;
    scale--;
  }

  s21_set_long_scale(source, scale);

  if (s21_has_long_bits(source)) {
    status = (s21_get_long_sign(source) == POSITIVE) ? POSITIVE_INFINITY_ERR
                                                     : NEGATIVE_INFINITY_ERR;
  } else {
    int is_last_bit_odd = s21_get_long_bit(source, 0) == 1;

    if (s21_is_not_max_value_ignore_scale(source) &&
        (last_discarded_digit > 5 ||
         (last_discarded_digit == 5 &&
          sum_of_discarded_digits > last_discarded_digit) ||
         (last_discarded_digit == 5 && sum_of_discarded_digits == 5 &&
          is_last_bit_odd))) {
      s21_increase_long_by_one(source);
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
      destination->bits[i] = source->bits[i];
    }

    destination->bits[ARRAY_SIZE] = source->bits[LONG_ARRAY_SIZE];
  }

  return status;
}

void s21_mul_long_by_ten(s21_buffer *value) {
  s21_buffer mul_by_2_value = INIT_ZERO_s21_buffer;
  s21_copy_long(value, &mul_by_2_value);
  s21_shift_long_bits_to_left(&mul_by_2_value, 1);
  s21_buffer mul_by_8_value = INIT_ZERO_s21_buffer;
  s21_copy_long(value, &mul_by_8_value);
  s21_shift_long_bits_to_left(&mul_by_8_value, 3);
  s21_add_long_bits_ignore_scale(&mul_by_2_value, &mul_by_8_value, value);
}

int s21_div_long_by_ten(s21_buffer *value) {
  s21_buffer value_copy = INIT_ZERO_s21_buffer;
  s21_copy_long(value, &value_copy);
  s21_buffer ten = INIT_ZERO_s21_buffer;
  ten.bits[0] = 10;
  s21_buffer remainder = INIT_ZERO_s21_buffer;
  s21_integer_div_long_ignore_scale(&value_copy, &ten, value, &remainder);

  return remainder.bits[0];
}

int s21_max(int first, int second) { return first > second ? first : second; }

int s21_min(int first, int second) { return first < second ? first : second; }

void s21_add_long_bits_ignore_scale(s21_buffer *first, s21_buffer *second,
                                    s21_buffer *result) {
  s21_reset_long_only_bits(result);
  int actual_index =
      s21_min(MAX_LONG_INDEX, 1 + s21_max(s21_get_top_long_bit_index(first),
                                          s21_get_top_long_bit_index(second)));

  for (int i = 0, buffer = 0; i <= actual_index; i++) {
    int sum = s21_get_long_bit(first, i) + s21_get_long_bit(second, i) + buffer;

    if (sum == 1 || sum == 3) {
      s21_set_long_bit(result, i);
    }

    buffer = sum < 2 ? 0 : 1;
  }
}

void s21_sub_long_bits_ignore_scale(s21_buffer *first, s21_buffer *second,
                                    s21_buffer *result) {
  s21_reset_long_only_bits(result);
  int first_top_bit_index = s21_get_top_long_bit_index(first);

  for (int i = 0, buffer = 0; i <= first_top_bit_index; i++) {
    int difference =
        s21_get_long_bit(first, i) - s21_get_long_bit(second, i) - buffer;

    if (difference == 1 || difference == -1) {
      s21_set_long_bit(result, i);
    }

    buffer = difference >= 0 ? 0 : 1;
  }
}

int s21_integer_div_long_ignore_scale(s21_buffer *value, s21_buffer *divider,
                                      s21_buffer *result,
                                      s21_buffer *remainder) {
  if (s21_is_long_zero(divider)) {
    return NAN_RESULT_ERR;
  }

  s21_reset_long_only_bits(result);
  s21_copy_long(value, remainder);

  if (s21_compare_only_long_bits(value, divider) >= 0) {
    int shift =
        s21_get_top_long_bit_index(value) - s21_get_top_long_bit_index(divider);
    s21_buffer shifted_divider = INIT_ZERO_s21_buffer;
    s21_copy_long(divider, &shifted_divider);
    s21_shift_long_bits_to_left(&shifted_divider, shift);

    for (int i = shift; i >= 0; i--) {
      if (s21_compare_only_long_bits(remainder, &shifted_divider) >= 0) {
        s21_buffer buffer = INIT_ZERO_s21_buffer;
        s21_copy_long(remainder, &buffer);
        s21_sub_long_bits_ignore_scale(&buffer, &shifted_divider, remainder);
        s21_set_long_bit(result, i);
      }

      if (i) s21_shift_long_bits_to_right(&shifted_divider, 1);
    }
  }

  return OK;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_compare(&value_1, &value_2) < 0 ? TRUE : FALSE;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_compare(&value_1, &value_2) <= 0 ? TRUE : FALSE;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_compare(&value_1, &value_2) > 0 ? TRUE : FALSE;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_compare(&value_1, &value_2) >= 0 ? TRUE : FALSE;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_compare(&value_1, &value_2) == 0 ? TRUE : FALSE;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_compare(&value_1, &value_2) != 0 ? TRUE : FALSE;
}

int s21_compare(s21_decimal *value_1, s21_decimal *value_2) {
  int result = 0;

  if (s21_is_valid(value_1) && s21_is_valid(value_2)) {
    s21_buffer first = INIT_ZERO_s21_buffer;
    s21_extend(value_1, &first);
    s21_buffer second = INIT_ZERO_s21_buffer;
    s21_extend(value_2, &second);

    int first_sign = s21_get_long_sign(&first);
    int second_sign = s21_get_long_sign(&second);

    if (s21_is_long_zero(&first) && s21_is_long_zero(&second)) {
      result = 0;
    } else if (first_sign == NEGATIVE && second_sign == POSITIVE) {
      result = -1;
    } else if (first_sign == POSITIVE && second_sign == NEGATIVE) {
      result = 1;
    } else {
      s21_equalize_long_scale(&first, &second);
      result = s21_compare_only_long_bits(&first, &second);
      if (first_sign == NEGATIVE) {
        result *= -1;
      }
    }
  }

  return result;
}

int s21_from_int_to_decimal(int srs, s21_decimal *dst) {
  if (dst == NULL) {
    return ERROR;
  }

  s21_reset(dst);

  if (srs < 0) {
    s21_set_sign(dst, NEGATIVE);
    srs = -srs;
  }

  if (srs == INT_MIN) {
    s21_set_bit(dst, 31);
  } else {
    dst->bits[0] = srs;
  }

  return OK;
}

float s21_fabsf(float value) {
  return value == value && value >= 0.0 ? value : value * (-1.0);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL || src != src || s21_fabsf(src) > 3.4E+38) {
    return ERROR;
  }

  int status = OK;
  s21_reset(dst);

  if (s21_fabsf(src) < TOO_SMALL || s21_fabsf(src) > TOO_BIG) {
    status = ERROR;
  } else {
    char string[100];
    sprintf(string, "%.6E", src);

    int value = 0;
    int e_symbol_index = s21_parse_int(string, 'E', &value);

    if (value < 0) {
      value = -value;
      s21_set_sign(dst, NEGATIVE);
    }

    dst->bits[0] = value;

    int scale = 0;
    s21_parse_int(string + e_symbol_index + 1, '\0', &scale);
    scale -= 6;

    if (scale < 0) {
      while (scale < 0 && (dst->bits[0] % 10 == 0)) {
        dst->bits[0] /= 10;
        scale++;
      }
      s21_set_scale(dst, -scale);
    }

    else if (scale > 0) {
      s21_buffer temp = INIT_ZERO_s21_buffer;
      s21_extend(dst, &temp);

      for (int i = 0; i < scale; i++) {
        s21_mul_long_by_ten(&temp);
      }

      s21_normalize_and_round(&temp, dst);
    }
  }
  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = s21_truncate(src, &src);

  for (int i = 1; i < ARRAY_SIZE; i++) {
    if (src.bits[i] != 0) {
      status = ERROR;
    }
  }

  if (status == OK) {
    int sign = s21_get_sign(&src);
    unsigned int absolute_value = (unsigned int)src.bits[0];
    const unsigned int max_int_value = 2147483648u;

    if (absolute_value < max_int_value) {
      *dst = (sign == POSITIVE) ? (int)absolute_value : -((int)absolute_value);
    } else if (absolute_value == max_int_value && sign == NEGATIVE) {
      *dst = INT_MIN;
    } else {
      status = ERROR;
    }
  }

  return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (s21_is_invalid(&src)) {
    return ERROR;
  }

  double number = 0.0;
  double power = 1.0;

  for (int i = 0; i <= MAX_INDEX; i++) {
    if (s21_get_bit(&src, i) == 1) {
      number += power;
    }
    power *= 2.0;
  }

  int scale = s21_get_scale(&src);
  while (scale-- > 0) {
    number /= 10.0;
  }

  int sign = s21_get_sign(&src);
  *dst = (sign == POSITIVE) ? (float)number : -((float)number);

  return OK;
}

void s21_extend(s21_decimal *src, s21_buffer *dst) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    dst->bits[i] = src->bits[i];
  }
  dst->bits[LONG_ARRAY_SIZE] = src->bits[ARRAY_SIZE];
}

void s21_reset(s21_decimal *value) {
  for (int i = 0; i <= ARRAY_SIZE; i++) {
    value->bits[i] = 0;
  }
}

int s21_has_long_bits(s21_buffer *value) {
  int result = FALSE;

  for (int i = ARRAY_SIZE; i < LONG_ARRAY_SIZE && result == FALSE; i++) {
    if (value->bits[i] != 0) {
      result = TRUE;
    }
  }

  return result;
}

int s21_is_not_max_value_ignore_scale(s21_buffer *value) {
  int result = FALSE;

  for (int i = 0; i < ARRAY_SIZE && result == FALSE; i++) {
    if ((unsigned int)value->bits[i] < MAX_32INT) {
      result = TRUE;
    }
  }

  return result;
}

void s21_increase_long_by_one(s21_buffer *value) {
  for (int i = 0; i <= MAX_LONG_INDEX; i++) {
    if (s21_get_long_bit(value, i) == 1) {
      s21_reset_long_bit(value, i);
    } else {
      s21_set_long_bit(value, i);
      i = MAX_LONG_INDEX;
    }
  }
}

int s21_parse_int(char *string, char off_symbol, int *result) {
  int value = 0;
  int off_symbol_index = 0;

  for (int i = 0; string[i] != off_symbol && string[i] != '\0'; i++) {
    if (48 <= string[i] && string[i] <= 57) {
      value *= 10;
      value += (int)string[i] - 48;
    }

    off_symbol_index++;
  }

  if (string[0] == '-') {
    value *= -1;
  }

  *result = value;

  return off_symbol_index;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (s21_is_invalid(&value) || result == NULL) {
    return ERROR;
  }

  int truncated_result = s21_truncate_to_integer(&value, result);

  if (s21_get_sign(&value) == NEGATIVE && truncated_result > 0) {
    s21_increase_by_one(result);
  }

  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (s21_is_invalid(&value) || result == NULL) {
    return ERROR;
  }

  int number = s21_truncate_to_integer(&value, result);

  if (number > 0) {
    int discarded_digit = number % 10;
    int discarded_sum = number / 10;
    int is_odd = s21_get_bit(result, 0);

    if (discarded_digit > 5 ||
        (discarded_digit == 5 &&
         (discarded_sum > 5 || (discarded_sum == 5 && is_odd)))) {
      s21_increase_by_one(result);
    }
  }

  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (s21_is_invalid(&value) || result == NULL) {
    return ERROR;
  }

  s21_truncate_to_integer(&value, result);

  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (s21_is_invalid(&value) || result == NULL) {
    return ERROR;
  }

  s21_copy(&value, result);

  s21_inverse_sign(result);

  return OK;
}

int s21_truncate_to_integer(s21_decimal *source, s21_decimal *destination) {
  if (s21_is_invalid(source) || destination == NULL) {
    return ERROR;
  }

  int discarded_digit = 0;
  int discarded_digits_sum = 0;
  int scale = s21_get_scale(source);

  if (scale == 0) {
    s21_copy(source, destination);
  } else {
    s21_buffer value = INIT_ZERO_S21_DECIMAL;
    s21_extend(source, &value);
    s21_set_long_scale(&value, 0);

    for (int i = 0; i < scale; i++) {
      discarded_digit = s21_div_long_by_ten(&value);
      discarded_digits_sum += discarded_digit;
    }

    s21_normalize_and_round(&value, destination);
  }

  return discarded_digit + discarded_digits_sum * 10;
}

void s21_increase_by_one(s21_decimal *value) {
  for (int i = 0; i <= MAX_INDEX; i++) {
    if (s21_get_bit(value, i) == 0) {
      s21_set_bit(value, i);
      return;
    }
    s21_reset_bit(value, i);
  }
}
