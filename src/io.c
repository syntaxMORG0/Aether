#include "io.h"
#include "uart.h"

void print(const char *s) {
    while (*s) {
        while (*UART0_FR & UART0_FR_TXFF);  // wait for space in FIFO
        *UART0_DR = *s++;
    }
}

void print_num(long num) {
    char buffer[20];
    int i = 0;

    if (num == 0) {
        return;
    }

    if (num < 0) {
        num = -num;
    }

    // convert number to string in reverse
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // print digits in correct order
    for (int j = i - 1; j >= 0; j--) {
        char c[2] = {buffer[j], '\0'};
        print(c);
    }
}

char *readline(char *buf, size_t bufSize) {
    size_t len = 0;

    while (1) {
        char c = uart_getchar();  // blocking read from UART

        // ENTER → finish line
        if (c == '\n' || c == '\r') {
            uart_putchar('\n');
            buf[len] = '\0';   // null terminate
            return buf;
        }

        // BACKSPACE
        if (c == '\b' || c == 127) {
            if (len > 0) {
                len--;
                uart_putchar('\b');
                uart_putchar(' ');
                uart_putchar('\b');
            }
            continue;
        }

        // normal characters
        if (len < bufSize - 1) {
            buf[len++] = c;
            uart_putchar(c);  // echo character
        }
    }
}