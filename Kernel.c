#include <stdio.h>
#include <windows.h>

#include "injector.h"
#include "kernel.h"

#define T 5

void kernel_init(void) {
    printf("[KERNEL] Scheduler online\n");
}

void kernel_handle(Event event) {

    if (event.type == EVENT_S1_THRESHOLD) {
        printf("[KERNEL] S1 threshold reached at %.2f C\n", event.temp);
        Inject_Trait();
        return;
    }

    if (event.type == EVENT_S2_THRESHOLD) {
        printf("[KERNEL] S2 threshold reached at %.2f C\n", event.temp);

        Inject_Trait();
        printf("[KERNEL] Cooldown engaged for %d seconds\n", T);
        Sleep(T * 1000);
        Inject_Trait();
    }
}
