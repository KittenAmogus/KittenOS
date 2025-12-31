[bits 32]

section .text
	; Multiboot header for GRUB
	global _start
	extern kernelMain
	
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 00)

_start:
	; Setup stack
	cli
	mov esp, stack_top
	mov ebp, stack_top
	
	call set_cpos		; Move BIOS cursor to 0, 0
	call kernelMain		; Main function of kernel, written in C
	
	; Disable anything lower
	cli
	hlt

posX db 0
posY db 0
cols equ 80

set_cpos:
	mov al, [posX]
	mov cl, cols
	mul cl
	mov bx, ax
	mov ax, [posY]
	add bx, ax
	mov cx, bx

	mov al, 0x0F
	mov dx, 0x3D4
	out dx, al
	mov ax, cx
	mov dx, 0x3D5
	out dx, al

	mov al, 0x0E
	mov dx, 0x3D4
	out dx, al
	mov ax, cx
	shr ax, 8
	mov dx, 0x3D5
	out dx, al

	ret

section .bss
	align 4

stack_bottom:
	resb 8192

stack_top:

