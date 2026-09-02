#include "../src/slice/slice_structure.h"
#include "../src/slice/slice_funcs.h"
#include "../src/slice/diff_engine/diff_engine.h"
#include "../src/global/tuya_global_funcs.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

Slice *sl = NULL;

void update(int sig) {
    update_slice(sl, "      ");

    delete_slice(sl);
    int x = (get_terminal_width() - 6) / 2;
    int y = get_terminal_height() / 2;

    *sl = create_slice(x, y, x + 6, y);
    update_slice(sl, "center");
}

int main() {
    tuya_init(get_buffer_size(0.1), 1);

    sl = malloc(sizeof(Slice));

    int x = (get_terminal_width() - 6) / 2;
    int y = get_terminal_height() / 2;
    *sl = create_slice(x, y, x + 6, y);

    update_slice(sl, "center");

    signal(SIGWINCH, update);
    while (1) {
        pause();
    }

    tuya_shutdown();
    return 0;
}
