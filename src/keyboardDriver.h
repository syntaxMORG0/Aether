// keyboard/input driver
#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stddef.h>
#include "uart.h"

char *readLine(char *buf, size_t bufSize) {
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

#endif