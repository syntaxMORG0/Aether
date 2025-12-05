#ifndef UART_H
#define UART_H

#define UART0_BASE    0x101F1000
#define UART0_DR      ((volatile unsigned int*)(UART0_BASE + 0x00))
#define UART0_FR      ((volatile unsigned int*)(UART0_BASE + 0x18))
#define UART0_FR_TXFF (1 << 5)  /* Transmit FIFO full */
#define UART0_FR_RXFE (1 << 4)  /* Receive FIFO empty */

/* Read a character from UART (blocking) */
static inline char uart_getchar(void) {
    while (*UART0_FR & UART0_FR_RXFE);  /* Wait for data */
    return (char)(*UART0_DR & 0xFF);
}

/* Write a character to UART (blocking) */
static inline void uart_putchar(char c) {
    while (*UART0_FR & UART0_FR_TXFF);  /* Wait for space */
    *UART0_DR = (unsigned int)c;
}

#endif