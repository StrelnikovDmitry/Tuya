# Raw API

`tuya_raw.h` provides legacy and low-level helpers. These functions are usable, but their interface may change and is not guaranteed to stay backward-compatible. Prefer [`tuya.h`](stable_API.md) when you can.

# Legacy

## Non-difference based updating

If difference-based [`update_slice`](../src/slice/update_funcs/update_funcs.c#L37) misbehaves, use [`FORCE_update_slice`](../src/slice/update_funcs/update_funcs.c#L99) as a fallback. It redraws the whole slice without comparing against the previous buffer.

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
