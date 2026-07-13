// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI

#include <ncurses.h>

void ShowField(int platform1, int platform2, int ball_x,
               int ball_y);  // отображение поля
int Absfunc(int number);

int main(void) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  refresh();
  int ball_x;
  int ball_y;
  int ball_dx;
  int ball_dy;

  int p1_score;
  int p1_platform;

  int p2_score;
  int p2_platform;

  ball_x = 4;
  ball_y = 12;
  ball_dx = -1;
  ball_dy = 1;

  p1_score = 0;
  p1_platform = 13;

  p2_score = 0;
  p2_platform = 13;

  while (p2_score < 21 && p1_score < 21) {
    char input;
    clear();
    printw("Player1 score: %d, Player2 score: %d\n", p1_score, p2_score);
    ShowField(p1_platform, p2_platform, ball_x, ball_y);
    refresh();
    input = getch();
    if (input == 'q') {
      p1_score = 99;
      p2_score = 99;

    } else {
      // отскок от вертикальных границ
      if (ball_y == 1 || ball_y == 24) {
        ball_dy = -1 * ball_dy;
      }

      // отскок от платформы
      if (((Absfunc(ball_y - p1_platform) <= 1) && (ball_dx == -1) &&
           (ball_x == 3)) ||
          ((Absfunc(ball_y - p2_platform) <= 1) && (ball_dx == 1) &&
           (ball_x == 76))) {
        ball_dx = -1 * ball_dx;
      }

      ball_x += ball_dx;
      ball_y += ball_dy;

      // обработка движения обоих ракеток
      if (input == 'a' && p1_platform >= 3) {
        p1_platform--;
      }
      if (input == 'z' && p1_platform <= 22) {
        p1_platform++;
      }

      if (input == 'k' && p2_platform >= 3) {
        p2_platform--;
      }
      if (input == 'm' && p2_platform <= 22) {
        p2_platform++;
      }

      if (ball_x <= 1 || ball_x >= 78) {
        if (ball_x <= 1) {
          p2_score++;
        }
        if (ball_x >= 78) {
          p1_score++;
        }
        ball_x = 40;
        ball_y = 13;
        ball_dy = -1 * ball_dy;
        if ((p1_score + p2_score) % 2 == 0) {
          ball_dx = -1 * ball_dx;
        }
      }
      flushinp();
      napms(100);
    }
  }
  if (p2_score == 99 && p1_score == 99) {
    printw("End game");
  } else if (p2_score == 21) {
    printw("Player 2 WIN");
  } else {
    printw("Player 1 WIN");
  }
  nodelay(stdscr, FALSE);
  getch();
  endwin();
  return 0;
}

void ShowField(int platform1, int platform2, int ball_x, int ball_y) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 80; j++) {
      // шар
      if (j == ball_x && i == ball_y) {
        printw("o");
      }

      // ракетки
      if ((Absfunc(i - platform1) <= 1) && j == 3) {
        printw("{");
      }
      if ((Absfunc(i - platform2) <= 1) && j == 76) {
        printw("}");
      }
      // поле
      if ((i == 0 || i == 24) && !((Absfunc(i - platform1) <= 1) && j == 3) &&
          !((Absfunc(i - platform2) <= 1) && j == 76) &&
          !(j == ball_x && i == ball_y)) {
        printw("_");
      } else if (j == 0 || j == 79) {
        printw("|");
        // длинное условие на отсутствие принта чтобы не сдвинуло край платформы
      } else if (((Absfunc(i - platform1) <= 1) && j == 3) ||
                 ((Absfunc(i - platform2) <= 1) && j == 76) ||
                 (j == ball_x && i == ball_y)) {
        ;
      } else {
        printw(" ");
      }

      // центальная плашка
      if (j == 40) {
        if (ball_x == 40 && ball_y == i) {  // вместо |o вывести только шар
          printw(" ");
        } else {
          if (i > 0 && i < 24) {
            printw(":");
          }
        }
      }
    }
    printw("\n");
  }
}

int Absfunc(int number) {
  if (number > 0) {
    return number;
  }
  return -1 * number;
}