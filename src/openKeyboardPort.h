#ifndef OPEN_KEYBOARD_PORT_H
#define OPEN_KEYBOARD_PORT_H

#include <stdint.h>
#include <stdbool.h>

static const char scancode_set1[] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0, '\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '
};

static volatile char last_char = 0;

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

__attribute__((unused))
static void keyboard_handler(void) {
    uint8_t sc = inb(0x60);

    // Ignore break codes (key releases)
    if (sc & 0x80)
        return;

    if (sc < sizeof(scancode_set1))
        last_char = scancode_set1[sc];
}

static char keyboard_getchar(void) {
    char c;
    while ((c = last_char) == 0)
        ;
    last_char = 0;
    return c;
}

#endif
