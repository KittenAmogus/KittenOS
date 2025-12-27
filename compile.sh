nasm -f bin src/kernel/kernel.asm -o build/kernel.bin
nasm -f bin src/bootloader/bootloader.s -o build/boot.bin

ld build/*.bin -o build/kittenos

qemu-system-x86_64 build/kittenos -m 256 -vga std $@
