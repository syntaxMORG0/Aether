//#include "io.h"
#include "uart.h"
#include "keyboardDriver.h"

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

void sleep(int ms) {
    volatile long i;
    for (i = 0; i < ms * 50000; i++) {}
}

int main() {
    print("Hello from Aether!\n");

    print("\nEnter your name: ");
    char buffer[100];
    readLine(buffer, sizeof(buffer));

    print("You entered: ");
    print(buffer);
    print("\n");

    while(1) {} // kernel should NEVER exit, implement ACPI or use (Ctrl + A -> X) to exit qemu
}
