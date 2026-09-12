#ifndef PROGRESS_BAR_FUNCS
#define PROGRESS_BAR_FUNCS

#include "progress_bar_structure.h"

void update_progress_bar(Progress_bar *prb,int current);
Progress_bar create_progress_bar(int x1,int y1,int x2,int y2,int max);

#endif
