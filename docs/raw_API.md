# Raw API

`tuya_raw.h` provides legacy and low-level helpers. These functions are usable, but their interface may change and is not guaranteed to stay backward-compatible. Prefer [`tuya.h`](stable_API.md) when you can.

# ANSI codes

Thin wrappers around common terminal escape sequences. They write directly to stdout; call `fflush` yourself when you need the output to appear immediately (unless another Tuya function already flushed).

## Moving cursor

To place the cursor at a given column and row, use [`move_cursor`](../src/terminal/ansi.c#L5).

The function takes two arguments:
- int x — column number.
- int y — row number.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    move_cursor(10, 5);
    printf("here");
    fflush(stdout);

    tuya_shutdown();
    return 0;
}
```

## Clearing terminal

To clear from the cursor to the end of the line, use [`clear_the_rest`](../src/terminal/ansi.c#L10).

To clear the whole screen, use [`clear_all`](../src/terminal/ansi.c#L15). This is also useful with `SIGWINCH` handling when you rebuild slices after a resize.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    clear_all();
    move_cursor(1, 1);
    printf("clean screen");
    fflush(stdout);

    tuya_shutdown();
    return 0;
}
```

## Hiding and showing cursor

To hide the cursor, use [`hide_cursor`](../src/terminal/ansi.c#L25).

To show it again, use [`show_cursor`](../src/terminal/ansi.c#L20).

> **Note:** `tuya_init` can already hide the cursor for you. These helpers are for manual control outside of that.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 0); // leave cursor visible

    hide_cursor();
    /* YOUR CODE HERE */
    show_cursor();

    tuya_shutdown();
    return 0;
}
```

## Turning alternative screen on and off

To switch to the alternative screen buffer (no scrollback history in the session), use [`turn_alt_screen_on`](../src/terminal/ansi.c#L30).

To restore the previous screen, use [`turn_alt_screen_off`](../src/terminal/ansi.c#L35).

> **Note:** `tuya_init` / `tuya_shutdown` already manage the alternative screen. Use these only if you need to toggle it yourself.

### Code-example

```c
int main() {
    turn_alt_screen_on();
    /* YOUR CODE HERE */
    turn_alt_screen_off();
    return 0;
}
```

# Raw input mode

By default the terminal is in cooked mode (line-buffered, echoed). For character-by-character input (for example with [`ask_input`](#ask-input)), switch to raw mode.

## Enabling raw

To disable echo and canonical line editing, use [`enable_raw`](../src/global/tuya_global_funcs.c#L25). It saves the previous terminal attributes into the struct you pass, then turns raw mode on.

The function takes one argument:
- struct termios *orig_termios — pointer where current attributes are stored so you can restore them later. Include `<termios.h>`.

## Disabling raw

To restore previous terminal attributes, use [`disable_raw`](../src/global/tuya_global_funcs.c#L38) with the same `struct termios` you filled in `enable_raw`.

### Code-example

```c
#include <tuya.h>
#include <tuya_raw.h>
#include <termios.h>

int main() {
    struct termios orig;

    tuya_init(get_buffer_size(0.5), 1);
    enable_raw(&orig);

    /* read chars with read() / ask_input() here */

    disable_raw(&orig);
    tuya_shutdown();
    return 0;
}
```

# Legacy

## Non-difference based updating

If difference-based [`update_slice`](../src/slice/update_funcs/update_funcs.c#L37) misbehaves, use [`FORCE_update_slice`](../src/slice/update_funcs/update_funcs.c#L105) as a fallback. It redraws the whole slice without comparing against the previous buffer.

The function takes two arguments:
- Slice *sl — pointer to the slice you want to redraw.
- char *content — new content for the slice. Writing stops early if a `'\0'` is hit inside the slice area.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    Slice sl = create_slice(10, 5, 15, 5);
    FORCE_update_slice(&sl, "hello");

    delete_slice(&sl);
    tuya_shutdown();
    return 0;
}
```

# Widgets

## Ask input

To show a one-line prompt and read typed text into a heap buffer, use [`ask_input`](../src/widgets/input_widget.c#L11). It prints `message` inside `[x1, x2]` on row `y`, then reads characters until Enter or Esc.

The function takes four arguments:
- int x1, x2 — left and right bounds of the input line.
- int y — row of the input line.
- char *message — prompt text printed before the typed input. Must fit inside the line width; otherwise the function returns `NULL` (`0`).

Returns a `malloc`'d null-terminated string with the typed text. You must `free` it yourself. Supports backspace; when the line is full, the prompt turns red until you delete characters.

> **Note:** Call `ask_input` only after turning on raw input terminal mode ([`enable_raw`](#enabling-raw))

### Code-example

```c
#include <tuya.h>
#include <tuya_raw.h>
#include <termios.h>
#include <stdlib.h>

int main() {
    struct termios orig;

    tuya_init(get_buffer_size(0.5), 0);
    enable_raw(&orig);

    char *name = ask_input(2, 40, 5, "name: ");
    if (name) {
        /* use name */
        free(name);
    }

    disable_raw(&orig);
    tuya_shutdown();
    return 0;
}
```
