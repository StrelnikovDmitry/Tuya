#include <stdio.h>
#include <stdlib.h>

#include "slice_structure.h"
#include "../terminal/ansi.h"

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
