.section .text

.global interrupt_common_stub
interrupt_common_stub:
  // Save CPU state
  pusha
  mov %ds, %ax
  pushl %eax
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs

  // Call external interrupt handler
  pushl %esp
  call interrupt_handler
  addl $4, %esp

  // Restore CPU state
  popl %eax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss

  popa
  addl $8, %esp
  iret // Return


