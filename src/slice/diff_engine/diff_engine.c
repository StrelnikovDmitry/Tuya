#include <stdio.h>
#include "../slice_structure.h"
#include "../slice_funcs.h"
#include "../../cursor/cursor_funcs.h"

// branchless algorithm for findin length of an integer given
// it could be binary search algorithm but this one is faster practically
int get_length(int n) {
	int length = 1;
	length += (n > 9);
	length += (n > 99);
	length += (n > 999);
	length += (n > 9999);
	length += (n > 99999);
	length += (n > 999999);
	length += (n > 9999999);
	length += (n > 99999999);
	length += (n > 999999999);

	return length;
}

// getting cost of ANSI code moving cursor to the given place
int moving_cursor_cost(int x, int y) {
	return 4+get_length(x)+get_length(y);
}

// updating a small part of slice given.
void update_sequence(int start_x, int start_y, int start_edit, int end_edit, Slice *sl, char *content) {
	move_cursor(start_x, start_y);
	for (int c = start_edit - 1; c <= end_edit - 1; c++) {
		sl->buffer[c] = content[c];
	    printf("%c", content[c]);
	}
}

void update_slice(Slice *sl, char *content) {
    int x = sl->x1;
    int y = sl->y1;

    // the buffer will be between indexes (start_edit - 1) and end (edit - 1)
    // assigning it to zero so some if statements that are designed to react only when the
    // start edit is assigned to a value didn't react
    int start_edit = 0;
    int end_edit = 0;

	// coordinates of a (start_edit - 1) index
	int start_x = 0;
	int start_y = 0;

    for (int i = 0; i < sl->size - 1; i++) {
        // checking whether we should go to another line
        if ( i && !( i % get_width(sl) ) ) {
            if (start_edit) {
                update_sequence(start_x, start_y, start_edit, end_edit, sl, content);
                start_edit = 0;
            }
            x = sl->x1;
            y++;
        }

        if (sl->buffer[i] != content[i]) {
            if (!start_edit) {
				start_x = x;
				start_y = y;
				// assigning start_edit to an index + 1 so conditions like
				// (start_edit) would work
            	start_edit = i + 1;
            }
            // same as start_edit
            end_edit = i + 1;
        }
        else {
        	// compare the amount of unchanged chars we need to change if we don't move cursor
        	// with the cost of cursor moving
        	// basically, if the cost is higher than the amount of unchanged symbols,
        	// we change the symbols beetwen to buffers to reduce CPU usage (printf usage)
        	if (start_edit && moving_cursor_cost(start_x, start_y) < i - end_edit) {
        		update_sequence(start_x, start_y, start_edit, end_edit, sl, content);
        	}
        }

        x++;
    }
    // final update if needed
    if (start_edit) {
        update_sequence(start_x, start_y, start_edit, end_edit, sl, content);
        start_edit = 0;
    }
    // fflushing
    fflush(stdout);
}
