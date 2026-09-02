# TUYA

<table align="center" style="border: none;">
  <tr>
    <td>
      <img src="gallery/icon.svg" width="400" height="200" />
    </td>
    <td style="padding-left: 20px;">
      <b>SECTIONS</b><br>
      <hr style="margin: 5px 0;">
      <a href="#technology">technology</a><br>
      <a href="#installation">installation</a><br>
      <a href="#quick-start">quick start</a><br>
      <a href="#docs">docs</a><br>
      <a href="#contributing">contributing</a><br>
      <a href="#license">license</a>
    </td>
  </tr>
</table>

Tuya is a lightweight and minimalistic library written in C for TUI rendering. It implements a dirty-rectangles strategy focused on isolated screen regions rather than global framebuffers.
## Technology

Tuya manages screen rendering through isolated local update zones called slices, avoiding global framebuffers and full-screen redraws. By processing only explicitly defined areas, the library minimizes memory allocation overhead and CPU utilization, rendering it suitable for resource-constrained environments and low-level matrix output.

Developers retain explicit control over slice allocation, positioning, and rendering cycles, bypassing standard heavy TUI abstractions in favor of direct terminal byte control.
## Installation

> *This section will be updated as development progresses.*
## Quick Start

### Basic concepts

#### Initialising

Before you start using the library, initialize the terminal by calling `tuya_init` at the beginning of your `main` function.

`tuya_init` configures the terminal buffer size and switches the terminal to manual control mode. This means that you will need to call `fflush` manually when necessary.

The function accepts two arguments:

1. **Buffer size** — you can specify the value manually or use `get_buffer_size()` to calculate it automatically.
2. **Cursor visibility** — an `unsigned char` value. If it is `0`, the cursor remains visible. Any non-zero value hides the cursor.

#### Buffer size

`get_buffer_size()` calculates the terminal area and multiplies it by the specified value. The optimal multiplier depends on your application, so it is worth experimenting with different values.

A multiplier of `0.5` should work well for most cases.

#### Shutting down

When your program finishes using the library, call `tuya_shutdown()` to restore the terminal to its original state.

#### Input handling

> **Note:** Input handling is not implemented in the library yet, so input events must currently be handled by your application.

### Example

The following example creates a simple program that displays a string in the center of the terminal and redraws it whenever the terminal window is resized.
```c
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
            clear_all();
            free(sl.buffer);

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
```
## Docs

> *This section will be updated as development progresses.*
## Contributing

Contributions, issues, and feature requests are welcome. Feel free to check the repository issues or submit pull requests.
## License

This project is licensed under the [MIT License](LICENSE).
