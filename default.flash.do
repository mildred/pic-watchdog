exec >&2
redo-ifchange objs/$2.hex
pk2cmd -PPIC18F2550 -Fobjs/$2.hex -M -I -T
