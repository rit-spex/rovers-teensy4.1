#!/usr/bin/env python3
import sys
import os
from pathlib import Path
from clang.cindex import Index, CursorKind
from jinja2 import Template, Environment, FileSystemLoader

def pascal_to_snake(s):
    import re
    words = re.findall(r'[A-Z][a-z0-9]*', s)
    return "_".join(w.upper() for w in words)

if len(sys.argv) != 4:
    print("Usage: can_codegen.py <header_file> <output_file> <template_file>")
    sys.exit(1)

HEADER_FILE = Path(sys.argv[1])
OUTPUT_FILE = Path(sys.argv[2])
TEMPLATE_FILE = Path(sys.argv[3])

# Setup Jinja2 environment with filter
env = Environment(loader=FileSystemLoader(TEMPLATE_FILE.parent))
env.filters['pascal_to_snake'] = pascal_to_snake
template = env.get_template(TEMPLATE_FILE.name)

# Parse header
index = Index.create()
tu = index.parse(str(HEADER_FILE), args=['-x', 'c++', '-std=c++17'])

MESSAGES = []
FIELDS = {}
TYPES = {}

for c in tu.cursor.get_children():
    if c.kind == CursorKind.STRUCT_DECL and c.spelling.endswith("Msg"):
        msg_name = c.spelling
        MESSAGES.append(msg_name)
        FIELDS[msg_name] = []
        TYPES[msg_name] = []
        for f in c.get_children():
            if f.kind == CursorKind.FIELD_DECL:
                FIELDS[msg_name].append(f.spelling)
                TYPES[msg_name].append(f.type.spelling)

# DLC header optional
DLC_HEADER = None  # or "generated/messages/science_constants.h"

# Render template
rendered = template.render(
    STRUCT_HEADER=str(os.path.relpath(HEADER_FILE, OUTPUT_FILE.parent)),
    DLC_HEADER=DLC_HEADER,
    MESSAGES=MESSAGES,
    FIELDS=FIELDS,
    TYPES=TYPES
)

# Ensure output folder exists
OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)

# Write generated header
with open(OUTPUT_FILE, "w") as f:
    f.write(rendered)

print(f"Generated {OUTPUT_FILE}")
