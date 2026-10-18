#include <kernel/idt.h>
#include <kernel/irq.h>
#include <kernel/vga.h>

#define IDT_LENGTH 256

// Stack smash dummy
uint32_t __stack_chk_guard = 0xDEADC0DE;

__attribute__((noreturn)) void __stack_chk_fail(void) {
  vga_puts("KERNEL PANIC: STACK SMASHING DETECTED!");
  while (1) {
    asm volatile("hlt");
  }
}

static idt_trampoline_t idt_trampolines[IDT_LENGTH]
    __attribute__((aligned(16)));

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

  idt_trampoline_t trmp_err = {
      ._bytes0 = {0x90, 0x90, 0x6A},
      .num = 0,
      ._bytes1 = {0xE9},
      .jmp_offset = 0,
      ._bytes2 = {0x90},
  };

  idt_trampoline_t trmp_noerr = {
      ._bytes0 = {0x6A, 0x00, 0x6A},
      .num = 0,
      ._bytes1 = {0xE9},
      .jmp_offset = 0,
      ._bytes2 = {0x90},
  };

  uint32_t cs_addr = (uint32_t)interrupt_common_stub;

  // Check if math is valid
  _Static_assert(sizeof(idt_trampoline_t) == 10,
                 "Trampoline structure size must be exactly 10 bytes!");
  // Fill IDT
  for (int i = 0; i < IDT_LENGTH; ++i) {
    uint8_t type = 0x8E;
    uint32_t t_addr = (uint32_t)&idt_trampolines[i];

    if (i == 0x80)
      type = 0xEF; // Syscall

    idt_trampoline_t *trmp = &idt_trampolines[i];
    if (i == 8 || (i >= 10 && i <= 14)) {
      *trmp = trmp_err;
    } else {
      *trmp = trmp_noerr;
    }
    trmp->num = i;
    trmp->jmp_offset = cs_addr - t_addr - 9;

    idt_add_entry(i, t_addr, 0x08, type);
  }

  // Load IDT
  idt_ptr.limit = sizeof(IDT) - 1;
  idt_ptr.base = (uint32_t)IDT;
  idt_load();
}
