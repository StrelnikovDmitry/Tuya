#include "slice_structure.h"
#include <stdlib.h>

Slice create_slice(int x1, int y1, int x2, int y2, char *content) {
	Slice slice;

	slice.pointer = malloc(sizeof(char)*(x2-x1)*(y2-y1)+1);

	slice.x1 = x1;
	slice.y1 = y1;
	slice.x2 = x2;
	slice.y2 = y2;

	return slice;
}
