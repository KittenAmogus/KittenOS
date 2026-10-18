#include <kernel/io.h>

void outb(uint16_t port, uint8_t data) {
  asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void io_wait(void) { outb(0x0080, 0x00); }
