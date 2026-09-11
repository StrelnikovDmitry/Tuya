#include "../../terminal/ansi.h"
#include <stdio.h>

// Prints static content within the bounds given.
// The output is clipped to the frame and does not affect the rest of the terminal.
void print_static (int x1, int y1, int x2, int y2, char *content) {
    int width = x2 - (x1 - 1);
    int height = y2 - (y1 - 1);

    // y coordinate of the cursor, needed for moving cursor when the line ends
    int y = y1;

    move_cursor(x1, y1);

    int i = 0;
    while (content[i] != '\0') {
        if (i && !(i % width)) {
            y++;
            move_cursor(x1, y);
        }
        printf("%c", content[i]);
        i++;
    }
    fflush(stdout);
}
