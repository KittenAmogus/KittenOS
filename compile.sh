# Compiling
nasm\
	-f bin\
	-o build/boot.bin\
	src/boot/boot.s

nasm\
	-f bin\
	-o build/kernel.bin\
	src/kernel/kernel.s


# Creating image
dd\
	if=build/boot.bin\
	of=hda.img\
	conv=notrunc\
	bs=512\
	conv=notrunc

dd\
	if=build/kernel.bin\
	of=hda.img\
	conv=notrunc\
	bs=512\
	conv=notrunc\
	seek=1


# Running
qemu-system-x86_64\
	hda.img\
	-m 256\
	-cpu pentium\
	$@

