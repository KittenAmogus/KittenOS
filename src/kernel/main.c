#include <kernel/gdt.h>
#include <kernel/idt.h>

#include <kernel/vga.h>

int kmain(int magic, void *mbi) {
  (void)mbi;

  // Check magic
  if (magic != 0x2BADB002) {
    return 1;
  }

  // Init GDT and IDT
  gdt_create();
  idt_create();

  // Clear
  vga_clear();

  // Colors
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      vga_set_color(i, j);
      vga_putat(((j < 10 ? '0' : ('A' - 10)) + j), (i << 1) + 0, j);
      vga_putat(((i < 10 ? '0' : ('A' - 10)) + i), (i << 1) + 1, j);
    }
  }

  // Hello World
  vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  vga_set_cursor(0, 16);
  vga_puts("Hello, World!");

  // VGA corners
  vga_putat('*', 79, 24);
  vga_putat('*', 79, 0);
  vga_putat('*', 0, 24);
  vga_putat('*', 0, 0);

  return 0;
}
