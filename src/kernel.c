#include "io.h"

void sleep(int ms) {
    volatile long i;
    for (i = 0; i < ms * 50000; i++) {}
}

int streq(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b)
            return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

int main() {
    print("Hello from Aether!\n");

    char cmd_buf[128];
    for (;;) {
        print("> ");
        readline(cmd_buf, sizeof(cmd_buf));
        if (streq(cmd_buf, "help")) {
            print("we aint got nothing here...\n");
        } else {
            print(cmd_buf);
            print(": command not found\n");
        }
    }

    print("\nKernel exited... (Ctrl + A -> X to exit qemu)\n");
    for (;;) {} // kernel should NEVER exit, implement ACPI or use (Ctrl + A -> X) to exit qemu
}
