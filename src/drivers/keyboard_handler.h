
#include "../utils/typedef.h"
#include "../utils/stdout.h"

#define RING_BUFF_SIZE 256

extern uint_8 ring_buffer[ RING_BUFF_SIZE ];
extern uint_16 tail;
extern uint_16 head;

// Asm functions
extern int_8 read_port( uint_8 port );
extern void write_port( uint_8 port, uint_8 byte );

// Key mapping
extern const uint_8 keyboard_map[ 128 ];
extern const uint_8 keyboard_map_shift[ 128 ];

void on_key_pressed( void );

uint_8 getch( void );
void get_input( uint_8 *buffer );

