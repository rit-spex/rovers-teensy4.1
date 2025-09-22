#!/usr/bin/env bash
# run-tidy.sh — run clang-tidy across all subprojects
# Skips anything under .platformio/ or packages/

set -euo pipefail

CLANG_TIDY_ARGS="-checks=*"

for db in $(find . -name 'compile_commands.json'); do
    projdir=$(dirname "$db")
    echo ">>> Running clang-tidy in $projdir"

    # Find source & header files, pruning .platformio and packages
    find "$projdir" \
        -type d \( -name '.platformio' -o -name 'packages' \) -prune -false -o \
        -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.h' -o -name '*.hpp' \) \
        | while read -r file; do
            echo "  Checking $file"
            clang-tidy $CLANG_TIDY_ARGS -p "$projdir" "$file" || true
        done
done
