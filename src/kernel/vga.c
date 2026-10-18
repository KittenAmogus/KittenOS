#include <kernel/vga.h>
#include <stdint.h>

static int vga_cursor = 0;
static uint16_t vga_color = VGA_DEFAULT_COLOR;

static uint16_t *vga_buffer = (uint16_t *)0xB8000;

void vga_clear(void) {
  for (int i = 0; i < VGA_SIZE; ++i) {
    vga_buffer[i] = VGA_CHAR(' ', vga_color);
  }
}

void vga_clear_row(int row) {
  for (int i = 0; i < VGA_WIDTH; ++i) {
    vga_buffer[VGA_POS(i, row)] = VGA_CHAR(' ', vga_color);
  }
}

void vga_set_cursor(int col, int row) { vga_cursor = VGA_POS(col, row); }

void vga_set_color(vga_color_e fg, vga_color_e bg) {
  vga_color = VGA_COLOR(fg, bg);
}

void vga_putc(char c) {
  switch (c) {
  case 0:
    break;

  case '\n':
    vga_cursor = ((vga_cursor / VGA_WIDTH) + 1) * VGA_WIDTH;
    break;

  case '\r':
    vga_cursor = ((vga_cursor / VGA_WIDTH) + 0) * VGA_WIDTH;
    break;

  case '\b':
    if (vga_cursor > 0) {
      --vga_cursor;
      vga_putc(' ');
      --vga_cursor;
    }
    break;

  case '\t':
    // TODO: Tabs
    break;

  default:
    vga_buffer[vga_cursor++] = VGA_CHAR(c, vga_color);
  }
}

void vga_puts(char *s) {
  while (*s != 0) {
    vga_putc(*s);
    ++s;
  }
  vga_putc('\n');
}

void vga_put(char *s, int length) {
  while (length > 0) {
    vga_putc(*s);
    ++s;
    --length;
  }
}

void vga_putat(char c, int col, int row) {
  vga_buffer[VGA_POS(col, row)] = VGA_CHAR(c, vga_color);
}
