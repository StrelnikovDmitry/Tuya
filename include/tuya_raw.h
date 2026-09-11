/* This file is an open api header
 * Functions provided are experimental and subjected to change
 * I do not guarantee future support of these functions */

#ifndef RAW
#define RAW

#include "slice_structure.h"

// ansi codes
void move_cursor(int x, int y);

void clear_the_rest();
void clear_all();

void show_cursor();
void hide_cursor();

void turn_alt_screen_on();
void turn_alt_screen_off();

// no-diff update
void FORCE_update_slice(Slice *sl, char *content);

// static print (benig tested)
void print_static (int x1, int y1, int x2, int y2, char *content);

#endif
