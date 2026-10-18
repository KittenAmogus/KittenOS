#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

typedef struct {
  uint32_t ds; // Data segment

  uint32_t edi;
  uint32_t esi;
  uint32_t ebp;
  uint32_t esp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;

  uint32_t int_no;   // Interrupt number
  uint32_t err_code; // Error code

  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
  uint32_t useresp;
  uint32_t ss;
} __attribute__((packed)) registers_t;

extern void interrupt_common_stub(void);
void interrupt_handler(registers_t *regs);

#endif // IRQ_H
