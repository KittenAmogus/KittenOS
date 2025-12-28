bits 16
[org 0x7C00]
	mov si, text
	call print
	
	jmp $			; if failed to load, do nothing forever

; Data
text: db "Booting KittenOS...", 10, 13, 0

; Functions
print:
	mov ah, 0x0E	; For int 0x10 - print
	.loop:
		lodsb		; Load si

		cmp al, 0	; If end of string
		je .done

		int 0x10	; Print char from al
		jmp .loop
	
	.done:
		jmp load	; Load kernel after print

load:
	cld				; Clear direction flag

	mov ax, 0		; For segment
	mov ss, ax
	mov sp, 0x7C00	; Stack from 0x07C00

	mov bx, 0x7E00
	mov es, ax		; Read sector start from 0x7E00

	mov ah, 2		; Some boot stuff
	mov al, 1
	mov ch, 0
	mov cl, 2
	mov dh, 0

	int 0x13

	jmp 0x0000:0x7E00	; Jump to sector 0x07E00

; Boot
times 510 - ($-$$) db 0	; Set size 510
dw 0xAA55				; Boot signature
