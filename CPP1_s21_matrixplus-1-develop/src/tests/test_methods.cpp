#include <gtest/gtest.h>

#include "test.h"

TEST(Methods, Equal1) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2 = mat1;

  EXPECT_TRUE(mat1.EqMatrix(mat2));
}

TEST(Methods, Equal2) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  EXPECT_TRUE(mat1.EqMatrix(mat1));
}

TEST(Methods, Equal3) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 4);
  initMat(mat2);

  EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST(Methods, SumMatrix) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  initMat(mat2);

  mat1.SumMatrix(mat2);

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

TEST(Methods, SumMatrixError) {
  S21Matrix mat1(10, 15);
  initMat(mat1);
  S21Matrix mat2(10, 16);
  initMat(mat2);

  EXPECT_ANY_THROW(mat1.SumMatrix(mat2));
}

TEST(Methods, SubMatrix) {
  S21Matrix mat1(3, 3);
  initMat(mat1);
  S21Matrix mat2(3, 3);
  initMat(mat2);

  mat1.SubMatrix(mat2);

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

TEST(Methods, SubMatrixError) {
  S21Matrix mat1(25, 35);
  initMat(mat1);
  S21Matrix mat2(25, 36);
  initMat(mat2);

  EXPECT_ANY_THROW(mat1.SubMatrix(mat2));
}

TEST(Methods, MulNumber) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.MulNumber(2);

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

TEST(Methods, MulMatrix) {
  S21Matrix mat1(3, 4);
  initMat(mat1);
  S21Matrix mat2(4, 3);
  initMat(mat2);

  mat1.MulMatrix(mat2);

  EXPECT_EQ(mat1(0, 0), 70);
  EXPECT_EQ(mat1(0, 1), 80);
  EXPECT_EQ(mat1(0, 2), 90);
  EXPECT_EQ(mat1(1, 0), 158);
  EXPECT_EQ(mat1(1, 1), 184);
  EXPECT_EQ(mat1(1, 2), 210);
  EXPECT_EQ(mat1(2, 0), 246);
  EXPECT_EQ(mat1(2, 1), 288);
  EXPECT_EQ(mat1(2, 2), 330);
}

TEST(Methods, MulMatrixError) {
  S21Matrix mat1(3, 4);
  initMat(mat1);
  S21Matrix mat2(3, 4);
  initMat(mat2);

  EXPECT_ANY_THROW(mat1.MulMatrix(mat2));
}

TEST(Methods, Transpose) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1 = mat1.Transpose();

  EXPECT_EQ(mat1(0, 0), 1);
  EXPECT_EQ(mat1(0, 1), 4);
  EXPECT_EQ(mat1(0, 2), 7);
  EXPECT_EQ(mat1(1, 0), 2);
  EXPECT_EQ(mat1(1, 1), 5);
  EXPECT_EQ(mat1(1, 2), 8);
  EXPECT_EQ(mat1(2, 0), 3);
  EXPECT_EQ(mat1(2, 1), 6);
  EXPECT_EQ(mat1(2, 2), 9);
}

TEST(Methods, CalcComplements) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1 = mat1.CalcComplements();

  EXPECT_EQ(mat1(0, 0), -3);
  EXPECT_EQ(mat1(0, 1), 6);
  EXPECT_EQ(mat1(0, 2), -3);
  EXPECT_EQ(mat1(1, 0), 6);
  EXPECT_EQ(mat1(1, 1), -12);
  EXPECT_EQ(mat1(1, 2), 6);
  EXPECT_EQ(mat1(2, 0), -3);
  EXPECT_EQ(mat1(2, 1), 6);
  EXPECT_EQ(mat1(2, 2), -3);
}

TEST(Methods, CalcComplementsError) {
  S21Matrix mat1(3, 4);

  EXPECT_ANY_THROW(mat1.CalcComplements());
}

TEST(Methods, Determinant) {
  S21Matrix mat1(5, 5);
  initMat(mat1);

  EXPECT_EQ(mat1.Determinant(), 0);
}

TEST(Methods, DeterminantError) {
  S21Matrix mat1(4, 5);

  EXPECT_ANY_THROW(mat1.Determinant());
}

TEST(Methods, InverseMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 6;
  mat1(0, 1) = 7;
  mat1(1, 0) = 2;
  mat1(1, 1) = 4;

  mat1 = mat1.InverseMatrix();

  EXPECT_EQ(mat1(0, 0), 0.4);

  EXPECT_EQ(mat1(1, 0), -0.2);
}

TEST(Methods, InverseMatrixError1) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  EXPECT_ANY_THROW(mat1.InverseMatrix());
}

TEST(Methods, InverseMatrixError2) {
  S21Matrix mat1(3, 4);

  EXPECT_ANY_THROW(mat1.InverseMatrix());
}

TEST(Methods, MinorError1) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  EXPECT_ANY_THROW(mat1.GetMinor(3, 3));
}

TEST(Methods, MinorError2) {
  S21Matrix mat1(3, 2);
  initMat(mat1);

  EXPECT_ANY_THROW(mat1.GetMinor(1, 1));
}
