#ifndef __TERM_H
#define __TERM_H

typedef enum {
    TERMKEY_ARROW_UP,
    TERMKEY_ARROW_DOWN,
    TERMKEY_ARROW_LEFT,
    TERMKEY_ARROW_RIGHT,
    TERMKEY_Q
  } termkey_t;

typedef enum {
    TERMCOLOR_BLACK = 0,
    TERMCOLOR_RED = 1,
    TERMCOLOR_GREEN = 2,
    TERMCOLOR_YELLOW = 3,
    TERMCOLOR_BLUE = 4,
    TERMCOLOR_MAGENTA = 5,
    TERMCOLOR_CYAN = 6,
    TERMCOLOR_WHITE = 7,
    TERMCOLOR_BBLACK = 60,
    TERMCOLOR_BRED = 61,
    TERMCOLOR_BGREEN = 62,
    TERMCOLOR_BYELLOW = 63,
    TERMCOLOR_BBLUE = 64,
    TERMCOLOR_BMAGENTA = 65,
    TERMCOLOR_BCYAN = 66,
    TERMCOLOR_BWHITE = 67,
  } termcolor_t;
  
void term_init(int, int);
void term_kill(void);

void term_goto(int, int);
void term_putc(char, termcolor_t, termcolor_t);

int term_getkey(termkey_t *key);

#endif
