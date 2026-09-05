#ifndef SLICE_STRUCT
#define SLICE_STRUCT

typedef struct {
    // upper left corner
    int x1;
	int y1;

	// lower right corner
	int x2;
	int y2;

	// automatically calculated size based on area (area + 1 for terminator)
	int size;

	// a pointer to the content inside
	char *buffer;
} Slice;

#endif
