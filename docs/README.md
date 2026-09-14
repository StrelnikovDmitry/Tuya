# Tuya

Tuya is a minimalistic TUI library designed for minimal resource consumption by implementing manual handling of specified screen parts called slices.

## Links

* [tuya.h](stable_API.md) - stable functions
  * [global functions](stable_API.md#global-functions)
    * [initialising](stable_API.md#initialising)
    * [getting terminal and buffer sizes](stable_API.md#getting-terminal-size)
    * [shutting down](stable_API.md#shutting-your-programm-down)
  * [static print](stable_API.md#static-print)
  * [slices](stable_API.md#slices)
    * [basic slice operations](stable_API.md#basic-slice-operations)
      * [creating slice](stable_API.md#creating-slice)
      * [deleting slice](stable_API.md#deleting-slice)
      * [getting slice width](stable_API.md#getting-slice-width)
      * [getting slice height](stable_API.md#getting-slice-height)
    * [updating](stable_API.md#updating)
      * [difference based update](stable_API.md#difference-based-update)
  * [widgets](stable_API.md#widgets)
    * [progress bar](stable_API.md#progress-bar)
      * [creating progress bar](stable_API.md#creating-progress-bar)
      * [updating progress bar](stable_API.md#updating-progress-bar)
* [tuya_raw.h](raw_API.md) - experimental, legacy and ugly functions to use
  * [ansi codes](raw_API.md#ansi-codes)
    * [moving cursor](raw_API.md#moving-cursor)
    * [clearing terminal](raw_API.md#clearing-terminal)
    * [hiding and showing cursor](raw_API.md#hiding-and-showing-cursor)
    * [turning alternative screen on and off](raw_API.md#turning-alternative-screen-on-and-off)
  * [raw input mode](raw_API.md#raw-input-mode)
    * [enabling raw](raw_API.md#enabling-raw)
    * [disabling raw](raw_API.md#disabling-raw)
  * [legacy](raw_API.md#legacy)
    * [non-difference based updating](raw_API.md#non-difference-based-updating)
  * [widgets](raw_API.md#widgets)
    * [ask input](raw_API.md#ask-input)

## Installation

To install Tuya to `/usr/local` using CMake, you need to clone the repository:
```bash
git clone https://github.com/StrelnikovDmitry/Tuya
cd Tuya
```

After that, configure and build the project
```bash
cmake -S . -B build
cmake --build build
```

Finally, install it
```bash
sudo cmake --install build --prefix /usr/local
```
