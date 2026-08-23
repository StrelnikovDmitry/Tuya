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
	while (sl->pointer[i] != '\0') {
		if (string[i] != sl->pointer[i]) {
			sl->pointer[i] = string[i];
		}
		i++;
	}
}
