#include "tetris.h"

#include "../../gui/cli/interface.h"

Tetromino createTetromino(int type) {
  Tetromino t;
  t.type = type;
  t.x = 0;
  t.y = 0;

  if (type == 0) {
    int square[4][4] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  if (type == 1) {
    int square[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  if (type == 2) {
    int square[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  if (type == 3) {
    int square[4][4] = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  if (type == 4) {
    int square[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  if (type == 5) {
    int square[4][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  if (type == 6) {
    int square[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    memcpy(t.shape, square, sizeof(square));
  }
  return t;
}
int moveDown(Tetromino *tetromino, GameInfo_t *gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->shape[i][j]) {
        int newY = tetromino->y + i + 1;
        int newX = tetromino->x + j;

        if (newY >= gameInfo->rows || gameInfo->field[newY][newX] > 0) {
          return 0;
        }
      }
    }
  }

  tetromino->y++;
  return 1;
}

int proverka(Tetromino *t, GameInfo_t *gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (t->shape[i][j] != 0) {
        if (t->y + i >= gameInfo->rows || t->x + j < 0 ||
            t->x + j >= gameInfo->cols ||
            gameInfo->field[t->y + i][t->x + j] != 0) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void fixTetromino(Tetromino *tetromino, GameInfo_t *gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->shape[i][j]) {
        gameInfo->field[tetromino->y + i][tetromino->x + j] =
            tetromino->type + 1;
      }
    }
  }
}
int delete(GameInfo_t *gameInfo) {
  int another = 0;
  int score = 0;

  for (int i = 0; i < gameInfo->rows; i++) {
    int isRowFull = 1;

    for (int j = 0; j < gameInfo->cols; j++) {
      if (gameInfo->field[i][j] == 0) {
        isRowFull = 0;
        break;
      }
    }

    if (isRowFull) {
      another++;
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < gameInfo->cols; j++) {
          gameInfo->field[k][j] = gameInfo->field[k - 1][j];
        }
      }

      for (int j = 0; j < gameInfo->cols; j++) {
        gameInfo->field[0][j] = 0;
      }

      i--;
    }
  }
  switch (another) {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 700;
      break;
    case 4:
      score += 1500;
      break;
    default:
      break;
  }
  return score;
}
void rotate(Tetromino *tetromino, GameInfo_t *gameInfo) {
  if (tetromino->type == 1) {
    return;
  }
  int temp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp[j][4 - 1 - i] = tetromino->shape[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp[i][j]) {
        int newX = tetromino->x + j;
        int newY = tetromino->y + i;

        if (newX < 0 || newX >= gameInfo->cols || newY >= gameInfo->rows) {
          return;
        }

        if (gameInfo->field[newY][newX] > 0) {
          return;
        }
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetromino->shape[i][j] = temp[i][j];
    }
  }
}

void moveRight(Tetromino *tetromino, GameInfo_t *gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->shape[i][j]) {
        int newX = tetromino->x + j + 1;
        if (newX >= gameInfo->cols ||
            gameInfo->field[tetromino->y + i][newX] != 0) {
          tetromino->x--;
        }
      }
    }
  }
  tetromino->x++;
}
void moveLeft(Tetromino *tetromino, GameInfo_t *gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->shape[i][j]) {
        int newX = tetromino->x + j - 1;
        if (newX < 0 || gameInfo->field[tetromino->y + i][newX] != 0) {
          tetromino->x++;
        }
      }
    }
  }
  tetromino->x--;
}
void moveDownInsta(Tetromino *tetromino, GameInfo_t *gameInfo) {
  int maxDrop = gameInfo->rows;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino->shape[i][j]) {
        int drop = 0;

        while (tetromino->y + i + drop + 1 < gameInfo->rows &&
               gameInfo->field[tetromino->y + i + drop + 1][tetromino->x + j] ==
                   0) {
          drop++;
        }

        if (drop < maxDrop) {
          maxDrop = drop;
        }
      }
    }
  }

  tetromino->y += maxDrop;
}
