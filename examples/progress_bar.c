#include <tuya.h>
#include <unistd.h>

void do_something () {}

int main() {
    tuya_init(get_buffer_size(0.5), 1);

    Progress_bar prb = create_progress_bar(/*x1=*/1, /*y1=*/1,/*x2=*/10,/*y2=*/1,/*max=*/10);

    char letter[1];

    for (int i = 0; i < 10; i++) {
        do_something();
        update_progress_bar(&prb, i);
        sleep(1);
    }

    tuya_shutdown();

    return 0;
}
