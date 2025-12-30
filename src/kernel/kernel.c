#include "../utils/stdout.h"

const uint_8 *prompt = "user@kittenOS $ ";

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
	setColor( 0x02 );	// Green
	clearScreen();
	
	for ( uint_8 i=0; i<15; i++ ) {
		printString( fetch_strings[ i ] );
	}
	printString( prompt );

	return 0;
}

