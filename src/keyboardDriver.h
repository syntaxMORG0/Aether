// keyboard driver
#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stddef.h>
#include "uart.h"

static void putchar(char c) {
    while (*UART0_FR & UART0_FR_TXFF);
    *UART0_DR = (unsigned int)c;
}

char *readLine(char *buf, size_t bufSize) {
    size_t len = 0;
    
    while (1) {
        char c = keyboard_getchar();  // blocking read

        // ENTER → finish line
        if (c == '\n' || c == '\r') {
            putchar('\n');
            buf[len] = '\0';   // null terminate
            return buf;
        }
    
        // BACKSPACE
        if (c == '\b' || c == 127) {
            if (len > 0) {
                len--;
                putchar('\b');
                putchar(' ');
                putchar('\b');
            }
            continue;
        }
    
        // normal characters
        if (len < bufSize - 1) {
            buf[len++] = c;
            putchar(c);
        }
    }
}

#endif