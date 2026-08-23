#ifndef SLICE_FUNCS
#define SLICE_FUNCS

#include "slice_structure.h"

void slice_update_force(Slice sl, char *content);
Slice create_slice(int x1, int y1, int x2, int y2);
int get_honest_width(Slice *sl);
int get_width(Slice *sl);
int get_height(Slice *sl);

#endif
