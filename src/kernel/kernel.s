bits 16
org 0x0000

main:
	mov ax, 0x07E0
	mov ds, ax		; Segments
	mov es, ax
	
	call clear

	mov si, msg
	call print

	; input
	.input_loop:
		call input

		lea si, [fetch_cmd]
		lea di, [buffer]
		mov cx, 64
		
		repe cmpsb
		jne .print_fetch

		jmp .input_loop
	
	.print_fetch:
		call print_fetch
		jmp .input_loop
	
	.input_end:

	cli				; Do not execute anything lower
	hlt				;


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
	mov bx, 0
	.loop:
	lodsb

	cmp al, 0
	je .done

	mov ah, 0x0E
	int 0x10
	inc bx
	
	cmp bx, 255
	je .done

	jmp .loop
	
	.done:
		ret

clear_buffer:
	mov bx, 0
	.loop:
		mov [buffer + bx], 0
		inc bx
		
		jmp .loop
	.done:
		ret

input:
	call clear_buffer
	mov si, prompt
	call print

	mov bx, 0
	.loop:
		mov ah, 0
		int 0x16
		
		cmp ah, 0x1C
		je .done

		cmp al, 4
		je halt

		mov ah, 0x0E
		int 0x10

		mov [buffer + bx], al
		inc bx
	
		jmp .loop
	
	.done:
		mov si, newline
		call print
		ret

print_fetch:
	mov si, fetch
	call print
	ret

; Data

msg:		db "Loading kernel...", 10, 13, 0
newline:	db 10, 13, 0
prompt:		db "D:/HOME> ", 0
halt_msg:	db 10, 13, "Shutdown", 10, 13, 0

fetch:
	db "         x                                        ", 10, 13,
	db "       .$   :&&                    X&&    &       ", 10, 13,
	db "        &        &&&&&$::x$&&&&&&&        &       ", 10, 13,
	db "        &                          &     ;+       ", 10, 13,
	db "        ++   &                      &&   &        ", 10, 13,
	db "         & $&                         & $.        ", 10, 13,
	db "          &&                           &&         ", 10, 13,
	db "          &                            ;;         ", 10, 13,
	db "          &                             &         ", 10, 13,
	db "      &&+ &                             & $&&     ", 10, 13,
	db "          &                            &          ", 10, 13,
	db "                                                  ", 10, 13,
	db "           $&                         &           ", 10, 13,
	db "             &+                     &&            ", 10, 13,
	db "               &&                &&$              ", 10, 13,
	db "                  X&&&&$   +&&&&                  ", 10, 13,
	db 0
                                                  

fetch_cmd:	db "fetch"
			times 59 db 0

; Input buffer
buffer:
	times 64 db 0


halt:
	mov si, halt_msg
	call print

	mov ax, 1
	mov bx, 0
	int 0x80

