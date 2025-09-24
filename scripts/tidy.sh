#!/usr/bin/env bash
# check.sh - run PlatformIO static analysis (pio check) in all subprojects

set -euo pipefail

# Verify PlatformIO CLI is installed
if ! command -v platformio >/dev/null 2>&1; then
    echo "❌ Error: platformio (pio) is not installed or not in PATH."
    echo "   Install with: pip install platformio"
    exit 1
fi

ROOT_DIR="$(pwd)"

# Find all subprojects (directories containing platformio.ini)
SUBPROJECTS=$(find "$ROOT_DIR" -type f -name "platformio.ini" -exec dirname {} \;)

if [ -z "$SUBPROJECTS" ]; then
    echo "⚠️  No PlatformIO projects found under $ROOT_DIR"
    exit 0
fi

for proj in $SUBPROJECTS; do
    echo "🔍 Running 'pio check' in: $proj"
    (
        cd "$proj"
        platformio check || {
            echo "❌ pio check failed in $proj"
            exit 1
        }
    )
done

echo "✅ All PlatformIO projects checked successfully."
