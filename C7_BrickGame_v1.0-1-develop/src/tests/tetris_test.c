#include "../brick_game/tetris/tetris.h"

#include <check.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../gui/cli/interface.h"

START_TEST(test_create_tetromino) {
  Tetromino t = createTetromino(0);
  ck_assert_int_eq(t.shape[0][0], 1);
  ck_assert_int_eq(t.shape[0][1], 1);
}
END_TEST

START_TEST(test_move_tetromino_down) {
  Tetromino t = createTetromino(0);
  GameInfo_t gameInfo;
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));

  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)calloc(gameInfo.cols, sizeof(int));
  }

  int prev_row = t.y;
  moveDown(&t, &gameInfo);

  ck_assert_int_eq(t.y, prev_row + 1);
  free(gameInfo.field);
}
END_TEST

START_TEST(test_collision_detection) {
  Tetromino t = createTetromino(0);
  GameInfo_t gameInfo;
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));

  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)calloc(gameInfo.cols, sizeof(int));
  }

  for (int i = 0; i < gameInfo.cols; i++) {
    gameInfo.field[19][i] = 1;
  }

  t.y = 19;
  int result = proverka(&t, &gameInfo);
  ck_assert_int_eq(result, 1);
  free(gameInfo.field);
}

void initializeField(GameInfo_t *gameInfo, int rows, int cols) {
  gameInfo->rows = rows;
  gameInfo->cols = cols;
  gameInfo->field = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    gameInfo->field[i] = malloc(cols * sizeof(int));
    memset(gameInfo->field[i], 0, cols * sizeof(int));
  }
}

void freeField(GameInfo_t *gameInfo) {
  for (int i = 0; i < gameInfo->rows; i++) {
    free(gameInfo->field[i]);
  }
  free(gameInfo->field);
}

END_TEST
START_TEST(test_fixTetromino) {
  Tetromino t;
  t.type = 2;
  t.x = 3;
  t.y = 5;

  GameInfo_t gameInfo = {0};
  initializeField(&gameInfo, 20, 10);

  int square[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, square, sizeof(square));

  ck_assert_int_eq(gameInfo.field[5][3], 0);
  ck_assert_int_eq(gameInfo.field[5][4], 0);
  ck_assert_int_eq(gameInfo.field[6][3], 0);
  ck_assert_int_eq(gameInfo.field[6][4], 0);

  fixTetromino(&t, &gameInfo);

  ck_assert_int_eq(gameInfo.field[5][3], 3);
  ck_assert_int_eq(gameInfo.field[5][4], 3);
  ck_assert_int_eq(gameInfo.field[6][3], 3);
  ck_assert_int_eq(gameInfo.field[6][4], 3);

  ck_assert_int_eq(gameInfo.field[0][0], 0);
  ck_assert_int_eq(gameInfo.field[19][9], 0);

  freeField(&gameInfo);
}
END_TEST

START_TEST(test_createTetromino) {
  Tetromino t = createTetromino(0);
  ck_assert_int_eq(t.shape[0][0], 1);
  ck_assert_int_eq(t.shape[0][1], 1);
  ck_assert_int_eq(t.shape[0][2], 1);
  ck_assert_int_eq(t.shape[0][3], 1);
  ck_assert_int_eq(t.shape[1][0], 0);
  ck_assert_int_eq(t.shape[1][1], 0);
  ck_assert_int_eq(t.shape[1][2], 0);
  ck_assert_int_eq(t.shape[1][3], 0);

  t = createTetromino(1);
  ck_assert_int_eq(t.shape[0][0], 1);
  ck_assert_int_eq(t.shape[0][1], 1);
  ck_assert_int_eq(t.shape[1][0], 1);
  ck_assert_int_eq(t.shape[1][1], 1);
  ck_assert_int_eq(t.shape[2][0], 0);
  ck_assert_int_eq(t.shape[2][1], 0);
  ck_assert_int_eq(t.shape[3][0], 0);
  ck_assert_int_eq(t.shape[3][1], 0);

  t = createTetromino(2);
  ck_assert_int_eq(t.shape[0][1], 1);
  ck_assert_int_eq(t.shape[1][0], 1);
  ck_assert_int_eq(t.shape[1][1], 1);
  ck_assert_int_eq(t.shape[2][0], 0);

  t = createTetromino(3);
  ck_assert_int_eq(t.shape[0][1], 1);
  ck_assert_int_eq(t.shape[0][2], 1);
  ck_assert_int_eq(t.shape[1][0], 1);
  ck_assert_int_eq(t.shape[1][1], 1);

  t = createTetromino(4);
  ck_assert_int_eq(t.shape[0][0], 1);
  ck_assert_int_eq(t.shape[0][1], 1);
  ck_assert_int_eq(t.shape[1][1], 1);
  ck_assert_int_eq(t.shape[1][2], 1);

  t = createTetromino(5);
  ck_assert_int_eq(t.shape[0][0], 1);
  ck_assert_int_eq(t.shape[1][0], 1);
  ck_assert_int_eq(t.shape[1][1], 1);
  ck_assert_int_eq(t.shape[1][2], 1);

  t = createTetromino(6);
  ck_assert_int_eq(t.shape[0][2], 1);
  ck_assert_int_eq(t.shape[1][0], 1);
  ck_assert_int_eq(t.shape[1][1], 1);
  ck_assert_int_eq(t.shape[2][0], 0);
}
END_TEST
START_TEST(test_delete_no_full_rows) {
  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  int score = delete (&gameInfo);

  ck_assert_int_eq(score, 0);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_delete_one_full_row) {
  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  for (int j = 0; j < gameInfo.cols; j++) {
    gameInfo.field[0][j] = 1;
  }

  int score = delete (&gameInfo);

  ck_assert_int_eq(score, 100);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_delete_multiple_full_rows) {
  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 1;
    }
  }

  int score = delete (&gameInfo);

  ck_assert_int_eq(score, 700);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
START_TEST(test_delete_multiple_full_rows1) {
  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 1;
    }
  }

  int score = delete (&gameInfo);

  ck_assert_int_eq(score, 300);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
START_TEST(test_delete_multiple_full_rows2) {
  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 1;
    }
  }

  int score = delete (&gameInfo);

  ck_assert_int_eq(score, 1500);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
START_TEST(test_rotate_square_tetromino) {
  Tetromino t;
  t.type = 1;
  t.x = 5;
  t.y = 5;
  int square[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, square, sizeof(square));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  rotate(&t, &gameInfo);

  ck_assert_int_eq(t.shape[0][0], 1);
  ck_assert_int_eq(t.shape[0][1], 1);
  ck_assert_int_eq(t.shape[1][0], 1);
  ck_assert_int_eq(t.shape[1][1], 1);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_rotate_regular_tetromino) {
  Tetromino t;
  t.type = 2;
  t.x = 5;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  rotate(&t, &gameInfo);

  ck_assert_int_eq(t.shape[0][2], 1);
  ck_assert_int_eq(t.shape[1][1], 0);
  ck_assert_int_eq(t.shape[1][2], 1);
  ck_assert_int_eq(t.shape[2][2], 1);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_rotate_with_collision) {
  Tetromino t;
  t.type = 2;
  t.x = 5;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  gameInfo.field[6][6] = 1;

  rotate(&t, &gameInfo);

  ck_assert_int_eq(t.shape[0][2], 1);
  ck_assert_int_eq(t.shape[1][1], 0);
  ck_assert_int_eq(t.shape[1][2], 1);
  ck_assert_int_eq(t.shape[2][2], 1);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_rotate_out_of_bounds) {
  Tetromino t;
  t.type = 2;
  t.x = 8;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  rotate(&t, &gameInfo);

  ck_assert_int_eq(t.shape[0][2], 1);
  ck_assert_int_eq(t.shape[1][1], 1);
  ck_assert_int_eq(t.shape[1][2], 1);
  ck_assert_int_eq(t.shape[2][2], 0);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_delete_all_full_rows) {
  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 1;
    }
  }

  int score = delete (&gameInfo);

  ck_assert_int_eq(score, 0);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
START_TEST(test_moveRight_successful_move) {
  Tetromino t;
  t.type = 2;
  t.x = 5;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  moveRight(&t, &gameInfo);

  ck_assert_int_eq(t.x, 6);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_moveRight_edge_of_field) {
  Tetromino t;
  t.type = 2;
  t.x = 9;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  moveRight(&t, &gameInfo);

  ck_assert_int_eq(t.x, 7);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}

START_TEST(test_moveRight_empty_space) {
  Tetromino t;
  t.type = 2;
  t.x = 5;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  moveRight(&t, &gameInfo);

  ck_assert_int_eq(t.x, 6);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
START_TEST(test_moveLeft_normal_move) {
  Tetromino t;
  t.type = 2;
  t.x = 5;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  moveLeft(&t, &gameInfo);

  ck_assert_int_eq(t.x, 4);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
END_TEST
START_TEST(test_moveDownInsta_no_obstacle) {
  Tetromino t;
  t.type = 2;
  t.x = 5;
  t.y = 5;
  int lShape[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  memcpy(t.shape, lShape, sizeof(lShape));

  GameInfo_t gameInfo = {0};
  gameInfo.rows = 20;
  gameInfo.cols = 10;
  gameInfo.field = (int **)malloc(gameInfo.rows * sizeof(int *));
  for (int i = 0; i < gameInfo.rows; i++) {
    gameInfo.field[i] = (int *)malloc(gameInfo.cols * sizeof(int));
    for (int j = 0; j < gameInfo.cols; j++) {
      gameInfo.field[i][j] = 0;
    }
  }

  moveDownInsta(&t, &gameInfo);

  ck_assert_int_eq(t.y, 18);

  for (int i = 0; i < gameInfo.rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s = suite_create("Tetris Game Tests");

  TCase *tc_core = tcase_create("Core");
  tcase_set_timeout(tc_core, 7);
  tcase_add_test(tc_core, test_create_tetromino);
  tcase_add_test(tc_core, test_move_tetromino_down);
  tcase_add_test(tc_core, test_collision_detection);
  tcase_add_test(tc_core, test_fixTetromino);
  tcase_add_test(tc_core, test_createTetromino);
  tcase_add_test(tc_core, test_delete_no_full_rows);
  tcase_add_test(tc_core, test_delete_one_full_row);
  tcase_add_test(tc_core, test_delete_multiple_full_rows);
  tcase_add_test(tc_core, test_delete_all_full_rows);
  tcase_add_test(tc_core, test_delete_multiple_full_rows1);
  tcase_add_test(tc_core, test_delete_multiple_full_rows2);
  tcase_add_test(tc_core, test_rotate_square_tetromino);
  tcase_add_test(tc_core, test_rotate_regular_tetromino);
  tcase_add_test(tc_core, test_rotate_with_collision);
  tcase_add_test(tc_core, test_rotate_out_of_bounds);
  tcase_add_test(tc_core, test_moveRight_successful_move);

  tcase_add_test(tc_core, test_moveRight_edge_of_field);
  tcase_add_test(tc_core, test_moveRight_empty_space);
  tcase_add_test(tc_core, test_moveLeft_normal_move);
  tcase_add_test(tc_core, test_moveDownInsta_no_obstacle);
  suite_add_tcase(s, tc_core);

  return s;
}

#ifdef TESTING
int main(void) {
  int number_failed;
  Suite *s = tetris_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
#endif