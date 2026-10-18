#include <kernel/idt.h>

#define IDT_LENGTH 256

idt_entry_t IDT[IDT_LENGTH];
idt_ptr_t idt_ptr;

static void idt_load(void) { asm volatile("lidt (%0)" : : "r"(&idt_ptr)); }

static void idt_add_entry(int index, uint32_t offset, uint16_t selector,
                          uint8_t type) {
  idt_entry_t *idt = &IDT[index];
  idt->offset_low = (uint16_t)(offset & 0xFFFF);
  idt->offset_high = (uint16_t)((offset >> 16) & 0xFFFF);
  idt->selector = selector;
  idt->type = type;
  idt->zero = 0;
}

void idt_create(void) {
  // Reset IDT
  for (int i = 0; i < IDT_LENGTH; ++i) {
    idt_add_entry(i, 0, 0, 0);
  }

  // idt_add_entry(index, handler, 0x08, 0x8E); // Interrupt
  // idt_add_entry(0x80, handler, 0x08, 0xEF);  // SysCall

  // Load IDT
  idt_ptr.limit = sizeof(IDT) - 1;
  idt_ptr.base = (uint32_t)IDT;
  idt_load();
}
