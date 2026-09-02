#ifndef SLICE_FUNCS
#define SLICE_FUNCS

#include "slice_structure.h"

Slice create_slice(int x1, int y1, int x2, int y2);
void delete_slice(Slice *sl);

int get_honest_width(Slice *sl);
int get_width(Slice *sl);
int get_height(Slice *sl);

void FORCE_update_slice(Slice *sl, char *content);

#endif
