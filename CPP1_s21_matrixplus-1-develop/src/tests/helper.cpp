#include "test.h"

void initMat(S21Matrix &mat) {
  double num = 0;
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = ++num;
    }
  }
}
