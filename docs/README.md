# Tuya

Tuya is a minimalistic TUI library designed for minimal resource consumption by implementing manual handling of specified screen parts called slices.

## Links

* tuya.h - stable functions
  * global functions
    * initialising 
    * getting terminal and buffer sizes
    * shutting down
  * slices
    * basic slice operations
      * creating slice
      * deleting slice
      * getting slice width
      * getting slice height
    * updating
      * difference based update
* tuya_raw.h - experimental, legacy and ugly functions to use
  * legacy
    * non-difference based updating
  * experimental
    * static slice
  * ansi codes
    * moving cursor
    * clearing terminal
    * hiding and showing cursor
    * turning alternative screen on and off

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
