#include <stdio.h>
#include "../slice_funcs.h"
#include "../slice_structure.h"
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
	for (int c = start_edit; c <= end_edit; c++) {
		if (sl->pointer[c] == '\n' || sl->pointer[c] == '\0') {
			printf("%c", sl->pointer[c]);
	    }
	    printf("%c", content[c]);
	}
}

void update_slice(Slice *sl, char *content) {
    int lines_count = 1;
    
    int x = sl->x1;
    int y = sl->y1;
    int start_edit = 0;
    int end_edit = 0;

	int start_x = 0;
	int start_y = 0;
    
    for (int i = 0; i < sl->size; i++) {
        x++;
        if (sl->pointer[i] == '\0') {
			if (start_edit) {
				update_buffer(start_x, start_y, start_edit, end_edit, sl, content);
			}
        	break;
        }
        else if (sl->pointer[i] == '\n') {
            lines_count++;
            x = sl->x1;
            y++;
            continue;
        }
        else if (sl->pointer[i] != content[i - (lines_count - 1)]) {
            sl->pointer[i] = content[i - (lines_count - 1)];
            if (!start_edit) {
				start_x = x;
				start_y = y;
            	start_edit = i;
            }
            end_edit = i;
        }
        else {
        	if (start_edit && moving_cursor_cost(start_x, start_y) < i - end_edit) {
        		update_buffer(start_x, start_y, start_edit, end_edit, sl, content);
        	}
        }
    }
}
