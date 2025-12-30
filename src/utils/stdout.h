#include "typedef.h"

#ifndef STDOUT_H
#define STDOUT_H

extern volatile uint_8 *vgaMemory;

extern uint_16 cursorPos;

extern uint_8 color;


void setColor( const uint_8 color );
void setPos( const uint_8 col, const uint_8 row );
void clearScreen( void );
void printChar( const uint_8 ch );
void printString( const uint_8 *str );
void newline( void );

#endif // STDOUT_H

