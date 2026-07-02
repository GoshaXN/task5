#include <stdio.h>
#include <string.h>

int main(void) {
  char input_string[16];  // всегда b=1 символ под \0
  while (1) {
    printf("ping?\n");
    fgets(input_string, sizeof(input_string), stdin);
    // чтение клавиатуры в код
    if (strncmp(input_string, "ping", 4) == 0) {
      printf("pong\n");
    } else {
      printf("wrong\n");
    }
  }
  return 0;
}