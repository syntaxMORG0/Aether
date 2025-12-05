#include "io.h"

void sleep(int ms) {
    volatile long i;
    for (i = 0; i < ms * 50000; i++) {}
}

int main() {
    print("Hello from Aether!\n");

    print("\nEnter your name: ");
    char buffer[100];
    readline(buffer, sizeof(buffer));

    print("You entered: '");
    print(buffer);
    print("'\n");

    print("\nKernel exited... (Ctrl + A -> X to exit qemu)\n");
    while(1) {} // kernel should NEVER exit, implement ACPI or use (Ctrl + A -> X) to exit qemu
}
