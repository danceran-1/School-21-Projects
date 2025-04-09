#include "test.h"

TEST(Operators, SumMatrix) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  S21Matrix mat2(3, 3);
  initMat(mat2);

  S21Matrix mat3 = mat1 + mat2;

  EXPECT_EQ(mat3(0, 0), 2);
  EXPECT_EQ(mat3(0, 1), 4);
  EXPECT_EQ(mat3(0, 2), 6);
  EXPECT_EQ(mat3(1, 0), 8);
  EXPECT_EQ(mat3(1, 1), 10);
  EXPECT_EQ(mat3(1, 2), 12);
  EXPECT_EQ(mat3(2, 0), 14);
  EXPECT_EQ(mat3(2, 1), 16);
  EXPECT_EQ(mat3(2, 2), 18);
}

TEST(Operators, SumMatrixError) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(3, 4);
  try {
    S21Matrix mat3 = mat1 + mat2;
  } catch (...) {
    return;
  }
  FAIL();
}

TEST(Operators, SubMatrix) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  S21Matrix mat2(3, 3);
  initMat(mat2);

  S21Matrix mat3 = mat1 - mat2;

  EXPECT_EQ(mat3(0, 0), 0);
  EXPECT_EQ(mat3(0, 1), 0);
  EXPECT_EQ(mat3(0, 2), 0);
  EXPECT_EQ(mat3(1, 0), 0);
  EXPECT_EQ(mat3(1, 1), 0);
  EXPECT_EQ(mat3(1, 2), 0);
  EXPECT_EQ(mat3(2, 0), 0);
  EXPECT_EQ(mat3(2, 1), 0);
  EXPECT_EQ(mat3(2, 2), 0);
}

TEST(Operators, SubMatrixError) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(3, 4);
  try {
    S21Matrix mat3 = mat1 - mat2;
  } catch (...) {
    return;
  }
  FAIL();
}

TEST(Operators, MulNumber) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  S21Matrix mat2 = mat1 * 2;

  EXPECT_EQ(mat2(0, 0), 2);
  EXPECT_EQ(mat2(0, 1), 4);
  EXPECT_EQ(mat2(0, 2), 6);
  EXPECT_EQ(mat2(1, 0), 8);
  EXPECT_EQ(mat2(1, 1), 10);
  EXPECT_EQ(mat2(1, 2), 12);
  EXPECT_EQ(mat2(2, 0), 14);
  EXPECT_EQ(mat2(2, 1), 16);
  EXPECT_EQ(mat2(2, 2), 18);
}

TEST(Operators, MulMatrix) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 4);
  initMat(mat2);

  S21Matrix mat3 = mat1 * mat2;

  EXPECT_EQ(mat3(0, 0), 38);
  EXPECT_EQ(mat3(0, 1), 44);
  EXPECT_EQ(mat3(0, 2), 50);
  EXPECT_EQ(mat3(0, 3), 56);
  EXPECT_EQ(mat3(1, 0), 83);
  EXPECT_EQ(mat3(1, 1), 98);
  EXPECT_EQ(mat3(1, 2), 113);
  EXPECT_EQ(mat3(1, 3), 128);
  EXPECT_EQ(mat3(2, 0), 128);
  EXPECT_EQ(mat3(2, 1), 152);
  EXPECT_EQ(mat3(2, 2), 176);
  EXPECT_EQ(mat3(2, 3), 200);
}

TEST(Operators, MulMatrixError) {
  S21Matrix mat1(3, 3);
  S21Matrix mat2(4, 3);
  try {
    S21Matrix mat3 = mat1 * mat2;
  } catch (...) {
    return;
  }
  FAIL();
}

TEST(Operators, Equal) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  initMat(mat2);

  EXPECT_TRUE(mat1 == mat2);
}

TEST(Operators, Assign1) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  mat2 = mat1;
  EXPECT_TRUE(mat1 == mat2);
}

TEST(Operators, Assign2) {
  S21Matrix mat1(3, 0);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  mat2 = mat1;
  EXPECT_TRUE(mat1 == mat2);
}

TEST(Operators, AssignMove) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2 = mat1;
  S21Matrix mat3(4, 4);
  mat3 = std::move(mat2);
  EXPECT_TRUE(mat1 == mat3);
}

TEST(Operators, SumEqual) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  initMat(mat2);
  mat1 += mat2;

  EXPECT_EQ(mat1(0, 0), 2);
  EXPECT_EQ(mat1(0, 1), 4);
  EXPECT_EQ(mat1(0, 2), 6);
  EXPECT_EQ(mat1(1, 0), 8);
  EXPECT_EQ(mat1(1, 1), 10);
  EXPECT_EQ(mat1(1, 2), 12);
  EXPECT_EQ(mat1(2, 0), 14);
  EXPECT_EQ(mat1(2, 1), 16);
  EXPECT_EQ(mat1(2, 2), 18);
}

TEST(Operators, SubEqual) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  initMat(mat2);
  mat1 -= mat2;

  EXPECT_EQ(mat1(0, 0), 0);
  EXPECT_EQ(mat1(0, 1), 0);
  EXPECT_EQ(mat1(0, 2), 0);
  EXPECT_EQ(mat1(1, 0), 0);
  EXPECT_EQ(mat1(1, 1), 0);
  EXPECT_EQ(mat1(1, 2), 0);
  EXPECT_EQ(mat1(2, 0), 0);
  EXPECT_EQ(mat1(2, 1), 0);
  EXPECT_EQ(mat1(2, 2), 0);
}

TEST(Operators, MulEqualNumber) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  mat1 *= 2;

  EXPECT_EQ(mat1(0, 0), 2);
  EXPECT_EQ(mat1(0, 1), 4);
  EXPECT_EQ(mat1(0, 2), 6);
  EXPECT_EQ(mat1(1, 0), 8);
  EXPECT_EQ(mat1(1, 1), 10);
  EXPECT_EQ(mat1(1, 2), 12);
  EXPECT_EQ(mat1(2, 0), 14);
  EXPECT_EQ(mat1(2, 1), 16);
  EXPECT_EQ(mat1(2, 2), 18);
}

TEST(Operators, MulEqualMatrix) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  initMat(mat2);
  mat1 *= mat2;

  EXPECT_EQ(mat1(0, 0), 30);
  EXPECT_EQ(mat1(0, 1), 36);
  EXPECT_EQ(mat1(0, 2), 42);
  EXPECT_EQ(mat1(1, 0), 66);
  EXPECT_EQ(mat1(1, 1), 81);
  EXPECT_EQ(mat1(1, 2), 96);
  EXPECT_EQ(mat1(2, 0), 102);
  EXPECT_EQ(mat1(2, 1), 126);
  EXPECT_EQ(mat1(2, 2), 150);
}

TEST(Operators, Brackets) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  EXPECT_EQ(mat1(0, 0), 1);
  EXPECT_EQ(mat1(0, 1), 2);
  EXPECT_EQ(mat1(0, 2), 3);
  EXPECT_EQ(mat1(1, 0), 4);
  EXPECT_EQ(mat1(1, 1), 5);
  EXPECT_EQ(mat1(1, 2), 6);
  EXPECT_EQ(mat1(2, 0), 7);
  EXPECT_EQ(mat1(2, 1), 8);
  EXPECT_EQ(mat1(2, 2), 9);
}

TEST(Operators, BracketsError) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  EXPECT_ANY_THROW(mat1(3, 3));
}
