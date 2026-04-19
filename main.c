#include <stdio.h>

#include "serial.h"
#include "kernel.h"
#include "sensors.h"

int main() {
    HANDLE serial_handle;
    char buffer[100];

    printf("[BOOT] Starting MeasureOS_2...\n");
    printf("[BOOT] Initializing device drivers...\n");
    serial_handle = serial_open();

    printf("[BOOT] Initializing sensor subsystem...\n");
    sensors_init(0.0f);

    printf("[BOOT] Starting kernel services...\n");
    kernel_init();

    printf("[BOOT] System ready. Waiting for temperature frames...\n");

    while (1) {
        Event event;

        if (!serial_read_line(serial_handle, buffer, sizeof(buffer))) {
            continue;
        }

        event = parse_temperature(buffer);
        if (event.type != EVENT_NONE) {
            kernel_handle(event);
        }
    }

    serial_close(serial_handle);
    return 0;
}
