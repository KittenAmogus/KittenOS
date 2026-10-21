#ifndef MBI_H
#define MBI_H

#include <stdint.h>

typedef struct {
  uint32_t mem : 1;
  uint32_t boot_dev : 1;
  uint32_t cmdline : 1;
  uint32_t mods : 1;
  uint32_t symsA : 1;
  uint32_t symsB : 1;
  uint32_t mmap : 1;
  uint32_t drives : 1;
  uint32_t config : 1;
  uint32_t bootloader_name : 1;
  uint32_t apm : 1;
  uint32_t vbe : 1;
  uint32_t framebuffer : 1;
  uint32_t resv : 19;
} mbi_flags_t;

typedef struct {
  uint32_t flags;

  uint32_t mem_lower;
  uint32_t mem_upper;

  uint32_t mods_count;
  uint32_t mods_addr;

  char syms[12];

  uint32_t mmap_length;
  uint32_t mmap_addr;

  uint32_t drives_length;
  uint32_t drives_addr;

  uint32_t config_table;
  uint32_t boot_loader_name;
  uint32_t apm_table;

  struct {
    uint32_t control_info;
    uint32_t mode_info;
    uint16_t mode;
    uint16_t interface_seg;
    uint16_t interface_off;
    uint16_t interface_len;
  } __attribute__((packed)) vbm;

  struct {
    uint64_t addr;
    uint32_t pitch;
    uint32_t height;
    uint8_t bpp;
    uint8_t type;
    char color_info[6];
  } __attribute__((packed)) fb;
} __attribute__((packed)) mbi_t;

#endif // MBI_H
