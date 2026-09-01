#include <stdio.h>

// gets x and y coordinates and moves cursor there.
// first argument is column number, second is row
void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//clears everything at the right side of the cursor
void clear_the_rest() {
    printf("\033[K");
}

void show_cursor() {
    printf("\033[?25h");
}

void hide_cursor() {
    printf("\033[?25l");
}

void turn_alt_screen_on() {
    printf("\033[?1049h");
}

void turn_alt_screen_off() {
    printf("\033[?1049l");
}
