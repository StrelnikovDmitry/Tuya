#include <stdio.h>

// MUST BE the first command in the code
// buffer size value can be get from the special function get_buffer_size
// if should_hide_cursor does not equal zero cursor hides
void tuya_init(size_t buffer_size, unsigned char should_hide_cursor) {
    setvbuf(stdout, NULL, _IOFBF, buffer_size);
    printf("\033[1;1H\033[2J");
    if (should_hide_cursor) {
        printf("\033[?25l");
    }
    fflush(stdout);
}