#include <stdio.h>

// gets x and y coordinates and moves cursor there.
// first argument is column number, second is row
void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}
