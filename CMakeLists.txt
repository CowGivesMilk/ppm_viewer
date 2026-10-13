cmake_minimum_required(VERSION 3.20)

project(ppm_viewer
    VERSION 1.0.0
    LANGUAGES CXX
)

# -------------------- C++ Standard --------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------- Qt Code Generators --------------------
set(CMAKE_AUTOMOC ON)   # processes Q_OBJECT classes (signals/slots)
set(CMAKE_AUTOUIC ON)   # processes .ui files from Designer
set(CMAKE_AUTORCC ON)   # processes .qrc resource files

# -------------------- Dependency --------------------
find_package(Qt6 REQUIRED COMPONENTS Widgets Gui)
find_package(CLI11 REQUIRED)
# -------------------- Core Library (no Qt) --------------------
add_library(ppm_core
    src/pixel.cpp
    src/ppm.cpp
)

target_include_directories(ppm_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(ppm_core
    PUBLIC
        Qt6::Gui
        CLI11::CLI11
)
# -------------------- GUI Executable --------------------
add_executable(ppm_viewer
    gui/main.cpp
    gui/mainwindow.cpp
    gui/mainwindow.h
)

target_link_libraries(ppm_viewer
    PRIVATE
        ppm_core
        Qt6::Widgets
)

# -------------------- Compiler Warnings --------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ppm_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ppm_viewer PRIVATE -Wall -Wextra -Wpedantic)
endif()

# -------------------- Tests --------------------
# Tests can be added later.
# enable_testing()
# add_subdirectory(tests)
