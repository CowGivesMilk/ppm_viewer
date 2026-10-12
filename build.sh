#!/usr/bin/env bash
# Build ppm_viewer with CMake.
# Usage: ./build.sh [-run] [-release] [-clean] [-args PROGRAM_ARGS...]

set -euo pipefail

cd "$(dirname "${BASH_SOURCE[0]}")"

BUILD_DIR=target
BUILD_TYPE=Debug
RUN=0
CLEAN=0
PROGRAM_ARGS=()

while [[ $# -gt 0 ]]; do
    case "$1" in
        -run)
            RUN=1
            shift
            ;;
        -release)
            BUILD_TYPE=Release
            shift
            ;;
        -clean)
            CLEAN=1
            shift
            ;;
        -args)
            shift
            PROGRAM_ARGS=("$@")
            break
            ;;
        -h|--help)
            echo "Usage: $0 [-run] [-release] [-clean] [-args PROGRAM_ARGS...]"
            echo "  -run      run ppm_viewer after a successful build"
            echo "  -release  build in Release mode (default: Debug)"
            echo "  -clean    delete the build directory first"
            echo "  -args     pass remaining arguments to ppm_viewer"
            exit 0
            ;;
        *)
            echo "Unknown option: $1 (try --help)" >&2
            exit 1
            ;;
    esac
done

if [[ $CLEAN -eq 1 ]]; then
    rm -rf "$BUILD_DIR"
fi

cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
cmake --build "$BUILD_DIR" -j"$(nproc)"

if [[ $RUN -eq 1 ]]; then
    exec "./$BUILD_DIR/ppm_viewer" "${PROGRAM_ARGS[@]}"
fi