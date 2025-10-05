#!/usr/bin/env bash
# format.sh - format all C++ files with clang-format, ignoring git-ignored files

STYLE="file"  # uses .clang-format if present, otherwise LLVM
CLANG_FORMAT=$(command -v clang-format-20 || command -v clang-format)

# Get all tracked + unignored files, then filter for C++ extensions
git ls-files -co --exclude-standard \
  | grep -E '\.(cpp|cc|cxx|hpp|h)$' \
  | while read -r file; do
    echo "Formatting $file"
    ${CLANG_FORMAT} -i -style="$STYLE" "$file"
    dos2unix "$file"
done
