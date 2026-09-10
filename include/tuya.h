/* This header is a public API containing tested and ready to use functions
 * Functions in this header provide the normal, high-level interface
 * to the library. They handle output according to Tuya's standard output semantics */

#ifndef TUYA
#define TUYA

#include <stdlib.h>

// global functions configuring terminal, getting terminal size, etc
void tuya_init(size_t buffer_size, unsigned char should_hide_cursor);
void tuya_shutdown();
int get_terminal_height();
int get_terminal_width();
size_t get_buffer_size(float multiply_by);

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

Slice create_slice(int x1, int y1, int x2, int y2);
void delete_slice(Slice *sl);

int get_honest_width(Slice *sl);
int get_width(Slice *sl);
int get_height(Slice *sl);

void FORCE_update_slice(Slice *sl, char *content);

// difference based render
void update_slice(Slice *sl, char *content);

#endif
