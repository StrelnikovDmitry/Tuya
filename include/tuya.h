/* This header is a public API containing tested and ready to use functions
 * Functions in this header provide the normal, high-level interface
 * to the library. They handle output according to Tuya's standard output semantics */

#ifndef TUYA
#define TUYA

// global functions configuring terminal, getting terminal size, etc
#include "../src/global/tuya_global_funcs.h"

// basic slice interactions
#include "../src/slice/slice_funcs.h"
#include "../src/slice/slice_structure.h"

// difference based render
#include "../src/slice/diff_engine/diff_engine.h"

#endif
