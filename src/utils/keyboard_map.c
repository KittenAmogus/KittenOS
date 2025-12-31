#include "keyboard_map.h"


uint_8 keymap_pressed[
	2 +
	14 +
	14 +
	11 +
	13 +
	5 +
	12
] = {
	'\0', '\0',																// 2
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\0', '\0',	// 14
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0',	// 14
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',					// 11
	'`', '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',		// 13
	'0', '1', '\0', ' ', '\0', // 5
	'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F' // F-symbols
};


uint_8 getCharPress( int_8 keycode ) {
	// if ( keycode < keymap_len )
		return keymap_pressed[ keycode ];
	return 'p';
}

uint_8 getCharRelease( int_8 keycode ) {
	return 'r';
}

