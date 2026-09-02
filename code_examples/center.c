#include "../src/slice/slice_structure.h"
#include "../src/slice/slice_funcs.h"
#include "../src/slice/diff_engine/diff_engine.h"
#include "../src/global/tuya_global_funcs.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile unsigned char do_redraw = 0;

void update(int sig) {
    do_redraw = 1;
}

int main() {
    tuya_init(get_buffer_size(0.1), 1);

    int x = (get_terminal_width() - 6) / 2;
    int y = get_terminal_height() / 2;

    Slice sl = create_slice(x, y, x + 6, y);
    update_slice(&sl, "center");

    signal(SIGWINCH, update);
    while (1) {
        if (do_redraw) {
            do_redraw = 0;
            delete_slice(&sl);

            int x = (get_terminal_width() - 6) / 2;
            int y = get_terminal_height() / 2;

            sl = create_slice(x, y, x + 6, y);
            update_slice(&sl, "center");
        }
        pause();
    }

    tuya_shutdown();
    return 0;
}
