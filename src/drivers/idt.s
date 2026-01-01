global read_port
global write_port
global load_idt
global kb_handler

extern on_key_pressed

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	jmp $+2		; io wait
	ret

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

kb_handler:
	pushad
	call on_key_pressed
	popad
	iretd
