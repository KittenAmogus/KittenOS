#include "../utils/stdout.h"
#include "../drivers/idt_init.h"
#include "../utils/stdin.h"

const uint_8 *prompt = "user@kittenOS $ ";
extern void kb_handler( void );

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
	idt_init();

	setColor( 0x02 );	// Green
	clearScreen();

	for ( uint_8 i=0; i<15; i++ ) {
		printString( fetch_strings[ i ] );
	}
	printString( prompt );

	kb_handler();

	return 0;
}


