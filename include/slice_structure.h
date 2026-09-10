#ifndef SL_STRUCT
#define SL_STRUCT

// basic slice interactions
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
