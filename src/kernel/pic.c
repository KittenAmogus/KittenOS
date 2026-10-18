#include <kernel/io.h>
#include <kernel/pic.h>

void pic_remap(void) {
  // Save masks
  /*uint8_t p21, pA1;
  p21 = inb(0x21);
  pA1 = inb(0xA1);*/

  // ICW1
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  io_wait();

  // ICW2
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  io_wait();

  // ICW3
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  io_wait();

  // ICW4
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  io_wait();

  // Return saved
  outb(0x21, 0x11);
  outb(0xA1, 0xFF);
  io_wait();

  // Enable interrupts
  asm volatile("sti");
}
