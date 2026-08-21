#include "slice_structure.h"
#include <stdio.h>
#include <stdlib.h>

Slice create_slice(int x1, int y1, int x2, int y2) {
    Slice slice;

	slice.size = sizeof(char) * ((x2 - (x1 - 1)) + 1) * (y2 - (y1 - 1));
	slice.pointer = malloc(slice.size);
	slice.pointer[slice.size-1] = '\0';

	slice.x1 = x1;
	slice.y1 = y1;
	slice.x2 = x2;
	slice.y2 = y2;

	return slice;
}


void slice_update_force(Slice sl, char *content) {
    int width = (sl.x2+1) - (sl.x1 - 1);
    int count_lines = 1;
    for (int i = 0; i < sl.size; i++) {
        // if new state ended, end the content in slice
        if (content[i - (count_lines - 1)] == '\0') {
            sl.pointer[i] = '\0';
            break;
        }
        else {
            //if there shouldn't start another line
            if ((i + 1) % width) {
                sl.pointer[i] = content[i - (count_lines - 1)];
            }
            //if there should
            else {
                // if there can't fit new line
                if (count_lines + 1 > sl.y2 - (sl.y1 - 1)) {
                    sl.pointer[i] = '\0';
                    break;
                }
                // if there can
                else {
                    sl.pointer[i] = '\n';
                    count_lines++;
                    i++;
                    sl.pointer[i] = content[i - (count_lines - 1)];
                }
            }
        }
    }
    // moving cursor (need to change to my own function)
    printf("\033[%d;%dH", sl.y1, sl.x1);

    // printing new string
    printf("%s", sl.pointer);
    fflush(stdout);
}
