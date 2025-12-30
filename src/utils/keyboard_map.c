#include "keyboard_map.h"


uint_8 keymap_pressed[4] = {
	'0', '\\', '1', '2'
};


uint_8 getCharPress( int_8 keycode ) {
	if ( keycode < 4 )
		return keymap_pressed[ keycode ];
	return 'p';
}

uint_8 getCharRelease( int_8 keycode ) {
	return 'r';
}

