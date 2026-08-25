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
