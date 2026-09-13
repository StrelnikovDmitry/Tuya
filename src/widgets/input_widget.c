#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "../terminal/ansi.h"
#include "../slice/static/static.h"

// create input line
// returned array should be explicitly deleted
char* ask_input(int x1, int x2, int y, char *message) {
    int width = x2 - (x1 - 1);

    // finding message size
    int message_size = 0;
    while (message[message_size] != '\0') {
        message_size++;
    }

    // if message can't fit
    if (message_size >= width) {
        return 0;
    }
    else {
        // print message
        print_static(x1, y, x2, y, message);

        // create string to store input
        char *input = malloc(sizeof(char)*(width-message_size + 1));
        input[width-message_size] = '\0';
        char ch;

        // index of input array
        int counter = 0;

        // if the text is already red
        unsigned char warning = 0;
        while(read(STDIN_FILENO, &ch, 1) == 1 && (ch != 27 && ch != 10)) {
            // if there are no more place for chars
            if (counter >= width-message_size) {
                // if text is not red
                if (warning == 0) {
                    // make it red
                    move_cursor(x1, y);
                    printf("\033[31m%s%s\033[0m", message, input);
                    fflush(stdout);
                    warning = 1;
                }
            }
            else {
                input[counter] = ch;
                counter++;

                // printing char
                putchar(ch);
                fflush(stdout);
            }
        }
        // ending line
        input[counter] = '\0';

        return input;
    }
}
