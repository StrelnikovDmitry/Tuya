#include "../slice/slice_structure.h"
#include "../slice/slice_funcs.h"
#include "../slice/update_funcs/update_funcs.h"
#include "progress_bar_structure.h"

// creating a progress bar
ProgressBar create_progress_bar(int x1, int y1, int x2, int y2, int target) {
    ProgressBar prb;

    prb.sl = create_slice(x1, y1, x2, y2);

    prb.current = 0;
    prb.target = target;

    return prb;
}

void update_progress_bar(ProgressBar *prb, int current) {
    // updating current position
    prb->current = current;

    int width = get_width(&(prb->sl));
    int height = get_height(&(prb->sl));
    int to_fill = ((float)prb->current / prb->target) * width;

    char buffer[prb->sl.size];
    buffer[prb->sl.size - 1] = '\0';

    // filling the buffer
    for (int i = 0; i < width; i++) {
        if (i <= to_fill) {
            // assigning all the lines at position x to '#'
            for (int h = 0; h < height; h++) {
                buffer[i + (h * width)] = '#';
            }
        }
        else {
            // assigning all the lines at position x to ' '
            for (int h = 0; h < height; h++) {
                buffer[i + (h * width)] = ' ';
            }
        }
    }

    update_slice(&(prb->sl), buffer);
}
