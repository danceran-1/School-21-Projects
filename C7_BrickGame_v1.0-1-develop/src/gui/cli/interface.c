#include "interface.h"

#include <stdlib.h>
#include <time.h>

#include "../../brick_game/tetris/tetris.h"
void startMenu(WINDOW *win1) {
  box(win1, 0, 0);
  mvwprintw(win1, 1, 1, "TETRIS MENU");
  mvwprintw(win1, 2, 1, "Start game - 'b'");
  mvwprintw(win1, 3, 1, "Close game - 'q'");
  mvwprintw(win1, 4, 1, "Pause game - 'p'");
  mvwprintw(win1, 5, 1, "Rotate - 'w'");
  mvwprintw(win1, 6, 1, "Move left - 'a'");
  mvwprintw(win1, 7, 1, "Move right - 'd'");
  mvwprintw(win1, 8, 1, "Move down - 's'");

  refresh();
  wrefresh(win1);
}
void initColors() {
  start_color();

  init_color(COLOR_PINK, 1000, 686, 843);
  init_color(COLOR_BRIGHT_YELLOW, 900, 900, 0);
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(3, COLOR_BLUE, COLOR_BLUE);
  init_pair(4, COLOR_GREEN, COLOR_GREEN);
  init_pair(5, COLOR_PINK, COLOR_PINK);
  init_pair(6, COLOR_BRIGHT_YELLOW, COLOR_BRIGHT_YELLOW);
  init_color(COLOR_YELLOW, 1000, 500, 0);
  init_pair(7, COLOR_YELLOW, COLOR_YELLOW);
}
int loadHighScore() {
  FILE *file = fopen("high_score.txt", "r");
  int high_score = 0;

  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}

void saveHighScore(int high_score) {
  FILE *file = fopen("high_score.txt", "w");

  if (file) {
    fprintf(file, "%d", high_score);
    fclose(file);
  }
}
void updateScoreBoard(int *pause, int *score, double *delay) {
  int lvl = *score / 600;
  int high_score = loadHighScore();
  if (*score > high_score) {
    high_score = *score;
    saveHighScore(high_score);
  }

  if (lvl > 10) lvl = 10;

  double speed = 0.5 - (lvl * 0.05);
  if (speed < 0.1) speed = 0.1;

  *delay = speed;

  WINDOW *win3 = newwin(10, 20, 5, 28);
  werase(win3);
  box(win3, 0, 0);

  mvwprintw(win3, 1, 1, "Level: %d", lvl);
  mvwprintw(win3, 2, 1, "Speed: %0.2f", speed);
  mvwprintw(win3, 3, 1, "Score: %d", *score);
  mvwprintw(win3, 4, 1, "High Score %d", high_score);
  mvwprintw(win3, 5, 1, "Pause: %d ", *pause);

  wrefresh(win3);
}

void nextTetminator(int typik, WINDOW *winNext) {
  Tetromino t = createTetromino(typik);
  werase(winNext);

  box(winNext, 0, 0);
  onlyDraw(t, winNext);
  wrefresh(winNext);
}
void onlyDraw(Tetromino tetromino, WINDOW *win) {
  const int widthScale = 2;
  wattron(win, COLOR_PAIR(tetromino.type + 1));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino.shape[i][j] > 0) {
        mvwaddch(win, i + 1, j * widthScale + 1, ' ');
        mvwaddch(win, i + 1, j * widthScale + 2, ' ');
      }
    }
  }
  wattroff(win, COLOR_PAIR(tetromino.type + 1));
  wrefresh(win);
}

void gameFieldWithFigure(int cols, int rows, int **field, WINDOW *win,
                         Tetromino tetromino) {
  const int widthScale = 2;
  box(win, 0, 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (field[i][j] > 0) {
        wattron(win, COLOR_PAIR(field[i][j]));
        mvwaddch(win, i + 1, (j * widthScale) + 1, ' ');
        mvwaddch(win, i + 1, (j * widthScale) + 2, ' ');
        wattroff(win, COLOR_PAIR(field[i][j]));
      } else {
        mvwaddch(win, i + 1, (j * widthScale) + 1, ' ');
        mvwaddch(win, i + 1, (j * widthScale) + 2, ' ');
      }
    }
  }

  wattron(win, COLOR_PAIR(tetromino.type + 1));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino.shape[i][j] > 0) {
        mvwaddch(win, tetromino.y + i + 1, (tetromino.x + j) * widthScale + 1,
                 ' ');
        mvwaddch(win, tetromino.y + i + 1, (tetromino.x + j) * widthScale + 2,
                 ' ');
      }
    }
  }
  wattroff(win, COLOR_PAIR(tetromino.type + 1));
  wrefresh(win);
}
#ifndef TESTING

int main() {
  int vibor = 0;
  int pause = 0;
  int score = 0;
  clock_t last_time = clock();

  double fall_speed = 0.5;
  Tetromino currentTetromino;

  int start = 0;
  int cols = 10;
  int rows = 20;

  GameInfo_t gameInfo;
  gameInfo.cols = cols;
  gameInfo.rows = rows;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  initColors();
  nodelay(stdscr, TRUE);

  WINDOW *fieldWin = newwin(rows + 2, cols * 2 + 2, 5, 5);
  box(fieldWin, 0, 0);
  wrefresh(fieldWin);

  gameInfo.field = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    gameInfo.field[i] = calloc(cols, sizeof(int));
  }

  WINDOW *menuWin = newwin(10, 25, 3, 10);
  startMenu(menuWin);

  WINDOW *winNext = newwin(10, 20, 15, 28);
  box(winNext, 0, 0);

  int type = rand() % 7;
  int ch;
  ch = getch();
  if (ch == '\033') {
    if (ch == '[') {
      ch = getch();
      switch (ch) {
        case 'B':
          vibor = 1;
          break;
        case 'C':
          vibor = 2;
          break;
        case 'D':
          vibor = 3;
          break;
      }
    }
  }
  while ((ch = getch()) != 'q') {
    if (ch == 'b') {
      curs_set(0);
      start = 1;
      werase(menuWin);
      wrefresh(menuWin);
      delwin(menuWin);

      clear();
      refresh();

      updateScoreBoard(&pause, &score, &fall_speed);

      currentTetromino = createTetromino(rand() % 7);
      nextTetminator(type, winNext);

      break;
    }
  }

  while (start) {
    werase(fieldWin);

    gameFieldWithFigure(cols, rows, gameInfo.field, fieldWin, currentTetromino);

    clock_t current_time = clock();

    double delta_time = (double)(current_time - last_time) / CLOCKS_PER_SEC;
    score += delete (&gameInfo);
    updateScoreBoard(&pause, &score, &fall_speed);

    if (proverka(&currentTetromino, &gameInfo) == 1) {
      werase(fieldWin);
      delwin(fieldWin);
      endwin();
      printf("Игра окончена! Вы достигли верхней границы.\n");
      exit(0);
    }
    if (delta_time >= fall_speed) {
      if (moveDown(&currentTetromino, &gameInfo) == 0) {
        fixTetromino(&currentTetromino, &gameInfo);

        currentTetromino = createTetromino(type);
        type = rand() % 7;

        nextTetminator(type, winNext);
      }
      last_time = current_time;
    }

    ch = getch();
    if (ch == 'q') {
      start = 0;
    } else if (ch == 'd') {
      moveRight(&currentTetromino, &gameInfo);
    } else if (ch == 'a') {
      moveLeft(&currentTetromino, &gameInfo);
    } else if (ch == 's') {
      moveDownInsta(&currentTetromino, &gameInfo);
    } else if (ch == 'w' || ch == ' ') {
      rotate(&currentTetromino, &gameInfo);
    } else if (ch == 'p') {
      pause = 1;
      updateScoreBoard(&pause, &score, &fall_speed);
      nodelay(stdscr, FALSE);
      refresh();
      while (1) {
        ch = getch();
        if (ch == 'p') {
          pause = 0;
          updateScoreBoard(&pause, &score, &fall_speed);

          break;
        }
      }
      nodelay(stdscr, TRUE);
      werase(fieldWin);
      box(fieldWin, 0, 0);
      wrefresh(fieldWin);
    } else if (vibor == 1) {
      moveDownInsta(&currentTetromino, &gameInfo);
    } else if (vibor == 2) {
      moveRight(&currentTetromino, &gameInfo);
    } else if (vibor == 3) {
      moveLeft(&currentTetromino, &gameInfo);
    }
  }

  delwin(fieldWin);
  for (int i = 0; i < rows; i++) {
    free(gameInfo.field[i]);
  }
  free(gameInfo.field);
  endwin();
  return 0;
}
#endif
