#include "../utils/stdout.h"
#include "../drivers/idt_init.h"
#include "../drivers/keyboard_handler.h"
#include "../utils/stdin.h"
#include "../utils/global.h"

const uint_8 *prompt = "user@kittenOS $ ";
// extern void kb_handler( void );

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
	
	idt_init();
	write_port( 0x21, 0xFD );
	printString( prompt );

	while (1) {
		asm volatile ( "hlt" );
		if ( inputBufferLen >= 1 )
			printChar( getCharPress(
				inputBuffer[ --inputBufferLen ] )
			);
	}

	return 0;
}


