#include "../utils/typedef.h"
#include "../utils/global.h"
#include "keyboard_handler.h"

extern int_8 read_port( uint_8 port );
extern void write_port( uint_8 a, uint_8 b );


void keyboard_handler_main( void ) {
	uint_8 status;
	int_8 keycode;
	write_port( 0x20, 0x20 );

	status = read_port( 0x64 );
	if ( status & 0x01 ) {
		keycode = read_port( 0x60 );
		if ( keycode > 0 ) {
			if ( inputBufferLen < 64 )
				inputBuffer[ inputBufferLen++ ] = keycode;
		}
		else {
			// inputBuffer[ inputBufferLen++ ] = -keycode;
		}
	}
}

