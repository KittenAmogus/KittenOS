bits 16

[org 0x7C00]
	mov ax, 0
	mov ds, ax
	mov es, ax
	
	call clear

	mov si, fetch_lines
	call print

	.loop:
		call input
		jmp .loop

	jmp halt

; Constants

welcome_message	db "Hello, World", 0x0D, 0x0A, 0
prompt			db "D:/> ", 0
newline			db 0x0D, 0x0A, 0
interrupt_msg	db "^C", 0x0D, 0x0A, 0
halt_msg		db 0x0D, 0x0A, "exit", 0x0D, 0x0A, 0

fetch_lines:
	db "         <>                   ", 0x0D, 0x0A
	db "         /\                   ", 0x0D, 0x0A
	db "        /..\         NEW YEAR!", 0x0D, 0x0A
	db "       /....\          2026   ", 0x0D, 0x0A
	db "      /......\                ", 0x0D, 0x0A
	db "     /........\               ", 0x0D, 0x0A
	db "    /..........\              ", 0x0D, 0x0A
	db "   /............\             ", 0x0D, 0x0A
	db "  /..............\            ", 0x0D, 0x0A
	db " /................\           ", 0x0D, 0x0A,
	db "                              ", 0x0D, 0x0A, 0

; Functions

clear:
	mov ah, 0x07
	mov al, 0
	mov bh, 0x07
	mov cx, 0x0000
	mov dx, 0x184F
	int 0x10

	mov ah, 0x02
	mov bh, 0
	mov dh, 0
	mov dl, 0
	int 0x10

	ret

print:
	lodsb		; load from si
	
	cmp al, 0
	je .done

	mov ah, 0x0E
	int 0x10
	jmp print

	.done:
		ret

input:
	mov si, prompt
	call print

	.loop:
		mov ah, 0
		int 0x16

		cmp ah, 1Ch	; ENTER
		je .done

		cmp al, 3	; ^C
		je .int

		cmp al, 4	; ^D
		je halt

		mov ah, 0x0E
		int 0x10

		jmp .loop
	.done:
		mov si, newline
		call print
		ret
	.int:
		mov si, interrupt_msg
		call print
		ret

; Stack

stack:

halt:
	mov si, halt_msg
	call print
	cli
	hlt

; Boot
times 510-($-$$) db 0
dw 0xAA55

