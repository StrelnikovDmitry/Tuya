#include "slice_structure.h"
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
