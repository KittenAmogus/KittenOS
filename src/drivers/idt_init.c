#include "../utils/typedef.h"
#include "idt_init.h"

int __stack_chk_fail_local = 0;

extern void kb_handler( void );

struct IDT_entry IDT[ 2048 ];

void idt_init( void ) {
	uint_64 keyboard_addr;
	uint_64 idt_addr;
	uint_64 idt_ptr[ 2 ];
	
	keyboard_addr = (uint_64)kb_handler;
	IDT[ 0x21 ].offset_lowerbits = keyboard_addr & 0xFFFF;
	IDT[ 0x21 ].selector = 0x08;
	IDT[ 0x21 ].zero = 0;
	IDT[ 0x21 ].type_attr = 0x8E;
	IDT[ 0x21 ].offset_higherbits = (keyboard_addr & 0xFFFF0000) >> 16;

	// ICW1 - begin of init
	write_port( 0x20, 0x11 );
	write_port( 0xA0, 0x11 );

	// ICW2 - remap offset addr of IDT
	write_port( 0x21, 0x20 );
	write_port( 0xA1, 0x28 );

	// ICW3 - setup cascading
	write_port( 0x21, 0x00 );
	write_port( 0xA1, 0x00 );

	// ICW4 - environment info
	write_port( 0x21, 0x01 );
	write_port( 0xA1, 0x01 );

	// mask interrupts
	write_port( 0x21, 0xFF );
	write_port( 0xA1, 0xFF );

	// fill IDT descriptor
	idt_addr = (uint_64)IDT ;
	idt_ptr[ 0 ] = (sizeof (struct IDT_entry) * 2048) + ((idt_addr & 0xFFFF) << 16);
	idt_ptr[ 1 ] = idt_addr >> 16;

	load_idt( idt_ptr );
}

