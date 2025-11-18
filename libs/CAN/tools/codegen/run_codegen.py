#!/usr/bin/env python3
from pathlib import Path
import subprocess

INCLUDE_DIR = Path("include/messages")
GENERATED_DIR = Path("generated/messages")
TEMPLATE = Path("tools/codegen/templates/codec_template.j2")

for header in INCLUDE_DIR.glob("*.h"):
    output_file = GENERATED_DIR / (header.stem + "_codec.h")
    output_file.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([
        "python3",
        "tools/codegen/can_msg_codegen.py",
        str(header),
        str(output_file),
        str(TEMPLATE)
    ], check=True)
