exec >&2
: ${SDCC_FLAGS:=}
SDCC_FLAGS+=" -DPIC_18F"
search_paths=". USB_stack/common"
for d in $search_paths; do
  SDCC_FLAGS+=" -I$d"
  f="$d/$2.c"
  if [ -e "$f" ]; then
    break
  fi
done
redo-ifchange $f
sdcc -c --use-non-free -mpic16 -p18f2550 $SDCC_FLAGS $f -o $3
