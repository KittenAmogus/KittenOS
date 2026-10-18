#include <kernel/gdt.h>

#define GDT_LENGTH 5

gdt_entry_t GDT[GDT_LENGTH];
static gdt_ptr_t gdt_ptr;

static void gdt_load(void) {
  // Load pointer
  asm volatile("lgdt (%0)" : : "r"((uint32_t)&gdt_ptr));

  // Reset registers
  asm volatile("mov $0x10, %%ax\n\t"
               "mov %%ax, %%ds\n\t"
               "mov %%ax, %%es\n\t"
               "mov %%ax, %%fs\n\t"
               "mov %%ax, %%gs\n\t"
               "mov %%ax, %%ss\n\t"
               :
               :
               : "ax");

  // Long jump
  asm volatile("ljmpl $0x08, $1f\n\t"
               "1:\n\t");
}

static void gdt_add_entry(int index, uint32_t base, uint32_t limit,
                          uint8_t access, uint8_t flags) {
  gdt_entry_t *gdt = &GDT[index];
  gdt->limit_low = (uint16_t)(limit & 0xFFFF);
  gdt->flags_limit_high = (uint8_t)(((limit >> 16) & 0xF) | (flags << 4));
  gdt->base_low = (uint16_t)(base & 0xFFFF);
  gdt->base_mid = (uint8_t)((base >> 16) & 0xFF);
  gdt->base_high = (uint8_t)((base >> 24) & 0xFF);
  gdt->access = access;
}

void gdt_create(void) {
  // Create GDT
  gdt_add_entry(0, 0, 0, 0, 0);                  // NULL
  gdt_add_entry(1, 0, 0xFFFFF, 0b10011010, 0xC); // Kernel code
  gdt_add_entry(2, 0, 0xFFFFF, 0b10010010, 0xC); // Kernel data
  gdt_add_entry(3, 0, 0xFFFFF, 0b11111010, 0xC); // User code
  gdt_add_entry(4, 0, 0xFFFFF, 0b11110010, 0xC); // User data

  // Load GDT
  gdt_ptr.limit = sizeof(GDT) - 1;
  gdt_ptr.base = (uint32_t)GDT;
  gdt_load();
}
