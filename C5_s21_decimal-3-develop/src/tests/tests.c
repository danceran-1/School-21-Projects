#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

START_TEST(s21_add1) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add2) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 1;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 1;
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add3) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 123;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 8645123;
  s21_set_sign(&second, NEGATIVE);
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = 8645000;
  s21_set_sign(&sum, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add4) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 1;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[1] = 1;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add5) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = MAX_32INT - 1;
  sum.bits[1] = MAX_32INT;
  sum.bits[2] = 1;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add6) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 1024512;
  s21_set_scale(&first, 3);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 60044444;
  s21_set_scale(&second, 5);
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = 162495644;
  s21_set_scale(&sum, 5);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add7) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 6;
  s21_set_scale(&first, 1);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = MAX_32INT;
  sum.bits[1] = MAX_32INT;
  sum.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add8) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  s21_set_scale(&second, 28);
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = MAX_32INT;
  sum.bits[1] = MAX_32INT;
  sum.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add9) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 14;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 500;
  s21_set_scale(&second, 3);
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = 14;
  sum.bits[1] = MAX_32INT;
  sum.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add10) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 14;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 51;
  s21_set_scale(&second, 2);
  s21_decimal sum = INIT_ZERO_S21_DECIMAL;
  sum.bits[0] = 15;
  sum.bits[1] = MAX_32INT;
  sum.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(sum.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add11) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_add(first, second, NULL), NAN_RESULT_ERR);
}
END_TEST

START_TEST(s21_sub1) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub2) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 3;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 5;
  s21_set_sign(&second, NEGATIVE);
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = 2;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub3) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 753009;
  s21_set_scale(&first, 3);
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 82200321;
  s21_set_scale(&second, 5);
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = 157501221;
  s21_set_scale(&difference, 5);
  s21_set_sign(&difference, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub4) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[1] = MAX_32INT;
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = MAX_32INT;
  difference.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub5) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 3;
  s21_set_scale(&second, 1);
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = MAX_32INT;
  difference.bits[1] = MAX_32INT;
  difference.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub6) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 9;
  s21_set_scale(&second, 1);
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = MAX_32INT - 1;
  difference.bits[1] = MAX_32INT;
  difference.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub7) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 5;
  s21_set_scale(&second, 1);
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = MAX_32INT - 1;
  difference.bits[1] = MAX_32INT;
  difference.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub8) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT - 1;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 5;
  s21_set_scale(&second, 1);
  s21_decimal difference = INIT_ZERO_S21_DECIMAL;
  difference.bits[0] = MAX_32INT - 1;
  difference.bits[1] = MAX_32INT;
  difference.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(difference.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_sub9) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_scale(&second, 28);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), NEGATIVE_INFINITY_ERR);
}
END_TEST

START_TEST(s21_sub10) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  s21_set_scale(&second, 333);
  s21_set_sign(&second, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, &result), POSITIVE_INFINITY_ERR);
}
END_TEST

START_TEST(s21_sub11) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_sub(first, second, NULL), NAN_RESULT_ERR);
}
END_TEST

START_TEST(s21_mul1) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 62;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 48;
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  composition.bits[0] = 2976;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul2) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[1] = 83;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 1;
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  composition.bits[1] = 83;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul3) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  s21_set_sign(&composition, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul4) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[1] = 83;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 10;
  s21_set_scale(&second, 1);
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  composition.bits[1] = 830;
  s21_set_scale(&composition, 1);
  s21_set_sign(&composition, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul5) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_sign(&second, NEGATIVE);
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul6) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 115904;
  s21_set_sign(&first, NEGATIVE);
  s21_set_scale(&first, 2);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 785;
  s21_set_scale(&second, 1);
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  composition.bits[0] = 90984640;
  s21_set_sign(&composition, NEGATIVE);
  s21_set_scale(&composition, 3);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul7) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 0b01010101010101010101010101010101;
  first.bits[1] = 0b01010101010101010101010101010101;
  first.bits[2] = 0b01010101010101010101010101010101;
  s21_set_scale(&first, 21);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 5;
  s21_set_scale(&second, 16);
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  composition.bits[0] = 0b00101110101111011111010100110101;
  composition.bits[1] = 0b00101000100001001111011000010000;
  composition.bits[2] = 0b00000000000000000000000000000111;
  s21_set_scale(&composition, 28);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul8) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 2032156321;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 1200555987;
  s21_decimal composition = INIT_ZERO_S21_DECIMAL;
  composition.bits[0] = 0b01011010001110010000010110110011;
  composition.bits[1] = 0b00100001110110111001111000010101;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(composition.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul9) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[2] = MAX_32INT;
  s21_set_scale(&first, 28);
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_sign(&second, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), POSITIVE_INFINITY_ERR);
}
END_TEST

START_TEST(s21_mul10) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_scale(&second, 28);
  s21_set_sign(&second, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, &result), NEGATIVE_INFINITY_ERR);
}
END_TEST

START_TEST(s21_mul11) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_mul(first, second, NULL), NAN_RESULT_ERR);
}
END_TEST

START_TEST(s21_mul12) {
  s21_buffer first = INIT_ZERO_s21_buffer;
  s21_buffer mul_by_ten_first = INIT_ZERO_s21_buffer;

  s21_mul_long_by_ten(&first);

  for (int i = 0; i <= LONG_ARRAY_SIZE; i++) {
    ck_assert_int_eq(first.bits[i], mul_by_ten_first.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul13) {
  s21_buffer first = INIT_ZERO_s21_buffer;
  first.bits[0] = 55;
  s21_buffer mul_by_ten_first = INIT_ZERO_s21_buffer;
  mul_by_ten_first.bits[0] = 550;

  s21_mul_long_by_ten(&first);

  for (int i = 0; i <= LONG_ARRAY_SIZE; i++) {
    ck_assert_int_eq(first.bits[i], mul_by_ten_first.bits[i]);
  }
}
END_TEST

START_TEST(s21_mul14) {
  s21_buffer first = INIT_ZERO_s21_buffer;
  first.bits[1] = 123;
  s21_set_long_sign(&first, NEGATIVE);
  s21_buffer mul_by_ten_first = INIT_ZERO_s21_buffer;
  mul_by_ten_first.bits[1] = 1230;
  s21_set_long_sign(&mul_by_ten_first, NEGATIVE);

  s21_mul_long_by_ten(&first);

  for (int i = 0; i <= LONG_ARRAY_SIZE; i++) {
    ck_assert_int_eq(first.bits[i], mul_by_ten_first.bits[i]);
  }
}
END_TEST

START_TEST(s21_negate1) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1;
  s21_decimal negate_value = INIT_ZERO_S21_DECIMAL;
  negate_value.bits[0] = 1;
  s21_set_sign(&negate_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_negate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(negate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_negate2) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[2] = 1;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal negate_value = INIT_ZERO_S21_DECIMAL;
  negate_value.bits[2] = 1;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_negate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(negate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_negate3) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  value.bits[2] = MAX_32INT;
  s21_decimal negate_value = INIT_ZERO_S21_DECIMAL;
  negate_value.bits[0] = MAX_32INT;
  negate_value.bits[1] = MAX_32INT;
  negate_value.bits[2] = MAX_32INT;
  s21_set_sign(&negate_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_negate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(negate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_negate4) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_negate(value, NULL), ERROR);
}
END_TEST

START_TEST(s21_div1) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 123;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), NAN_RESULT_ERR);
}
END_TEST

START_TEST(s21_div2) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 321;
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  s21_set_sign(&quotient, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div3) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 36;
  s21_set_scale(&first, 25);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 24;
  s21_set_scale(&second, 25);
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 15;
  s21_set_scale(&quotient, 1);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div4) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 93074;
  s21_set_scale(&first, 2);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 173;
  s21_set_scale(&second, 1);
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 538;
  s21_set_scale(&quotient, 1);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div5) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 254;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 640;
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 396875;
  s21_set_scale(&quotient, 6);
  s21_set_sign(&quotient, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div6) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 89;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 25;
  s21_set_scale(&second, 1);
  s21_set_sign(&second, NEGATIVE);
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 356;
  s21_set_scale(&quotient, 1);
  s21_set_sign(&quotient, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div7) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[1] = 1 << 28;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 8;
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[1] = 1 << 25;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div8) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[2] = MAX_32INT - 1;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[2] = 2147483647;
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 2;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div9) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_sign(&first, NEGATIVE);
  s21_set_scale(&first, 5);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_scale(&second, 14);
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 1000000000;
  s21_set_sign(&quotient, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div10) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_sign(&first, NEGATIVE);
  s21_set_scale(&first, 5);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_scale(&second, 3);
  s21_decimal quotient = INIT_ZERO_S21_DECIMAL;
  quotient.bits[0] = 1;
  s21_set_sign(&quotient, NEGATIVE);
  s21_set_scale(&quotient, 2);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(quotient.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_div11) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_div(first, second, NULL), NAN_RESULT_ERR);
}
END_TEST

START_TEST(s21_truncate1) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  s21_decimal truncate_value = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_truncate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(truncate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_truncate2) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[2] = MAX_32INT;
  s21_decimal truncate_value = INIT_ZERO_S21_DECIMAL;
  truncate_value.bits[2] = MAX_32INT;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_truncate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(truncate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_truncate3) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 150000;
  s21_set_scale(&value, 5);
  s21_decimal truncate_value = INIT_ZERO_S21_DECIMAL;
  truncate_value.bits[0] = 1;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_truncate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(truncate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_truncate4) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 400000000;
  s21_set_scale(&value, 7);
  s21_set_sign(&value, NEGATIVE);
  s21_decimal truncate_value = INIT_ZERO_S21_DECIMAL;
  truncate_value.bits[0] = 40;
  s21_set_sign(&truncate_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_truncate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(truncate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_truncate5) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  value.bits[2] = MAX_32INT;
  s21_set_scale(&value, 28);
  s21_decimal truncate_value = INIT_ZERO_S21_DECIMAL;
  truncate_value.bits[0] = 7;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_truncate(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(truncate_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_truncate6) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_truncate(value, NULL), ERROR);
}
END_TEST

START_TEST(s21_round1) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1;
  s21_decimal round_value = INIT_ZERO_S21_DECIMAL;
  round_value.bits[0] = 1;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_round(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(round_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_round2) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 250000;
  s21_set_scale(&value, 5);
  s21_decimal round_value = INIT_ZERO_S21_DECIMAL;
  round_value.bits[0] = 2;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_round(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(round_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_round3) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 56888;
  s21_set_scale(&value, 2);
  s21_decimal round_value = INIT_ZERO_S21_DECIMAL;
  round_value.bits[0] = 569;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_round(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(round_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_round4) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  s21_set_sign(&value, NEGATIVE);
  s21_set_scale(&value, 28);
  s21_decimal round_value = INIT_ZERO_S21_DECIMAL;
  s21_set_sign(&round_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_round(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(round_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_round5) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  value.bits[2] = MAX_32INT;
  s21_set_sign(&value, NEGATIVE);
  s21_set_scale(&value, 28);
  s21_decimal round_value = INIT_ZERO_S21_DECIMAL;
  round_value.bits[0] = 8;
  s21_set_sign(&round_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_round(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(round_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_round6) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_round(value, NULL), ERROR);
}
END_TEST

START_TEST(s21_floor1) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal floor_value = INIT_ZERO_S21_DECIMAL;
  floor_value.bits[0] = 1;
  s21_set_sign(&floor_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_floor(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(floor_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_floor2) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 56;
  s21_set_scale(&value, 1);
  s21_decimal floor_value = INIT_ZERO_S21_DECIMAL;
  floor_value.bits[0] = 5;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_floor(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(floor_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_floor3) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 99999999;
  s21_set_scale(&value, 8);
  s21_decimal floor_value = INIT_ZERO_S21_DECIMAL;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_floor(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(floor_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_floor4) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  s21_set_scale(&value, 28);
  s21_set_sign(&value, NEGATIVE);
  s21_decimal floor_value = INIT_ZERO_S21_DECIMAL;
  floor_value.bits[0] = 1;
  s21_set_sign(&floor_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_floor(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(floor_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_floor5) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  value.bits[2] = MAX_32INT;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal floor_value = INIT_ZERO_S21_DECIMAL;
  floor_value.bits[0] = MAX_32INT;
  floor_value.bits[1] = MAX_32INT;
  floor_value.bits[2] = MAX_32INT;
  s21_set_sign(&floor_value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_floor(value, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(floor_value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_floor6) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_floor(value, NULL), ERROR);
}
END_TEST

START_TEST(s21_compare1) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  s21_set_sign(&second, NEGATIVE);

  ck_assert_int_eq(s21_is_less(first, second), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_greater(first, second), FALSE);
  ck_assert_int_eq(s21_is_greater_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_not_equal(first, second), FALSE);
}
END_TEST

START_TEST(s21_compare2) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_scale(&first, 16);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_scale(&second, 24);

  ck_assert_int_eq(s21_is_less(first, second), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_greater(first, second), TRUE);
  ck_assert_int_eq(s21_is_greater_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_not_equal(first, second), TRUE);
}
END_TEST

START_TEST(s21_compare3) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = 56000;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = 1;

  ck_assert_int_eq(s21_is_less(first, second), TRUE);
  ck_assert_int_eq(s21_is_less_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_greater(first, second), FALSE);
  ck_assert_int_eq(s21_is_greater_or_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_not_equal(first, second), TRUE);
}
END_TEST

START_TEST(s21_compare4) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT - 1;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_sign(&first, NEGATIVE);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_sign(&second, NEGATIVE);

  ck_assert_int_eq(s21_is_less(first, second), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_greater(first, second), TRUE);
  ck_assert_int_eq(s21_is_greater_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_not_equal(first, second), TRUE);
}
END_TEST

START_TEST(s21_compare5) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT - 1;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_set_scale(&first, 28);
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_scale(&second, 28);

  ck_assert_int_eq(s21_is_less(first, second), TRUE);
  ck_assert_int_eq(s21_is_less_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_greater(first, second), FALSE);
  ck_assert_int_eq(s21_is_greater_or_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_not_equal(first, second), TRUE);
}
END_TEST

START_TEST(s21_compare6) {
  s21_decimal first = INIT_ZERO_S21_DECIMAL;
  first.bits[0] = MAX_32INT;
  first.bits[1] = MAX_32INT;
  first.bits[2] = MAX_32INT;
  s21_decimal second = INIT_ZERO_S21_DECIMAL;
  second.bits[0] = MAX_32INT;
  second.bits[1] = MAX_32INT;
  second.bits[2] = MAX_32INT;
  s21_set_sign(&second, NEGATIVE);

  ck_assert_int_eq(s21_is_less(first, second), FALSE);
  ck_assert_int_eq(s21_is_less_or_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_greater(first, second), TRUE);
  ck_assert_int_eq(s21_is_greater_or_equal(first, second), TRUE);
  ck_assert_int_eq(s21_is_equal(first, second), FALSE);
  ck_assert_int_eq(s21_is_not_equal(first, second), TRUE);
}
END_TEST

START_TEST(s21_compare7) { ck_assert_int_eq(s21_compare(NULL, NULL), FALSE); }
END_TEST

START_TEST(s21_int1) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[ARRAY_SIZE] = MAX_32INT;

  ck_assert_int_eq(s21_is_invalid(&value), TRUE);
}
END_TEST

START_TEST(s21_int2) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[ARRAY_SIZE] = 0b00000000000111110000000000000000;

  ck_assert_int_eq(s21_is_valid(&value), FALSE);
}
END_TEST

START_TEST(s21_int3) {
  int number = -1;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_int_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_int4) {
  int number = INT_MAX;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT >> 1;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_int_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_int5) {
  int number = INT_MIN;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1U << 31;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_int_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_int6) {
  int number = 321123;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 321123;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_int_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_int7) {
  int number = -2147483647;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 2147483647;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_int_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(s21_int8) {
  int number = 0;

  ck_assert_int_eq(s21_from_int_to_decimal(number, NULL), ERROR);
}
END_TEST

START_TEST(s21_int9) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 0;
  s21_set_sign(&value, NEGATIVE);
  int number = 0;
  int result = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), OK);
  ck_assert_int_eq(number, result);
}
END_TEST

START_TEST(s21_int10) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 2147483647;
  int number = INT_MAX;
  int result = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), OK);
  ck_assert_int_eq(number, result);
}
END_TEST

START_TEST(s21_int11) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1U << 31;
  s21_set_sign(&value, NEGATIVE);
  int number = -2147483648;
  int result = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), OK);
  ck_assert_int_eq(number, result);
}
END_TEST

START_TEST(s21_int12) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1U << 31;
  int result = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), ERROR);
}
END_TEST

START_TEST(s21_int13) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  s21_set_sign(&value, NEGATIVE);
  int result = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), ERROR);
}
END_TEST

START_TEST(s21_int14) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[1] = 5;
  int result = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), ERROR);
}
END_TEST

START_TEST(s21_float2) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;

  value.bits[0] = 0b00101110101111011111010100110101;
  value.bits[1] = 0b00101000100001001111011000010000;
  value.bits[2] = 0b00000000000000000000000000000111;
  s21_set_scale(&value, 15);
  float number = 132046.937523773895989;
  float result = 0.0;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), OK);
  ck_assert_float_eq_tol(number, result, EPSILON);
}
END_TEST

START_TEST(s21_float3) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;

  value.bits[0] = 0b01011010001110010000010110110011;
  value.bits[1] = 0b00100001110110111001111000010101;
  s21_set_sign(&value, NEGATIVE);
  float number = -2439717437696443827.0;
  float result = 0.0;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), OK);
  ck_assert_float_eq_tol(number, result, EPSILON);
}
END_TEST

START_TEST(s21_float4) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  value.bits[2] = MAX_32INT;
  s21_set_sign(&value, NEGATIVE);
  float number = -7.9228162514264E+28;
  float result = 0.0;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), OK);
  ck_assert_float_eq_tol(number, result, EPSILON);
}
END_TEST

START_TEST(s21_float5) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = MAX_32INT;
  value.bits[1] = MAX_32INT;
  value.bits[2] = MAX_32INT;
  s21_set_scale(&value, 28);
  float number = 7.9228162514264;
  float result = 0.0;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), OK);
  ck_assert_float_eq_tol(number, result, EPSILON);
}
END_TEST

START_TEST(s21_float6) {
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[3] = MAX_32INT;
  float result = 0.0;

  ck_assert_int_eq(s21_from_decimal_to_float(value, &result), ERROR);
}
END_TEST

START_TEST(s21_float7) {
  float number = -123.0;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 123;
  s21_set_sign(&value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float8) {
  float number = NAN;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), ERROR);
}
END_TEST

START_TEST(s21_float9) {
  float number = INFINITY;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), ERROR);
}
END_TEST

START_TEST(s21_float10) {
  float number = 9E+28;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), ERROR);
}
END_TEST

START_TEST(s21_float11) {
  float number = -1E-30;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 0;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), ERROR);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float12) {
  float number = 1234567890;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 1234568000;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float13) {
  float number = 599E-8;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 599;
  s21_set_scale(&value, 8);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float14) {
  float number = -862.00005;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 8620001;
  s21_set_scale(&value, 4);
  s21_set_sign(&value, NEGATIVE);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float15) {
  float number = 75000.57;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 7500057;
  s21_set_scale(&value, 2);
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float16) {
  float number = 312E+09;
  s21_decimal value = INIT_ZERO_S21_DECIMAL;
  value.bits[0] = 0b10100100101001100011000000000000;
  value.bits[1] = 0b00000000000000000000000001001000;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);

  for (int i = 0; i <= ARRAY_SIZE; i++) {
    ck_assert_int_eq(value.bits[i], result.bits[i]);
  }

  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float17) {
  float number = 7.922816E+28;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);
  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

START_TEST(s21_float18) {
  float number = -7.922816E+28;
  s21_decimal result = INIT_ZERO_S21_DECIMAL;
  float float_result = 0.0;

  ck_assert_int_eq(s21_from_float_to_decimal(number, &result), OK);
  ck_assert_int_eq(s21_from_decimal_to_float(result, &float_result), OK);
  ck_assert_float_eq_tol(number, float_result, EPSILON);
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *suite = suite_create("s21_decimal");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, s21_add1);
  tcase_add_test(tcase_core, s21_add2);
  tcase_add_test(tcase_core, s21_add3);
  tcase_add_test(tcase_core, s21_add4);
  tcase_add_test(tcase_core, s21_add5);
  tcase_add_test(tcase_core, s21_add6);
  tcase_add_test(tcase_core, s21_add7);
  tcase_add_test(tcase_core, s21_add8);
  tcase_add_test(tcase_core, s21_add9);
  tcase_add_test(tcase_core, s21_add10);
  tcase_add_test(tcase_core, s21_add11);

  tcase_add_test(tcase_core, s21_sub1);
  tcase_add_test(tcase_core, s21_sub2);
  tcase_add_test(tcase_core, s21_sub3);
  tcase_add_test(tcase_core, s21_sub4);
  tcase_add_test(tcase_core, s21_sub5);
  tcase_add_test(tcase_core, s21_sub6);
  tcase_add_test(tcase_core, s21_sub7);
  tcase_add_test(tcase_core, s21_sub8);
  tcase_add_test(tcase_core, s21_sub9);
  tcase_add_test(tcase_core, s21_sub10);
  tcase_add_test(tcase_core, s21_sub11);

  tcase_add_test(tcase_core, s21_mul1);
  tcase_add_test(tcase_core, s21_mul2);
  tcase_add_test(tcase_core, s21_mul3);
  tcase_add_test(tcase_core, s21_mul4);
  tcase_add_test(tcase_core, s21_mul5);
  tcase_add_test(tcase_core, s21_mul6);
  tcase_add_test(tcase_core, s21_mul7);
  tcase_add_test(tcase_core, s21_mul8);
  tcase_add_test(tcase_core, s21_mul9);
  tcase_add_test(tcase_core, s21_mul10);
  tcase_add_test(tcase_core, s21_mul11);
  tcase_add_test(tcase_core, s21_mul12);
  tcase_add_test(tcase_core, s21_mul13);
  tcase_add_test(tcase_core, s21_mul14);

  tcase_add_test(tcase_core, s21_negate1);
  tcase_add_test(tcase_core, s21_negate2);
  tcase_add_test(tcase_core, s21_negate3);
  tcase_add_test(tcase_core, s21_negate4);

  tcase_add_test(tcase_core, s21_div1);
  tcase_add_test(tcase_core, s21_div2);
  tcase_add_test(tcase_core, s21_div3);
  tcase_add_test(tcase_core, s21_div4);
  tcase_add_test(tcase_core, s21_div5);
  tcase_add_test(tcase_core, s21_div6);
  tcase_add_test(tcase_core, s21_div7);
  tcase_add_test(tcase_core, s21_div8);
  tcase_add_test(tcase_core, s21_div9);
  tcase_add_test(tcase_core, s21_div10);
  tcase_add_test(tcase_core, s21_div11);

  tcase_add_test(tcase_core, s21_truncate1);
  tcase_add_test(tcase_core, s21_truncate2);
  tcase_add_test(tcase_core, s21_truncate3);
  tcase_add_test(tcase_core, s21_truncate4);
  tcase_add_test(tcase_core, s21_truncate5);
  tcase_add_test(tcase_core, s21_truncate6);

  tcase_add_test(tcase_core, s21_round1);
  tcase_add_test(tcase_core, s21_round2);
  tcase_add_test(tcase_core, s21_round3);
  tcase_add_test(tcase_core, s21_round4);
  tcase_add_test(tcase_core, s21_round5);
  tcase_add_test(tcase_core, s21_round6);

  tcase_add_test(tcase_core, s21_floor1);
  tcase_add_test(tcase_core, s21_floor2);
  tcase_add_test(tcase_core, s21_floor3);
  tcase_add_test(tcase_core, s21_floor4);
  tcase_add_test(tcase_core, s21_floor5);
  tcase_add_test(tcase_core, s21_floor6);

  tcase_add_test(tcase_core, s21_compare1);
  tcase_add_test(tcase_core, s21_compare2);
  tcase_add_test(tcase_core, s21_compare3);
  tcase_add_test(tcase_core, s21_compare4);
  tcase_add_test(tcase_core, s21_compare5);
  tcase_add_test(tcase_core, s21_compare6);
  tcase_add_test(tcase_core, s21_compare7);

  tcase_add_test(tcase_core, s21_int1);
  tcase_add_test(tcase_core, s21_int2);
  tcase_add_test(tcase_core, s21_int3);
  tcase_add_test(tcase_core, s21_int4);
  tcase_add_test(tcase_core, s21_int5);
  tcase_add_test(tcase_core, s21_int6);
  tcase_add_test(tcase_core, s21_int7);
  tcase_add_test(tcase_core, s21_int8);
  tcase_add_test(tcase_core, s21_int9);
  tcase_add_test(tcase_core, s21_int10);
  tcase_add_test(tcase_core, s21_int11);
  tcase_add_test(tcase_core, s21_int12);
  tcase_add_test(tcase_core, s21_int13);
  tcase_add_test(tcase_core, s21_int14);

  tcase_add_test(tcase_core, s21_float2);
  tcase_add_test(tcase_core, s21_float3);
  tcase_add_test(tcase_core, s21_float4);
  tcase_add_test(tcase_core, s21_float5);
  tcase_add_test(tcase_core, s21_float6);
  tcase_add_test(tcase_core, s21_float7);
  tcase_add_test(tcase_core, s21_float8);
  tcase_add_test(tcase_core, s21_float9);
  tcase_add_test(tcase_core, s21_float10);
  tcase_add_test(tcase_core, s21_float11);
  tcase_add_test(tcase_core, s21_float12);
  tcase_add_test(tcase_core, s21_float13);
  tcase_add_test(tcase_core, s21_float14);
  tcase_add_test(tcase_core, s21_float15);
  tcase_add_test(tcase_core, s21_float16);
  tcase_add_test(tcase_core, s21_float17);
  tcase_add_test(tcase_core, s21_float18);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  int no_failed = 0;
  Suite *suite = s21_decimal_suite();
  SRunner *runner = srunner_create(suite);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
