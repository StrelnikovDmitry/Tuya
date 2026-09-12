# Global functions

## Initialising

to start an application without risk of erasing user's terminal story and to set up the virtual buffer for maximum recource economy, use [`tuya_init`](../src/global/tuya_global_funcs.c#L9) at the start of your programm.

The function takes two arguments:
- size_t buffer_size, which is virtual buffer size. Can be assigned manually or calculated based on terminal size (see [**further**](#getting-virtual-buffer-size)).
- unsigned char hide_cursor. Decides whether the cursor should be hidden. Every non-zero value will hide the cursor.

### Code-example

```c
int main() {
    tuya_init(1024, 1); // will assign virtual buffer size to 1024 and hidde cursor
    return 0;
}
```

## Getting terminal size

To get terminal width and height use [`get_terminal_width`](../src/global/tuya_global_funcs.c#L43) and [`get_terminal_height`](../src/global/tuya_global_funcs.c#L31) funcs. Both function return current size of terminal.

## Getting virtual buffer size

To get buffer size you should use [`get_buffer_size`](../src/global/tuya_global_funcs.c#L57) function. It takes terminal size and multiplies it by float given in argument. In most cases 0.5 multiplicator should be enough, however, optimal multiplicator is depends on your programm. I insist on finding perfect value by experimenting with your program.

This function is very convenient to use with `tuya_init`.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);
    return 0;
}
```

## Shutting your programm down

To restore your terminal (basically, revert changes of `tuya_init`), use [`tuya_shutdown`](../src/global/tuya_global_funcs.c#L19) function.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);
    /* YOUR CODE HERE */
    tuya_shutdown();
    return 0;
}
```

# Slices

Slices are isolated screen regions that Tuya updates instead of redrawing a global framebuffer. You allocate them yourself, place them with coordinates, and control when they are rendered.

## Basic slice operations

### Creating slice

To allocate a slice on the screen, use [`create_slice`](../src/slice/slice_funcs.c#L17). It creates a `Slice` covering the rectangle between two corners and allocates an internal buffer for that area.

The function takes four arguments:
- int x1, y1 — upper left corner of the slice.
- int x2, y2 — lower right corner of the slice.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    Slice sl = create_slice(10, 5, 20, 5); // one-line slice from (10, 5) to (20, 5)
    /* YOUR CODE HERE */

    tuya_shutdown();
    return 0;
}
```

### Deleting slice

To clear a slice from the terminal and free its buffer, use [`delete_slice`](../src/slice/slice_funcs.c#L37). It erases the slice area on screen, then frees `sl->buffer`.

> **Note:** `delete_slice` does not work correctly when handling terminal resize (`SIGWINCH`). In that case free the buffer manually with `free(sl.buffer)` and clear the screen with `clear_all` instead (see the example in the project README or examples/center.c).

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    Slice sl = create_slice(10, 5, 20, 5);
    /* YOUR CODE HERE */
    delete_slice(&sl);

    tuya_shutdown();
    return 0;
}
```

### Getting slice width

To get the width of a slice in characters, use [`get_width`](../src/slice/slice_funcs.c#L8). It returns the horizontal size calculated from the slice corners.

### Getting slice height

To get the height of a slice in characters, use [`get_height`](../src/slice/slice_funcs.c#L13). It returns the vertical size calculated from the slice corners.

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    Slice sl = create_slice(10, 5, 20, 7);
    int w = get_width(&sl);  // 11
    int h = get_height(&sl); // 3

    delete_slice(&sl);
    tuya_shutdown();
    return 0;
}
```

## Updating

### Difference based update

To redraw a slice, use [`update_slice`](../src/slice/update_funcs/update_funcs.c#L37). It compares the new content with the slice buffer and prints only the changed parts, which keeps CPU and I/O usage low.

The function takes two arguments:
- Slice *sl — pointer to the slice you want to update.
- char *content — new content for the slice. Length should match the slice area (`get_width(sl) * get_height(sl)`).

### Code-example

```c
int main() {
    tuya_init(get_buffer_size(0.5), 1);

    Slice sl = create_slice(10, 5, 15, 5);
    update_slice(&sl, "hello");

    delete_slice(&sl);
    tuya_shutdown();
    return 0;
}
```
