#include <stdio.h>
#include "../slice_structure.h"
#include "../slice_funcs.h"
#include "../../cursor/cursor_funcs.h"

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

int moving_cursor_cost(int x, int y) {
	return 4+get_length(x)+get_length(y);
}

void update_buffer(int start_x, int start_y, int start_edit, int end_edit, Slice *sl, char *content) {
	move_cursor(start_x, start_y);
	int lines_count = start_y - sl->y1;
	for (int c = start_edit - 2; c < end_edit - 1; c++) {
		sl->pointer[c] = content[c - lines_count];
	    printf("%c", content[c - lines_count]);
	}
	fflush(stdout);
}

void update_slice(Slice *sl, char *content) {
    int lines_count = 0;

    int x = sl->x1;
    int y = sl->y1;
    int start_edit = 0;
    int end_edit = 0;

	int start_x = 0;
	int start_y = 0;

    for (int i = 0; i < sl->size-1; i++) {
        if (i && !(i % get_honest_width(sl))) {
            lines_count++;
            if (start_edit) {
                update_buffer(start_x, start_y, start_edit, end_edit, sl, content);
                start_edit = 0;
            }
            x = sl->x1;
            y++;
            start_edit = 0;
            continue;
        }
        else if (sl->pointer[i] != content[i - lines_count]) {
            if (!start_edit) {
				start_x = x;
				start_y = y;
            	start_edit = i + 1;
            }
            end_edit = i + 1;
        }
        else {
        	if (start_edit && moving_cursor_cost(start_x, start_y) < i - end_edit) {
        		update_buffer(start_x, start_y, start_edit, end_edit, sl, content);
        	}
        }
        x++;
    }
    if (start_edit) {
        update_buffer(start_x, start_y, start_edit, end_edit, sl, content);
        start_edit = 0;
    }
}
