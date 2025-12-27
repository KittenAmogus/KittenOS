bits 16

extern halt

get_command:
	; Prompt to command
	.loop:
		mov ah, 0
		int 0x16

		cmp al, 0x03
		je .int

		cmp al, 0x04
		je halt

		cmp ah, 0x1C
		je .done

		mov ah, 0x0E
		int 0x10

		jmp .loop

	.done:	; Return command
		mov si, newline
		call print_string
		ret
	.int:	; Interrupted with ^C, empty command
		mov si, newline
		call print_string
		ret

clear_screen:
	mov ah, 0x06	; Scroll up
	mov al, 0		; Lines to scroll
	mov bh, 0x07	; White on black
	mov cx, 0x0000	; Left up
	mov dx, 0x184F	; Right bottom
	int 0x10

	mov ah, 02		; Set cursor position
	mov bh, 0		; Page number (0 - graphics)
	mov dh, 0		; first column
	mov dl, 0		; first row
	int 0x10

	ret
	

print_string:
	lodsb ; load from si

	or al, al
	jz .done

	mov ah, 0x0E
	int 0x10

	jmp print_string

	.done:
		ret


newline db 0x0D, 0x0A, 0


