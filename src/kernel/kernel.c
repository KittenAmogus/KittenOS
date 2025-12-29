#include "../utils/stdout.h"

const uint_8 *fetch_strings[ 15 ] = {"\n\r",
     "                  ______                  \n\r",
     "               .-\"      \"-.               \n\r",
     "              /            \\              \n\r",
     "  _          |              |          _  \n\r",
     " ( \\         |,  .-.  .-.  ,|         / ) \n\r",
     "  > \"=._     | )(__/  \\__)( |     _.=\" <  \n\r",
     " (_/\"=._\"=._ |/     /\\     \\| _.=\"_.=\"\\_) \n\r",
     "        \"=._ (_     ^^     _)\"_.=\"        \n\r",
     "            \"=\\__|IIIIII|__/=\"            \n\r",
     "           _.=\"| \\IIIIII/ |\"=._           \n\r",
     " _     _.=\"_.=\"\\          /\"=._\"=._     _ \n\r",
     "( \\_.=\"_.=\"     `--------`     \"=._\"=._/ )\n\r",
     " > _.=\"                            \"=._ < \n\r",
     "(_/                                    \\_)\n\r"
};


int kernelMain( void ) {
	setColor( 0x00 + 0x04 + 0x80 );
	clearScreen();
	
	for ( uint_8 i=0; i<2; i++ ) {
		printString( "\n\r" );
	}
	for ( uint_8 i=0; i<15; i++ ) {
		for ( uint_8 j=0; j<(80 - 43) / 2; j++ ) {
			printChar( ' ' );
		}
		printString( fetch_strings[ i ] );
	}

	/*
	for ( uint_8 row=0; row<16; row++ ) {
		for (uint_8 col=0; col<16; col++ ) {
			setColor( row * 16 + col );
			printChar( (char)(0x41 + col) );
		}
		printString( "\n\r" );
	}
	*/

	return 0;
}

