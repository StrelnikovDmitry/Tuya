#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "../terminal/ansi.h"
#include "../slice/static/static.h"

char* ask_input(int x1, int x2, int y, char *message) {
    int width = x2 - (x1 - 1);

    int message_size = 0;
    while (message[message_size] != '\0') {
        message_size++;
    }

    if (message_size >= width) {
        return 0;
    }
    else {
        print_static(x1, y, x2, y, message);
        char *input = malloc(sizeof(char)*(width-message_size + 1));
        input[width-message_size] = '\0';
        char ch;

        int counter = 0;
        unsigned char warning = 0;
        while(read(STDIN_FILENO, &ch, 1) == 1 && (ch != 27 && ch != 10)) {
            if (counter >= width-message_size) {
                if (warning == 0) {
                    move_cursor(x1, y);
                    printf("\033[31m%s%s\033[0m", message, input);
                    fflush(stdout);
                    warning = 1;
                }
            }
            else {
                input[counter] = ch;

                counter++;
                putchar(ch);
                fflush(stdout);
            }
        }
        input[counter] = '\0';

        return input;
    }
}
