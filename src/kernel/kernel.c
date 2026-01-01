#include "../utils/stdout.h"
#include "../drivers/idt_init.h"
#include "../drivers/keyboard_handler.h"
// #include "../utils/stdin.h"
// #include "../utils/global.h"

#define FETCH_LINES 14

const uint_8 *prompt = "user@kittenOS $ ";
// extern void kb_handler( void );

const uint_8 *fetch_strings[ FETCH_LINES ] = {
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

const uint_8 *help_text = (
	"HELP MENU:\n\r"
	"fetch -- fetch\n\r"
	"clear -- clear screen\n\r"
	"help -- show this menu\n\r"
);


void shutdown( void ) {
	// newline();
	printString( "System will(maybe) shutdown now!\n" );
}

bool isBuffEqualString( uint_8 *buff, uint_8 *str ) {
	for ( uint_8 i=0; i<128; i++ ) {
		if ( str[ i ] == 0 && buff[ i ] == 0 )
			return true;
		if ( str[ i ] != buff[ i ] )
			return false;
	}
	return true;
}


int kernelMain( void ) {

	setColor( 0x02 );	// Green
	clearScreen();

	idt_init();
	write_port( 0x21, 0xFD );

	while (1) {
		printString( prompt );

		uint_8 buff[ 128 ];
		get_input( buff );

		if ( isBuffEqualString( buff, "fetch" ) ) {
			for ( uint_8 i=0; i<FETCH_LINES; i++ ) {
				printString( fetch_strings[ i ] );
			}
		}

		else if ( isBuffEqualString( buff, "clear" ) ) {
			clearScreen();
		}
	
		else if ( isBuffEqualString( buff, "" ) ) {
			newline();
			continue;
		}

		else if ( isBuffEqualString( buff, "halt" ) ) {
			shutdown();
			break;
		}

		else if ( isBuffEqualString( buff, "help" ) ) {
			printString( help_text );
		}

		else {
			printString( "Unknown Command\n\r" );
		}
	}

	return 0;
}


