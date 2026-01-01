#include "typedef.h"
#include "stdout.h"

volatile uint_8 *vgaMemory	= (char *) 0xB8000;

uint_16 cursorPos			= 0;
uint_8 terminalColor		= 0x02;


void setColor( const uint_8 color ) {
	terminalColor = color;
}

void setPos( const uint_8 col, const uint_8 row ) {
	cursorPos = col + (row * 80);
}


void clearScreen( void ) {
	setPos( 0, 0 );
	uint_16 i = 0;
	while ( i < 80 * 25 ) {
		printChar( ' ' );
		i++;
	}
	setPos( 0, 0 );
}

void printChar( const uint_8 ch ) {
	if ( cursorPos >= 80 * 25 )
		clearScreen();

	switch ( ch ) {
		case ('\n'): {
			cursorPos += 80;
			cursorPos -= cursorPos % 80;
			break;
		}
		case ('\r'): {
			cursorPos -= cursorPos % 80;
			break;
		}
		case ('\0'): {
			break;
		}
		case ('\b'): {
			if ( cursorPos == 0 )
				break;
			cursorPos --;
			printChar( ' ' );
			cursorPos --;
			break;
		}
		default: {
			vgaMemory[ cursorPos * 2 ] = ch;
			vgaMemory[ cursorPos * 2 + 1 ] = terminalColor;
			cursorPos ++;
			break;
		}

	}
}

void printString( const uint_8 *str ) {
	uint_16 i = 0;
	while ( str[ i ] != 0 ) {
		printChar( str[ i ] );
		i++;
	}
}

void newline( void ) {
	printString( "\n\r" );
}
