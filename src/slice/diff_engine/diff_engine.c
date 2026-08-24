#include <stdio.h> 
#include "../slice_funcs.h"
#include "../slice_structure.h"

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

void update(Slice* sl, char* string) {
	int i = 0;
	int start_edit = 0;
	int end_edit = 0;
	unsigned char edit = 0;
	while (sl->pointer[i] != '\0') {
		if (string[i] != sl->pointer[i]) {
			if (!edit) {
				start_edit = i;
				edit = 1;
			}
			end_edit = i;
			sl->pointer[i] = string[i];
		}
		if (edit) {
			edit = 0;
			int x = start_edit % get_width(sl);
			int y = start_edit / get_width(sl);
			printf("\033[%d;%dH", x, y);
			for (int j = start_edit; j <= end_edit; j++) {
				x++;
				if (x > get_width(sl)) {
					x = sl->x1;
					y++;
				}
				printf("%c", string[j]);
			}
			fflush(stdout);
		}
		i++;
	}
}
