/* This header is a public API containing tested and ready to use functions
 * Functions in this header provide the normal, high-level interface
 * to the library. They handle output according to Tuya's standard output semantics */

#ifndef TUYA
#define TUYA

#include <stdlib.h>
#include "slice_structure.h"

// global functions configuring terminal, getting terminal size, etc
void tuya_init(size_t buffer_size, unsigned char should_hide_cursor);
void tuya_shutdown();
int get_terminal_height();
int get_terminal_width();
size_t get_buffer_size(float multiply_by);

// static print
void print_static (int x1, int y1, int x2, int y2, char *content);

// basic slice operations
Slice create_slice(int x1, int y1, int x2, int y2);
void delete_slice(Slice *sl);

int get_honest_width(Slice *sl);
int get_width(Slice *sl);
int get_height(Slice *sl);

// difference based render
void update_slice(Slice *sl, char *content);

// --- WIDGETS ---

//progress bar
typedef struct {
    Slice sl;

    int current;
    int aim;
} Progress_bar;

void update_progress_bar(Progress_bar *prb,int current);
Progress_bar create_progress_bar(int x1,int y1,int x2,int y2,int max);

#endif
