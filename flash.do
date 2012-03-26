exec >&2
redo-ifchange pic.hex
pk2cmd -PPIC18F2550 -Fpic.hex -M -I -T
