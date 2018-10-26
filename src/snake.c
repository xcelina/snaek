#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "term.h"

void paint_pixel(int off_x, int off_y, int x, int y, termcolor_t color) {
  term_goto(off_x + 2 * x, off_y + y);
  term_putc(' ', TERMCOLOR_WHITE, color);
  term_goto(off_x + 2 * x + 1, off_y + y);
  term_putc(' ', TERMCOLOR_WHITE, color);
}

int main (int argc, char **argv) {
  int field_w = 40;
  int field_h = 30;

  int margin_l = 0;
  int margin_r = 0;
  int margin_t = 0;
  int margin_b = 0;

  struct timespec sleeptime = {
      0,      /* seconds */
      100000000  /* nanoseconds */
    };

  int running = 1;

  term_init(
      margin_l + 2 * field_w + margin_r, 
      margin_t + field_h + margin_b
    );

  int head_x = 0, head_y = 0;
  int vel_x = 1, vel_y = 0;
  int treat_x = 0, treat_y = 0;

  // before the game even starts, make sure the treat is not under the snakes head
  while (head_x == treat_x && head_y == treat_y) {
    treat_x = rand() % field_w;
    treat_y = rand() % field_h;
  }

  paint_pixel(margin_l, margin_t, treat_x, treat_y, TERMCOLOR_RED);

  // game loop
  while (running) {
    int old_vel_x = vel_x;
    int old_vel_y = vel_y;

    // check out all pressed keys
    termkey_t key;

    while (term_getkey(&key)) {      
      if (key == TERMKEY_Q) {
        running = 0;
      } else if (key == TERMKEY_ARROW_UP && old_vel_y != 1) {
        vel_x = 0;
        vel_y = -1;
      } else if (key == TERMKEY_ARROW_DOWN && old_vel_y != -1) {
        vel_x = 0;
        vel_y = 1;
      } else if (key == TERMKEY_ARROW_LEFT && old_vel_x != 1) {
        vel_x = -1;
        vel_y = 0;
      } else if (key == TERMKEY_ARROW_RIGHT && old_vel_x != -1) {
        vel_x = 1;
        vel_y = 0;
      }
    }

    head_x = (field_w + head_x + vel_x) % field_w;
    head_y = (field_h + head_y + vel_y) % field_h;

    if (head_x == treat_x && head_y == treat_y) {
      treat_x = rand() % field_w;
      treat_y = rand() % field_h;

      paint_pixel(margin_l, margin_t, treat_x, treat_y, TERMCOLOR_RED);
    }

    paint_pixel(margin_l, margin_t, head_x, head_y, TERMCOLOR_GREEN);

    nanosleep(&sleeptime, NULL);
  }

  term_kill();

  return 0;
}
