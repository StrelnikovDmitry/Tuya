#include <stdio.h>

// gets x and y coordinates and moves cursor there.
// first argument is column number, second is row
void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

// clears everything at the right side of the cursor
void clear_the_rest() {
    printf("\033[K");
}

// clears the whole screen
void clear_all() {
    printf("\033[2J");
}

// show cursor
void show_cursor() {
    printf("\033[?25h");
}

// hide cursor
void hide_cursor() {
    printf("\033[?25l");
}

// turn alternative screen (no history) on
void turn_alt_screen_on() {
    printf("\033[?1049h");
}

// turn aalternative screen off
void turn_alt_screen_off() {
    printf("\033[?1049l");
}
