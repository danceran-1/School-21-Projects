#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

#define COLOR_PINK 13
#define COLOR_BRIGHT_YELLOW 12
void updateScoreBoard(int *pause, int *score, double *delay);
void saveHighScore(int high_score);
void startMenu(WINDOW *win1);
int start();
int loadHighScore();
int moveDown(Tetromino *tetromino, GameInfo_t *gameInfo);
void fixTetromino(Tetromino *tetromino, GameInfo_t *gameInfo);
void moveRight(Tetromino *tetromino, GameInfo_t *gameInfo);
void moveLeft(Tetromino *tetromino, GameInfo_t *gameInfo);
void moveDownInsta(Tetromino *tetromino, GameInfo_t *gameInfo);
Tetromino createTetromino(int type);
int proverka(Tetromino *tetromino, GameInfo_t *gameInfo);
int delete(GameInfo_t *gameInfo);
void onlyDraw(Tetromino tetromino, WINDOW *win);
void nextTetminator(int typik, WINDOW *winNext);
#endif
