#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define ANSI_CURSOR_UP "\e[1A"
#define ANSI_CURSOR_DOWN "\e[1B"
#define ANSI_CURSOR_LEFT "\e[1D"
#define ANSI_CURSOR_RIGHT "\e[1C"
#define ANSI_SAVE_CURSOR "\e[s"
#define ANSI_RESTORE_CURSOR "\e[u"
#define ANSI_CLEAR_CURSOR_TO_END "\e[0K"

void print_rel(int rel_x, int rel_y, const char *string) {
  printf(ANSI_SAVE_CURSOR);
  
  for (int i = 0; i < rel_x; i++) {
    printf(ANSI_CURSOR_RIGHT);
  }

  for (int i = 0; i < rel_y; i++) {
    printf(ANSI_CURSOR_DOWN);
  }

  printf("%s" ANSI_RESTORE_CURSOR, string);
}

void clear() {
  printf(ANSI_CLEAR_CURSOR_TO_END);
}

int main (int argc, char **argv) {
  int width = 20;
  int height = 15;

  struct timespec sleeptime = {
      0,      /* seconds */
      100000  /* nanoseconds */
    };

  // switch stdin to non canonical mode
  struct termios backup, noncanon;
  tcgetattr(STDIN_FILENO, &backup);
  tcgetattr(STDIN_FILENO, &noncanon);

  noncanon.c_lflag &= ~(ICANON|ECHO);
  noncanon.c_cc[VMIN] = 0;
  noncanon.c_cc[VTIME] = 0;
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &noncanon);

  int running = 1;

  for (int i = 0; i < (height - 1); i++) {
    printf("\n");
  }

  setvbuf(stdout, NULL, _IONBF, 0);

  for (int i = 0; i < (height - 1); i++) {
    printf(ANSI_CURSOR_UP);
  }

  // TEEEEEST
  print_rel(5, 10, "Hello World!");

  // game loop
  while (running) {
    // check out all pressed keys
    char c;

    while ((c = fgetc(stdin)) != EOF) {      
      if (c == 'q') {
        running = 0;
      } else {
        fputc(c, stdout);
      }
    }

    nanosleep(&sleeptime, NULL);
  }

  // switch stdin back to canonical mode
  tcsetattr(STDIN_FILENO, TCSANOW, &backup);

  return 0;
}
