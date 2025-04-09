#ifndef TETRIS_H
#define TETRIS_H
#define _POSIX_C_SOURCE 199309L

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH_MAP 10
#define HEIGHT_MAP 20
#define HIGH_SCORE_FILE "highscore.txt"

#define CLOCK_MONOTONIC 1

typedef struct {
  int shape[4][4];
  int x, y;
  int type;
} Tetromino;

typedef struct {
  int **field;
  int rows;
  int cols;
} GameInfo_t;
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

Tetromino createTetromino(int type);
void updateScoreBoard(int *pause, int *score, double *delay);
void saveHighScore(int high_score);
int loadHighScore();
void rotate(Tetromino *tetromino, GameInfo_t *gameInfo);
int moveDown(Tetromino *tetromino, GameInfo_t *gameInfo);
int proverka(Tetromino *tetromino, GameInfo_t *gameInfo);
void fixTetromino(Tetromino *tetromino, GameInfo_t *gameInfo);
int delete(GameInfo_t *gameInfo);
void moveRight(Tetromino *tetromino, GameInfo_t *gameInfo);
void moveLeft(Tetromino *tetromino, GameInfo_t *gameInfo);
void moveDownInsta(Tetromino *tetromino, GameInfo_t *gameInfo);
void rotate(Tetromino *tetromino, GameInfo_t *gameInfo);
#endif  // TETRIS_H
