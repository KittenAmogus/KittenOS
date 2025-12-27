nasm -f bin src/bootloader/bootloader.s -o build/kernel.bin
qemu-system-x86_64 build/kernel.bin -m 256 -vga std $@
