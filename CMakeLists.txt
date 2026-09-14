cmake_minimum_required(VERSION 3.20)

project(Tuya
    VERSION 1.3.1
    LANGUAGES C
)

# ============================================================
# Library
# ============================================================

add_library(tuya STATIC
    src/global/tuya_global_funcs.c

    src/slice/update_funcs/update_funcs.c
    src/slice/static/static.c
    src/slice/slice_funcs.c

    src/widgets/progress_bar.c
    src/widgets/input_widget.c

    src/terminal/ansi.c
)

# ------------------------------------------------------------
# Include directories
# ------------------------------------------------------------

target_include_directories(tuya
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ============================================================
# Installation
# ============================================================

include(GNUInstallDirs)

# Install library
install(TARGETS tuya
    EXPORT TuyaTargets

    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}

    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install public headers
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install CMake target description
install(
    EXPORT TuyaTargets
    FILE TuyaTargets.cmake
    NAMESPACE Tuya::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Tuya
)
