/* linker.ld - Linker script for minimal ARM bare-metal kernel */

/* Entry point */
ENTRY(_start)

/* Define memory layout */
SECTIONS
{
    /* VersatilePB loads kernel at 0x10000 */
    . = 0x10000;

    /* Text section: code */
    .text : {
        *(.text*)          /* all .text sections from input files */
    }

    /* Read-only data section */
    .rodata : {
        *(.rodata*)        /* all .rodata sections */
    }

    /* Data section (initialized variables) */
    .data : {
        *(.data*)
    }

    /* BSS section (zero-initialized variables) */
    .bss : {
        __bss_start = .;   /* optional symbol for start of BSS */
        *(.bss*)
        __bss_end = .;     /* optional symbol for end of BSS */
    }
}
