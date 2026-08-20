#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

// MUST BE the first command in the code
// buffer size value can be get from the special function get_buffer_size
// if should_hide_cursor does not equal zero cursor hides
void tuya_init(size_t buffer_size, unsigned char should_hide_cursor) {
    setvbuf(stdout, NULL, _IOFBF, buffer_size);
    printf("\033[1049h\033[1;1H\033[2J");
    if (should_hide_cursor) {
        printf("\033[?25l");
    }
    fflush(stdout);
}

void tuya_shutdown() {
    printf("\033[1049l\033[0m\033[?25l");
    fflush(stdout);
    abort();
}


// If you want to update the whole screen every frame, you should use multiplicator 4 or more.
// Either way, 0.5 or 1 is usually enough.
size_t get_buffer_size(float multiply_by) {
    struct winsize ws;
    int result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    if (result != -1) {
        size_t buffer_size = ws.ws_col*ws.ws_row*multiply_by;
        return buffer_size;
    }
    else {
        fputs("TUYA ERROR: NO TERMINAL SIZE\nThis usually means stdout is not connected to a terminal, or your OS isn't supported yet.\n\n Check official tuya github: https://github.com/StrelnikovDmitry/tuya/issues or write your own issue.", stderr);
        // TEMPORARY WAY OF CRASHING PROGRAMM: it will change after tuya_shutdown function will be created
        abort();
        // TODO:
        // make normal tuya_shutdown function
    }
}
