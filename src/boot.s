/* boot.S - only sets up stack and jumps to main */
.global _start
.extern main

.section .text
_start:
    ldr sp, =stack_top    /* Set stack pointer */
    bl main               /* Jump to C kernel main */

hang:
    b hang

.section .bss
.align 4
stack_bottom:
    .space 4096
stack_top:
