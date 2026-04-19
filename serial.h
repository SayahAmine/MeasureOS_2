#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>

HANDLE serial_open(void);
void serial_close(HANDLE serial_handle);
int serial_read_line(HANDLE serial_handle, char *buffer, int buffer_size);

#endif
