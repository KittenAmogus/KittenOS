call clear_screen

mov ah, 0xE
mov bx, 0

loop:
	mov al, [0x7C00 + bx + success_boot_msg]

	cmp al, 0
	je loop_end

	int 0x10
	inc bx

	jmp loop

loop_end:


jmp $

; Functions

clear_screen:
	mov ah, 0x06
	mov al, 0

	mov bh, 0x07
	mov cx, 0000
	mov dx, 0x184F
	int 0x10
	
	mov ah, 0x02
	mov bh, 0
	mov dh, 0
	mov dl, 0
	int 0x10

	ret

; Data

success_boot_msg:
	db "Hello, World!", 0

; Boot
times 510-($-$$) db 0  ; fill to 512
dw 0xAA55  ; boot signature

