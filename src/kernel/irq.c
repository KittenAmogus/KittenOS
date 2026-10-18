#include <kernel/irq.h>
#include <kernel/vga.h>

const char *err_strings[] = {
    "Divizion by 0",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Out of bounds",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "[RESERVED 0x0F]",
    "x87 Floating point error",
    "[RESERVED 0x11]",
    "[RESERVED 0x12]",
    "[RESERVED 0x13]",
    "[RESERVED 0x14]",
    "[RESERVED 0x15]",
    "[RESERVED 0x16]",
    "[RESERVED 0x17]",
    "[RESERVED 0x18]",
    "[RESERVED 0x19]",
    "[RESERVED 0x1A]",
    "[RESERVED 0x1B]",
    "[RESERVED 0x1C]",
    "[RESERVED 0x1D]",
    "[RESERVED 0x1E]",
    "[RESERVED 0x1F]",
};

#define TOCHAR(i) (i < 10 ? '0' + i : 'A' - 10 + i)

void interrupt_handler(registers_t *regs) {
  if (regs->int_no < 32) {
    vga_puts(err_strings[regs->int_no]);
  } else {
    vga_put("IRQ 0x", 6);
    vga_putc(TOCHAR(((regs->int_no >> 4) & 0x0F)));
    vga_putc(TOCHAR(((regs->int_no >> 0) & 0x0F)));
    vga_putc('\n');
  }
}
