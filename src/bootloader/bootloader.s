org 0x7C00  ; Add 0x7C00 to label addresses
bits 16  ; Real mode

; Segments
mov ax, 0
mov ds, ax
mov es, ax
mov ss, ax ; stack
mov sp, 0x7C00 ; stack from 7C00

; =======
; main
; =======

extern clear_screen
extern print_string
extern get_command

; Clear BIOS messages
call clear_screen

; Print welcome message
mov si, welcome_msg
call print_string

loop:
	mov si, prompt
	call print_string
	call get_command
	jmp loop
end:
	jmp halt

; =======
; Calls
; =======

; Data
welcome_msg	db "Hello, user of KittenOS!", 0x0D, 0x0A, 0
bad_command	db "Unknown command", 0x0D, 0x0A , 0
halt_msg	db "Shutting down machine", 0x0D, 0x0A, 0

prompt db "~ $ ", 0
newline db 0x0D, 0x0a, 0

buffer times 64 db 0

; End

halt:
	mov si, newline
	call print_string

	mov si, halt_msg
	call print_string

	cli
	hlt


times 510-($-$$) db 0  ; Set size 510 byte
dw 0xAA55  ; add boot signature

