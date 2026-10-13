# PPM Viewer

A small, fast image viewer for **PPM (P3, plain-text)** images, written in C++23 with a Qt6 Widgets GUI.

The PPM parser lives in its own library (`ppm_core`) and the GUI is a thin layer on top of it, so the decoding logic can be reused or tested without touching any window code.

## Features

- Parses plain-text PPM (`P3`) files with validation and clear error messages
- Supports any maximum color value from 1 to 255, rescaled to full 8-bit range for display
- Opens a file from `--file`, or reads an image from **stdin** (handy for pipes)
- Window opens at the image's native size
- Images larger than the window are scaled down smoothly while keeping their aspect ratio, and re-fitted live as you resize
- Includes a Python script for generating test images (Mandelbrot set, radial rainbow, smooth noise)

## Requirements

| Dependency | Notes |
|---|---|
| C++23 compiler | GCC 14+ or Clang 18+ (the code uses `<print>` / `std::println`) |
| CMake | 3.20 or newer |
| Qt 6 | `Widgets` and `Gui` components |
| [CLI11](https://github.com/CLIUtils/CLI11) | Found through `find_package(CLI11)` |
| Python 3 | Optional, only for `gen_ppm.py` |

Example installs:

```bash
# Arch
sudo pacman -S qt6-base cli11 cmake gcc

# Debian / Ubuntu
sudo apt install qt6-base-dev libcli11-dev cmake g++
```

## Building

```bash
git clone git@github.com:CowGivesMilk/ppm_viewer.git
cd ppm_viewer
./build.sh
```

The binary is placed at `target/ppm_viewer`.

### `build.sh` options

```
Usage: ./build.sh [-run] [-release] [-clean] [-args PROGRAM_ARGS...]
```

| Flag | Effect |
|---|---|
| `-run` | Run `ppm_viewer` after a successful build |
| `-release` | Build in Release mode (default is Debug) |
| `-clean` | Delete the `target/` build directory first |
| `-args ...` | Pass everything after it to `ppm_viewer` (must be the last option) |
| `-h`, `--help` | Show usage |

Examples:

```bash
./build.sh -release                          # optimized build
./build.sh -clean -release                   # rebuild from scratch
./build.sh -run -args --file image.ppm       # build, then open image.ppm
```

### Building manually

```bash
cmake -S . -B target -DCMAKE_BUILD_TYPE=Release
cmake --build target -j"$(nproc)"
```

## Usage

```bash
# Open a file
./target/ppm_viewer --file image.ppm

# Read from stdin (omit --file, or pass '-')
cat image.ppm | ./target/ppm_viewer
./target/ppm_viewer --file - < image.ppm
```

If no file is given and stdin is a terminal, the program prints its help text and exits with status 1. It also exits with status 1 if the file can't be opened.

| Option | Description |
|---|---|
| `--file PATH` | PPM file to open. Omit it or use `-` to read from stdin |
| `-h`, `--help` | Show help |

## Generating test images

`gen_ppm.py` writes plain-text PPM files using only the Python standard library:

| Function | Output |
|---|---|
| `mandelbrot_set(filename, width, height, max_iter=100)` | Mandelbrot set with a smooth palette |
| `radial_rainbow(filename, width, height)` | Hue wheel that darkens toward the corners |
| `perlin_style_smooth_noise(filename, width, height, cell=32)` | Grayscale value noise |

By default, running the script writes a 1920×1080 Mandelbrot image to `image.ppm`:

```bash
python3 gen_ppm.py
./target/ppm_viewer --file image.ppm
```

To try another generator, change the call on the last line of the script. Pure-Python generation at 1920×1080 takes a little while, so smaller sizes are handy while experimenting. `image.ppm` is listed in `.gitignore`.

## Supported format

PPM is a very simple format. A P3 file is a header followed by ASCII pixel data:

```
P3
<width> <height>
<max color value>
R G B R G B ...
```

What this viewer accepts:

- **Magic number `P3` only** (plain-text). Binary `P6` files are not supported
- **Max color value from 1 to 255.** Each channel is rescaled as `value * 255 / max` (rounded), so a file with a max of 15 still displays at full brightness
- Pixels are read in row-major order, three integers each

Errors are reported for a wrong magic number, an out-of-range maximum, a sample outside `0..max`, and truncated pixel data.

### Known limitations

- Binary `P6` images are not supported
- `#` comments in the header are not handled by the parser
- Maximum color values above 255 (16-bit PPMs) are rejected
- Images are only ever scaled **down** to fit the window, never up

## Project structure

```
ppm_viewer/
├── CMakeLists.txt        # Build configuration
├── build.sh              # Convenience build/run script
├── gen_ppm.py            # Test image generator
├── include/
│   ├── pixel.hh          # Pixel: 8-bit RGB triple, converts to QColor
│   └── ppm.hh            # Ppm: parsed image, converts to QImage
├── src/
│   ├── pixel.cpp
│   └── ppm.cpp           # P3 parser and QImage conversion
├── gui/
│   ├── main.cpp          # CLI parsing, input selection, app startup
│   ├── mainwindow.h
│   └── mainwindow.cpp    # Window that displays and rescales the image
├── .clangd               # clangd / clang-tidy settings
└── license.txt           # MIT license
```

### Architecture

The code is split into two CMake targets:

- **`ppm_core`** (static library): `Pixel` and `Ppm`. `Ppm` parses a `std::istream` into a vector of pixels and can turn them into a `QImage`.
- **`ppm_viewer`** (executable): `main.cpp` handles the command line and input source, then hands a `QImage` to `MainWindow`, which shows it in a `QLabel` and re-fits it on every resize.

Both targets compile with `-Wall -Wextra -Wpedantic` on GCC and Clang. Tests are not set up yet; `CMakeLists.txt` has the `enable_testing()` hook commented out for when they are.

## Development

The repo ships a `.clangd` file configured to read `target/compile_commands.json` (which CMake generates automatically) and to enable a set of clang-tidy checks. After the first build, restart your language server so it picks up the compilation database.

## License

Released under the [MIT License](license.txt).