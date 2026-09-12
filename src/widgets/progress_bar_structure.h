#ifndef PROGRESS_BAR_STRUCTURE
#define PROGRESS_BAR_STRUCTURE

#include "../slice/slice_structure.h"

typedef struct {
    Slice sl;

    int current;
    int target;
} ProgressBar;

#endif
