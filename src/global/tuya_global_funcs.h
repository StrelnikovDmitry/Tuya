#ifndef GLOBAL_FUNCS
#define GLOBAL_FUNCS

#include <stdlib.h>

void tuya_init(size_t buffer_size, unsigned char should_hide_cursor);
void tuya_shutdown();
int get_terminal_height();
int get_terminal_width();
size_t get_buffer_size(float multiply_by);

#endif
