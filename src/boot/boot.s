bits 16

[org 0x7C00]
	mov ax, 0
	mov ds, ax
	mov es, ax
	
	call clear

	mov si, welcome_message
	call print

	jmp halt

; Constants

welcome_message	db "Hello, World", 00

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

; Stack

halt:
	cli
	hlt

; Boot
times 510-($-$$) db 0
dw 0xAA55

