exec >&2
: ${SDCC_FLAGS:=}
: ${CPP_FLAGS:=}
CPP_FLAGS+=" -DPIC_18F -D__SDCC -Iinclude/usb"
search_paths=". USB_stack/common"
f=
for d in $search_paths; do
  CPP_FLAGS+=" -I$d"
  if [ -z "$f" ] || ! [ -e "$f" ]; then
    f="$d/$2.c"
  fi
done

SDCC_FLAGS+=" --use-non-free -mpic16 -p18f2550 $CPP_FLAGS"

redo-ifchange $f
sdcc -E $SDCC_FLAGS $f | egrep '^#\s*[0-9]+' | sed 's/^.*"\(.*\)".*$/\1/' | sort | uniq | grep -v '^<' | xargs -d'\n' redo-ifchange

sdcc -c $SDCC_FLAGS $f -o $3

