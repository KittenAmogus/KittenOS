// Constants
.set MODULEALIGN, 1 << 0
.set MEMINFO, 1 << 1
.set FLAGS, (MODULEALIGN | MEMINFO)
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

// Multiboot
.section .multiboot
.align 4
  .long MAGIC
  .long FLAGS
  .long CHECKSUM

// Stack
.section .bss
.align 16
stack_bottom:
  .skip 16384
stack_top:

// Entry
.section .text
.global _start
.global kmain

_start:
  // Setup stack
  mov $stack_top, %esp

  // GRUB parameters
  push %ebx // Multiboot info pointer
  push %eax // Magic

  // Call kernel main
  call kmain

  // After kmain end
.Lhang:
  cli
  hlt
  jmp .Lhang

