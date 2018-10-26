#include "term.h"

#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>

int w, h;

struct termios backup, noncanon;

inline void term_save_pos(void) {
  printf("\e[s");
}

inline void term_restore_pos(void) {
  printf("\e[u");
}

inline void term_cursor_up(int n) {
  printf("\e[%iA", n);
}

inline void term_cursor_down(int n) {
  printf("\e[%iB", n);
}

inline void term_cursor_right(int n) {
  printf("\e[%iC", n);
}

inline void term_cursor_left(int n) {
  printf("\e[%iD", n);
}

inline void term_set_color(termcolor_t fg, termcolor_t bg) {
  printf("\e[%i;%im", (int)(fg) + 30, (int)(bg) + 40);
}

inline void term_reset_color(void) {
  printf("\e[m");
}

void term_init(int width, int height) {
  w = width;
  h = height;
  
  // switch stdin to non canonical mode
  tcgetattr(STDIN_FILENO, &backup);
  tcgetattr(STDIN_FILENO, &noncanon);

  noncanon.c_lflag &= ~(ICANON|ECHO);
  noncanon.c_cc[VMIN] = 0;
  noncanon.c_cc[VTIME] = 0;
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &noncanon);

  for (int i = 0; i < (h - 1); i++) {
    printf("\n");
  }

  setvbuf(stdout, NULL, _IONBF, 0);

  term_cursor_up(h - 1);
  term_save_pos();
}

void term_kill(void) {
  term_restore_pos();
  term_cursor_down(h - 1);

  // switch stdin back to canonical mode
  tcsetattr(STDIN_FILENO, TCSANOW, &backup);

  printf("\n");
}

void term_goto(int x, int y) {
  term_restore_pos();
  term_save_pos();
  if (y > 0) { term_cursor_down(y); }
  if (x > 0) { term_cursor_right(x); }
}

void term_putc(char c, termcolor_t fg, termcolor_t bg) {
  term_set_color(fg, bg);
  printf("%c\b", c);
  term_reset_color();
}

int term_getkey(termkey_t *key) {
  /* stfu i know this method is shit and idc */
  char c = 0;

  c = fgetc(stdin);

  if (c == 'q') {
    *key = TERMKEY_Q;
    return 1;
  } else if (c == '\e') {
    c = fgetc(stdin);

    if (c == '[') {
      c = fgetc(stdin);

      if (c == 'A') {
        *key = TERMKEY_ARROW_UP;
        return 1;
      } else if (c == 'B') {
        *key = TERMKEY_ARROW_DOWN;
        return 1;
      } else if (c == 'C') {
        *key = TERMKEY_ARROW_RIGHT;
        return 1;
      } else if (c == 'D') {
        *key = TERMKEY_ARROW_LEFT;
        return 1;
      }
    }
  }

  return 0;
}
