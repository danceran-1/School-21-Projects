#include "test.h"

TEST(Gets, GetRows) {
  S21Matrix mat1(3, 3);
  EXPECT_EQ(mat1.GetRows(), 3);
}

TEST(Gets, GetCols) {
  S21Matrix mat1(10, 15);
  EXPECT_EQ(mat1.GetCols(), 15);
}

TEST(Sets, SetRows1) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.SetRows(5);

  EXPECT_EQ(mat1.GetRows(), 5);

  EXPECT_EQ(mat1(0, 0), 1);
  EXPECT_EQ(mat1(0, 1), 2);
  EXPECT_EQ(mat1(0, 2), 3);
  EXPECT_EQ(mat1(1, 0), 4);
  EXPECT_EQ(mat1(1, 1), 5);
  EXPECT_EQ(mat1(1, 2), 6);
  EXPECT_EQ(mat1(2, 0), 7);
  EXPECT_EQ(mat1(2, 1), 8);
  EXPECT_EQ(mat1(2, 2), 9);
  EXPECT_EQ(mat1(3, 0), 0);
  EXPECT_EQ(mat1(3, 1), 0);
  EXPECT_EQ(mat1(3, 2), 0);
  EXPECT_EQ(mat1(4, 0), 0);
  EXPECT_EQ(mat1(4, 1), 0);
  EXPECT_EQ(mat1(4, 2), 0);
}

TEST(Sets, SetRows2) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.SetRows(2);

  EXPECT_EQ(mat1.GetRows(), 2);

  EXPECT_EQ(mat1(0, 0), 1);
  EXPECT_EQ(mat1(0, 1), 2);
  EXPECT_EQ(mat1(0, 2), 3);
  EXPECT_EQ(mat1(1, 0), 4);
  EXPECT_EQ(mat1(1, 1), 5);
  EXPECT_EQ(mat1(1, 2), 6);
}

TEST(Sets, SetRows3) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.SetRows(0);

  EXPECT_EQ(mat1.GetRows(), 0);
  EXPECT_EQ(mat1.GetCols(), 0);
}

TEST(Sets, SetCols1) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.SetCols(5);

  EXPECT_EQ(mat1.GetCols(), 5);

  EXPECT_EQ(mat1(0, 0), 1);
  EXPECT_EQ(mat1(0, 1), 2);
  EXPECT_EQ(mat1(0, 2), 3);
  EXPECT_EQ(mat1(0, 3), 0);
  EXPECT_EQ(mat1(0, 4), 0);
  EXPECT_EQ(mat1(1, 0), 4);
  EXPECT_EQ(mat1(1, 1), 5);
  EXPECT_EQ(mat1(1, 2), 6);
  EXPECT_EQ(mat1(1, 3), 0);
  EXPECT_EQ(mat1(1, 4), 0);
  EXPECT_EQ(mat1(2, 0), 7);
  EXPECT_EQ(mat1(2, 1), 8);
  EXPECT_EQ(mat1(2, 2), 9);
  EXPECT_EQ(mat1(2, 3), 0);
  EXPECT_EQ(mat1(2, 4), 0);
}

TEST(Sets, SetCols2) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.SetCols(2);

  EXPECT_EQ(mat1.GetCols(), 2);

  EXPECT_EQ(mat1(0, 0), 1);
  EXPECT_EQ(mat1(0, 1), 2);
  EXPECT_EQ(mat1(1, 0), 4);
  EXPECT_EQ(mat1(1, 1), 5);
  EXPECT_EQ(mat1(2, 0), 7);
  EXPECT_EQ(mat1(2, 1), 8);
}

TEST(Sets, SetCols3) {
  S21Matrix mat1(3, 3);
  initMat(mat1);

  mat1.SetCols(0);

  EXPECT_EQ(mat1.GetRows(), 0);
  EXPECT_EQ(mat1.GetCols(), 0);
}
