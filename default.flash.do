exec >&2
redo-ifchange $2.hex
pk2cmd -PPIC18F2550 -F$2.hex -M -I -T
