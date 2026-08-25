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

void update_slice(Slice *sl, char *content) {
    int lines_count = 1;
    int x = sl->x1;
    int y = sl->y1;
    for (int i = 0; i < sl->size; i++) {
        x++;
        if (sl->pointer[i] == '\0') {
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
            move_cursor(x, y);
            printf("%c", sl->pointer[i]);
        }
    }
}
