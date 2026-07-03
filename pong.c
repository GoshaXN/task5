// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int ballx;
int bally;
int balldx;
int balldy;

int p1score;
int p1platform;

int p2score;
int p2platform;

void ShowField(int platform1, int platform2, int ballx,
               int bally);  // отображение поля
void BallMove();            // изменение координат
void Scored();

int main(void) {
  int ps = 0;
  int move = 0;
  ballx = 75;
  bally = 13;
  balldx = 1;
  balldy = 1;

  p1score = 0;
  p1platform = 13;

  p2score = 0;
  p2platform = 13;
  char input;

  while (1) {
    printf("\033[2J\033[H");  // очистка консоли и перемещение вверх
    ShowField(p1platform, p2platform, ballx, bally);
    printf("score: Player 1-%d, Player 2-%d\n", p1score, p2score);
    printf("Player% d >>>\n", ps + 1);

    do {
      scanf("%c", &input);
    } while (input == '\n' || input == '\t');

    scanf("%*[^\n]");  // очистка буфера. удаление всего лишнего до конца строки

    scanf("%*c");

    BallMove();  // p1platform, p2platform, ballx, bally, balldx, balldy

    // обработка движения обоих ракеток
    if (ps == 0) {
      if (input == 'a' && p1platform >= 3) {
        p1platform--;
        move = 1;
      }
      if (input == 'z' && p1platform <= 22) {
        p1platform++;
        move = 1;
      }
      if (input == ' ') {
        move = 1;
      }
    } else if (ps == 1) {
      if (input == 'k' && p2platform >= 3) {
        p2platform--;
        move = 1;
      }
      if (input == 'm' && p2platform <= 22) {
        p2platform++;
        move = 1;
      }
      if (input == ' ') {
        move = 1;
      }
    }

    if (move) {
      printf("\033[2J\033[H");  // очистка консоли и перемещение вверх
      move = 0;
    }
    ps = (ps + 1) % 2;
    Scored();
    if (p2score == 21 || p1score == 21) {
      if (p2score == 21) {
        printf("Player 2 WIN");
      } else {
        printf("Player 1 WIN");
      }
      return 0;
    }
  }
  return 0;
}

void ShowField(int platform1, int platform2, int ballx, int bally) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 80; j++) {
      // поле
      if ((i == 0 || i == 24) && !((abs(i - platform1) <= 1) && j == 3) &&
          !((abs(i - platform2) <= 1) && j == 76) &&
          !(j == ballx && i == bally)) {
        printf("_");
      } else if (j == 0 || j == 79) {
        printf("|");
        // длинное условие на отсутствие принта чтобы не сдвинуло край платформы
      } else if (((abs(i - platform1) <= 1) && j == 3) ||
                 ((abs(i - platform2) <= 1) && j == 76) ||
                 (j == ballx && i == bally)) {
        ;
      } else {
        printf(" ");
      }

      if ((abs(i - platform1) <= 1) && j == 3) {
        printf("{");
      }

      // центальная плашка
      if (j == 40) {
        if (ballx == 40 && bally == i) {  // вместо |o вывести только шар
          printf(" ");
        } else {
          if (i > 0 && i < 24) {
            printf(":");
          }
        }
      }
      // шар
      if (j == ballx && i == bally) {
        printf("o");
      }

      // ракетки

      if ((abs(i - platform2) <= 1) && j == 76) {
        printf("}");
      }
    }
    printf("\n");
  }
}

void BallMove() {
  // отскок от вертикальных границ
  if (bally == 1 || bally == 24) {
    balldy = -1 * balldy;
  }

  // отскок от платформы
  if (((abs(bally - p1platform) <= 1) && (balldx == -1) && (ballx == 3) &&
       ()) ||
      ((abs(bally - p2platform) <= 1) && (balldx == 1) && (ballx == 76))) {
    balldx = -1 * balldx;
  }

  ballx += balldx;
  bally += balldy;
}

void Scored() {
  if (ballx == 1 || ballx == 78) {
    if (ballx == 1) {
      p2score++;
    }
    if (ballx == 78) {
      p1score++;
    }
    ballx = 40;
    bally = 13;
    balldy = -1 * balldy;
    if ((p1score + p2score) % 2 == 0) {
      balldx = -1 * balldx;
    }
  }
}