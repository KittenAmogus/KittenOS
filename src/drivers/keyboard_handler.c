#include "../utils/stdout.h"
#include "../utils/typedef.h"
#include "../utils/global.h"
#include "keyboard_handler.h"

uint_8 ring_buffer[ RING_BUFF_SIZE ];
uint_16 head = 0;
uint_16 tail = 0;

// extern int_8 read_port( uint_8 port );
// extern void write_port( uint_8 a, uint_8 b );

const uint_8 keyboard_map[ 128 ] = {
	0, 21, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '.', ',', '/', 0, '*', 0, ' '
};

const uint_8 keyboard_map_shift[ 128 ] = {
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0,
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};


void on_key_pressed( void ) {
	// End Of Interrupt
	write_port( 0x20, 0x20 );

	uint_8 status = read_port( 0x64 );
	if ( ! (status & 0x01) )
		return;
	
	int_8 scancode = read_port( 0x60 );
	
	if ( scancode < 0 ) {	
		if ( (uint_8)scancode == 0xAA || (uint_8)scancode == 0xB6 )
			isShiftPressed = false;
		return;
	}
	
	if ( scancode == 0x2A || scancode == 0x36 ) {
		isShiftPressed = true;
		return;
	}
	
	uint_8 ascii = isShiftPressed ? keyboard_map_shift[ scancode ] : keyboard_map[ scancode ];

	if ( ascii != 0 ) {
		uint_16 next = (head + 1) % RING_BUFF_SIZE;
		if (next != tail) {
			ring_buffer[head] = ascii;
			head = next;
		}
	}
}


uint_8 getch( void ) {
	if ( head == tail )
		return 0;
	
	uint_8 ch = ring_buffer[ tail ];
	tail = (tail + 1) % RING_BUFF_SIZE;
	return ch;
}

void get_input( uint_8 *buffer ) {
	uint_16 i = 0;

	while (1) {
		asm volatile ("hlt");
	
		uint_8 ch = getch();
		if ( ch == 0 )
			continue;

		if ( ch == '\n' ) {
			if ( i > 0 )
				printChar( '\n' );
			buffer[ i ] = 0;
			return;
		}

		if ( ch == '\b' ) {
			if ( i > 0 ) {
				i--;
				printChar( '\b' );
			}
			continue;
		}
		printChar( ch );
		buffer[ i++ ] = ch;
	}
}

