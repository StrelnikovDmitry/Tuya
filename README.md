# TUYA

<img src="gallery/icon.svg" width="400" height="200" />

Tuya is a lightweight and minimalistic library written in C for TUI rendering. It implements a dirty-rectangles strategy focused on isolated screen regions rather than global framebuffers.

| SECTIONS |
| :---: |
|[technology](#technology)|
|[quick start](#quick-start)|
|[docs](#docs)|
|[contributing](#contributing)|
|[license](#license)|
## Technology

Tuya manages screen rendering through isolated local update zones called slices, avoiding global framebuffers and full-screen redraws. By processing only explicitly defined areas, the library minimizes memory allocation overhead and CPU utilization, rendering it suitable for resource-constrained environments and low-level matrix output.

Developers retain explicit control over slice allocation, positioning, and rendering cycles, bypassing standard heavy TUI abstractions in favor of direct terminal byte control.
## Quick Start

> *This section will be updated as development progresses.*
## Docs

> *This section will be updated as development progresses.*
## Contributing

Contributions, issues, and feature requests are welcome. Feel free to check the repository issues or submit pull requests.
## License

This project is licensed under the [MIT License](LICENSE).
