#include "../drivers/idt_init.h"
#include "../drivers/keyboard_handler,h"
#include "../utils/stdout.h"
// #include "../utils/colors.h"

#ifndef KERNEL_H
#define KERNEL_H


extern void kb_handler( void );

extern const uint_8 *prompt;
extern const uint_8 *fetch_string;

int kernelMain( void );

#endif // KERNEL_H

