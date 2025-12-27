nasm\
	-f bin\
	-o build/boot.bin\
	src/boot/boot.s

qemu-system-x86_64\
	build/boot.bin\
	-m 256\
	-cpu pentium\
	$@

