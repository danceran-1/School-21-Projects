#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define STR 25
#define COL 80

void update_matrix(int matr1[STR][COL], int matr2[STR][COL]);
void output(int matr[STR][COL]);

int main() {
    int matr1[STR][COL];
    int matr2[STR][COL];
    int matr3[STR][COL];

    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            scanf("%d", &matr1[i][j]);
        }
    }

    for (int stop = 0; stop <= 5; stop--) {
        int chet = 0;
        int chet_1 = 0;
        printf("\033[2J\033[H");
        update_matrix(matr1, matr2);
        output(matr1);
        sleep(1);
        for (int i = 0; i < STR; i++) {
            for (int j = 0; j < COL; j++) {
                matr3[i][j] = 0;
                if (matr3[i][j] == matr1[i][j]) {
                    chet_1 = chet_1 + 1;
                    if (chet_1 >= (STR * COL)) {
                        printf("Программа зациклилась");
                        return 0;
                    }
                    matr1[i][j] = matr3[i][j];
                }

                if (matr1[i][j] == matr2[i][j]) {
                    chet = chet + 1;
                    if (chet == 2000) {
                        printf("Програма стала статичной!!");
                        return 0;
                    }
                }
                matr1[i][j] = matr2[i][j];
            }
        }
    }

    return 0;
}
void output(int matr[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }
}

int count_neighbors(int j, int i, int matr1[STR][COL]) {
    int count = 0;
    if (matr1[i - 1][j] == 1) {
        count += 1;
    }
    if (matr1[i][j - 1] == 1) {
        count += 1;
    }
    if (matr1[i + 1][j] == 1) {
        count += 1;
    }
    if (matr1[i][j + 1] == 1) {
        count += 1;
    }
    if (matr1[i - 1][j - 1] == 1) {
        count += 1;
    }
    if (matr1[i - 1][j + 1] == 1) {
        count += 1;
    }

    if (matr1[i + 1][j - 1] == 1) {
        count += 1;
    }
    if (matr1[i + 1][j + 1] == 1) {
        count += 1;
    }
    if (count == 3) {
        return -1;
    }
    return 0;
}

int count_neighbors_1(int i, int j, int matr1[STR][COL]) {
    int count = 0;
    if (matr1[i - 1][j] == 1) {
        count += 1;
    }
    if (matr1[i][j - 1] == 1) {
        count += 1;
    }
    if (matr1[i + 1][j] == 1) {
        count += 1;
    }
    if (matr1[i][j + 1] == 1) {
        count += 1;
    }
    if (matr1[i - 1][j - 1] == 1) {
        count += 1;
    }
    if (matr1[i - 1][j + 1] == 1) {
        count += 1;
    }
    if (matr1[i + 1][j - 1] == 1) {
        count += 1;
    }
    if (matr1[i + 1][j + 1] == 1) {
        count += 1;
    }
    if (count > 3) {
        return 1;
    }
    if (count < 2) {
        return 1;
    }
    return 0;
}

void update_matrix(int matr1[STR][COL], int matr2[STR][COL]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < COL; j++) {
            if (matr1[i][j] == 0) {
                int n = count_neighbors(j, i, matr1);
                if (n == -1) {
                    matr2[i][j] = 1;
                } else {
                    matr2[i][j] = 0;
                }
            } else {
                int n = count_neighbors_1(i, j, matr1);
                if (n == 1) {
                    matr2[i][j] = 0;
                } else {
                    matr2[i][j] = 1;
                }
            }
        }
    }
}
