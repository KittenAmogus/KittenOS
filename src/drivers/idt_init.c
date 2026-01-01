#include "../utils/typedef.h"
#include "idt_init.h"

int __stack_chk_fail_local = 0;

extern void kb_handler( void );

struct IDT_entry IDT[ IDT_SIZE ];

void idt_init( void ) {
	uint_32 keyboard_addr;
	uint_32 idt_addr;
	// uint_64 idt_ptr[ 2 ];
	struct idt_ptr_struct idt_ptr;
	
	keyboard_addr = (uint_32)kb_handler;
	
	for ( int i=0; i<IDT_SIZE; i++ ) {
		IDT[ i ].offset_lowerbits	= 0;
		IDT[ i ].selector	= 0;
		IDT[ i ].zero	= 0;
		IDT[ i ].type_attr	= 0;
		IDT[ i ].offset_higherbits	= 0;
	}

	IDT[ 0x21 ].offset_lowerbits = keyboard_addr & 0xFFFF;
	IDT[ 0x21 ].selector = 0x08;
	IDT[ 0x21 ].zero = 0;
	IDT[ 0x21 ].type_attr = 0x8E;
	IDT[ 0x21 ].offset_higherbits = (keyboard_addr >> 16) & 0xFFFF;

	// ICW1 - begin of init
	write_port( 0x20, 0x11 );
	write_port( 0xA0, 0x11 );

	// ICW2 - remap offset addr of IDT
	write_port( 0x21, 0x20 );
	write_port( 0xA1, 0x28 );

	// ICW3 - setup cascading
	write_port( 0x21, 0x04 );	// 00
	write_port( 0xA1, 0x02 );	// 00

	// ICW4 - environment info
	write_port( 0x21, 0x01 );
	write_port( 0xA1, 0x01 );

	// mask interrupts
	write_port( 0x21, 0xFD );
	write_port( 0xA1, 0xFF );

	// fill IDT descriptor
	idt_addr = (uint_32)IDT ;
	//idt_ptr.limit = (sizeof (struct IDT_entry) * 2048) + ((idt_addr & 0xFFFF) << 16);
	idt_ptr.limit = (sizeof (struct IDT_entry) * IDT_SIZE ) - 1;
	idt_ptr.base = (unsigned int) IDT;// >> 16;

	load_idt( &idt_ptr );
}

