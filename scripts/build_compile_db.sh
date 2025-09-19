#!/usr/bin/sh
set -euo pipefail

# Root folder containing all subprojects
ROOT_DIR="$(pwd)"

# Find all subprojects (dirs containing platformio.ini)
SUBPROJECTS=$(find "$ROOT_DIR" -type f -name "platformio.ini" -exec dirname {} \;)

for proj in $SUBPROJECTS; do
    echo "📦 Building compile_commands.json for: $proj"

    pushd "$proj" > /dev/null

    # Make sure .pio is clean
    pio run -t clean

    # Generate compile_commands.json
    pio run -t compiledb

    # Ensure file ends up at project root (some versions put it in .pio/build/*)
    if [ -f "compile_commands.json" ]; then
        echo "✅ compile_commands.json generated in $proj"
    else
        # Collect the first one from .pio/build/*/
        DB=$(find .pio/build -name "compile_commands.json" | head -n1)
        if [ -n "$DB" ]; then
            cp "$DB" "$proj/compile_commands.json"
            echo "✅ compile_commands.json copied to $proj"
        else
            echo "⚠️  Could not find compile_commands.json in $proj"
        fi
    fi

    popd > /dev/null
done

echo "🎉 All subprojects processed!"