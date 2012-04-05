exec >&2
redo-ifchange "$2.objs"

if [ -e "$2.lkr" ]; then
  redo-ifchange "$2.lkr"
  linker_flags="-Wl,-s,$2.lkr"
else
  redo-ifcreate "$2.lkr"
  linker_flags=
fi
objs="$(cat "$2.objs")"
redo-ifchange $objs
sdcc -V --use-non-free -mpic16 -p18f2550 $linker_flags $objs -llibc18f.lib -o $3.hex
cp $3.hex $3

