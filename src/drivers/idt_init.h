#include "../utils/typedef.h"

#ifndef IDT_INIT_H
#define IDT_INIT_H

extern void load_idt( uint_64 *ptr );
extern void write_port( uint_8 a, uint_8 b );

struct IDT_entry {
	uint_16 offset_lowerbits;
	uint_16 selector;
	uint_8 zero;
	uint_8 type_attr;
	uint_16 offset_higherbits;
};

extern struct IDT_entry IDT[ 2048 ];

void idt_init( void );

#endif // IDT_INIT_H

