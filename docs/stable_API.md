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

To get terminal width and height use [`get_terminal_width`](../src/global/tuya_global_funcs.c#L43) and [`get_terminal_height`](../sr31c/global/tuya_global_funcs.c#L) funcs. Both function return current size of terminal.

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
