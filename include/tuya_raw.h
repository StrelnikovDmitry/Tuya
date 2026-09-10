/* This file is an open api header
 * Functions provided are experimental and subjected to change
 * I do not guarantee future support of these functions */

#ifndef RAW
#define RAW

// ansi codes
void move_cursor(int x, int y);

void clear_the_rest();
void clear_all();

void show_cursor();
void hide_cursor();

void turn_alt_screen_on();
void turn_alt_screen_off();

#endif
