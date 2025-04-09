#include "test.h"

TEST(Constructors, DefaultConstructor) {
  S21Matrix mat1(0, -1);

  EXPECT_EQ(mat1.GetCols(), 0);
  EXPECT_EQ(mat1.GetRows(), 0);
}

TEST(Constructors, CopyConstructor) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 1;
  mat1(0, 1) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  S21Matrix mat2 = mat1;

  EXPECT_EQ(mat2(0, 0), 1);
  EXPECT_EQ(mat2(0, 1), 2);
  EXPECT_EQ(mat2(1, 0), 3);
  EXPECT_EQ(mat2(1, 1), 4);
}

TEST(Constructors, MoveConstructor) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 1;
  mat1(0, 1) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  S21Matrix mat2 = std::move(mat1);

  EXPECT_EQ(mat2(0, 0), 1);
  EXPECT_EQ(mat2(0, 1), 2);
  EXPECT_EQ(mat2(1, 0), 3);
  EXPECT_EQ(mat2(1, 1), 4);
}
