#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct {
  uint16_t limit_low;       // 0-15
  uint16_t base_low;        // 16-31
  uint8_t base_mid;         // 32-39
  uint8_t access;           // 40-47
  uint8_t flags_limit_high; // 48-55
  uint8_t base_high;        // 56-63
} __attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_create(void);

#endif // GDT_H
