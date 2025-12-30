#include "keyboard_map.h"
#include "typedef.h"
#include "../drivers/keyboard_handler.h"
#include "stdin.h"

uint_8 getch( void ) {
	/*keyboard_init();
	int_8 scancode = getKeycode();
	if (scancode < 0)
		return getCharRelease( scancode );
	else if (scancode > 0)
		return getCharPress( scancode );*/
	return 'z';
}

