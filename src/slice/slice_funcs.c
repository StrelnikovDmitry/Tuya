#include <stdio.h>
#include <stdlib.h>

#include "slice_structure.h"
#include "../cursor/cursor_funcs.h"

// get width
int get_width(Slice *sl) {
    return (sl -> x2 - (sl -> x1 - 1));
}

// get height
int get_height(Slice *sl) {
    return (sl -> y2 - (sl -> y1 - 1));
}

Slice create_slice(int x1, int y1, int x2, int y2) {
    Slice slice;

    // to store terminator size of the buffer should be bigger by one
	slice.size = (sizeof(char) * (x2 - (x1 - 1)) * (y2 - (y1 - 1))) + 1;
	slice.buffer = malloc(slice.size);
	slice.buffer[slice.size - 1] = '\0';

	slice.x1 = x1;
	slice.y1 = y1;
	slice.x2 = x2;
	slice.y2 = y2;

	return slice;
}

// deleting slice buffer andd erasing thee insides
//
// THIS FUNCTIONS DOES NOT WORK WHEN RESIZING TERMINAL
// instead use free(sl.buffer) and clear_all for SIGWINCH handling.
void delete_slice(Slice *sl) {
    int width = get_width(sl);

    for (int i = 0; i < get_height(sl); i++) {
        move_cursor(sl->x1, sl->y1 + i);
        printf("\033[%dX", width);
    }
    fflush(stdout);

    free(sl->buffer);
}

// LEGACY
// used as a replacement for diff_engine func
//
// draws a slice without checking for changes
// use only if bugs with default update occure
void FORCE_update_slice(Slice *sl, char *content) {
    int width = get_width(sl);
    int height = sl->y2 - (sl->y1 - 1);

    int y = sl->y1;

    move_cursor(sl->x1, sl->y1);

    for (int i = 0; i < sl->size - 1; i++) {
        // if new state ended, end the content in slice
        if (content[i] == '\0') {
            sl->buffer[i] = '\0';
            break;
        }
        else {
            sl->buffer[i] = content[i];
            // if a new line should start
            if (i && !( i % width ) ) {
                y++;
                move_cursor(sl->x1, y);
            }
        }
        // printing char anyway
        printf("%c", sl->buffer[i]);
    }
    // fflushing
    fflush(stdout);
}
