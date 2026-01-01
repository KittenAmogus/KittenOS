#include "../utils/typedef.h"

#ifndef IDT_INIT_H
#define IDT_INIT_H

#define IDT_SIZE 256

struct idt_ptr_struct {
	uint_16 limit;
	uint_32 base;
} __attribute__((packed)) ;

extern void load_idt( struct idt_ptr_struct *ptr );
extern void write_port( uint_8 a, uint_8 b );

struct IDT_entry {
	uint_16 offset_lowerbits;
	uint_16 selector;
	uint_8 zero;
	uint_8 type_attr;
	uint_16 offset_higherbits;
} __attribute__((packed)) ;

extern struct IDT_entry IDT[ IDT_SIZE ];

void idt_init( void );

#endif // IDT_INIT_H

