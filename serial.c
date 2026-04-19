#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "serial.h"

#define PORT "\\\\.\\COM5"
#define BAUD_RATE CBR_9600

static void configure_port(HANDLE serial_handle) {
    DCB config = {0};
    COMMTIMEOUTS timeouts = {0};

    config.DCBlength = sizeof(config);
    if (!GetCommState(serial_handle, &config)) {
        printf("[SERIAL] Failed to read COM state\n");
        CloseHandle(serial_handle);
        exit(1);
    }

    config.BaudRate = BAUD_RATE;
    config.ByteSize = 8;
    config.StopBits = ONESTOPBIT;
    config.Parity = NOPARITY;

    if (!SetCommState(serial_handle, &config)) {
        printf("[SERIAL] Failed to configure COM port\n");
        CloseHandle(serial_handle);
        exit(1);
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(serial_handle, &timeouts)) {
        printf("[SERIAL] Failed to configure COM timeouts\n");
        CloseHandle(serial_handle);
        exit(1);
    }
}

HANDLE serial_open(void) {
    HANDLE serial_handle = CreateFileA(PORT,
                                       GENERIC_READ,
                                       0,
                                       NULL,
                                       OPEN_EXISTING,
                                       0,
                                       NULL);

    if (serial_handle == INVALID_HANDLE_VALUE) {
        printf("[SERIAL] Error opening COM\n");
        exit(1);
    }

    configure_port(serial_handle);
    printf("[SERIAL] Driver attached to %s at %d baud\n", PORT, BAUD_RATE);
    return serial_handle;
}

void serial_close(HANDLE serial_handle) {
    if (serial_handle != INVALID_HANDLE_VALUE) {
        CloseHandle(serial_handle);
    }
}

int serial_read_line(HANDLE serial_handle, char *buffer, int buffer_size) {

    char c;
    DWORD bytesRead;
    int i = 0;

    while (1) {

        if (ReadFile(serial_handle, &c, 1, &bytesRead, NULL) && bytesRead > 0) {
            if (c == '\r') {
                continue;
            }

            if (c == '\n') {
                buffer[i] = '\0';
                return 1;
            }

            if (i < buffer_size - 1) {
                buffer[i++] = c;
            }
        }
    }
}
