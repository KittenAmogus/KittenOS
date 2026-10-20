#ifndef PMM_H
#define PMM_H

#include <mbi.h>

#define MEMMAP_TYPE_AVAIL 1
#define PAGE_SIZE 0x1000 // 4KB

#define ALIGN_HIGHER(x) ((x + (PAGE_SIZE-1)) & (~(PAGE_SIZE-1)))
#define ALIGN_LOWER(x) ((x + 0) & (~(PAGE_SIZE-1)))
#define NEXT_ENTRY(entry) ((memmap_entry_t *)((uint32_t)entry + entry->size + sizeof(memmap_entry_t)))

typedef struct {
  uint32_t size;
  uint64_t base_addr;
  uint64_t length;
  uint32_t type;
} memmap_entry_t

int pmm_init(mbi_t *mbi);       // Initialized pmm bitmap
void *pmm_alloc_page(void);     // Allocates physical page
int pmm_available_pages(void);  // Returns available pages count

#endif // PMM_H
