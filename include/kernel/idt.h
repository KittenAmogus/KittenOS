#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t type;
  uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;

typedef struct {
  uint8_t _bytes0[3];
  uint8_t num;
  uint8_t _bytes1[1];
  int32_t jmp_offset;
  uint8_t _bytes2[1];
} __attribute__((packed)) idt_trampoline_t;

void idt_create(void);

#endif // IDT_H
