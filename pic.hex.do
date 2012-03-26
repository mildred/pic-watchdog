exec >&2
objs="pic.o usb_stack.o cdc.o"
redo-ifchange 18f2550.lkr $objs
sdcc --use-non-free -mpic16 -p18f2550 -Wl,-s,18f2550.lkr $objs -o $3.hex
cp $3.hex $3

