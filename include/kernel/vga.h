#ifndef KERNEL_VGA_H
#define KERNEL_VGA_H

typedef enum {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
} vga_color_e;

#define VGA_COLOR(fg, bg) ((uint16_t)((uint8_t)fg | ((uint8_t)bg << 4)))
#define VGA_CHAR(ch, col) ((uint16_t)ch | ((uint16_t)col << 8))

#define VGA_DEFAULT_COLOR VGA_COLOR(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK)

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_SIZE (VGA_WIDTH * VGA_HEIGHT)
#define VGA_POS(x, y) (y * VGA_WIDTH + x)

void vga_clear(void);
void vga_clear_row(int row);
void vga_set_cursor(int col, int row);
void vga_set_color(vga_color_e fg, vga_color_e bg);

void vga_putc(char c);
void vga_puts(char *s);
void vga_put(char *s, int length);
void vga_putat(char c, int col, int row);

#endif // KERNEL_VGA_H
