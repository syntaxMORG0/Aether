#define UART0_BASE   0x101F1000
#define UART0_DR     ((volatile unsigned int*)(UART0_BASE + 0x00))
#define UART0_FR     ((volatile unsigned int*)(UART0_BASE + 0x18))
#define UART0_FR_TXFF (1 << 5)