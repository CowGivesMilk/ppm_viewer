cmake_minimum_required(VERSION 4.0.0)

project(ppm_viewer
    VERSION 1.0
    LANGUAGES CXX
)

# -------------------- C++ Standard --------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# -------------------- Library --------------------
add_library(ppm_core
    src/pixel.cpp
    src/ppm.cpp
)

target_include_directories(ppm_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# -------------------- Main Executable --------------------
add_executable(ppm_viewer
    main.cpp
)

target_link_libraries(ppm_viewer
    PRIVATE
        ppm_core
)

# -------------------- Compiler Warnings --------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ppm_core PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    target_compile_options(ppm_viewer PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# -------------------- Tests --------------------
# Tests can be added later.
# enable_testing()
# add_subdirectory(tests)
