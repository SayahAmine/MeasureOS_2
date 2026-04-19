#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define PORT "\\\\.\\COM5"
#define T 5

float last_temp = 0;

void Inject_Trait() {
    printf("[UC] Injecting medication...\n");
}

HANDLE open_serial() {
    HANDLE h = CreateFileA(PORT, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (h == INVALID_HANDLE_VALUE) {
        printf("COM ERROR\n");
        exit(1);
    }
    return h;
}

int main() {

    HANDLE hSerial = open_serial();

    char buffer[100];
    char c;
    DWORD bytesRead;
    int i = 0;

    printf("[UC] Running...\n");

    while (1) {

        if (ReadFile(hSerial, &c, 1, &bytesRead, NULL) && bytesRead > 0) {

            if (c == '\n') {
                buffer[i] = '\0';

                if (strncmp(buffer, "TEMP:", 5) == 0) {

                    float temp = atof(buffer + 5);
                    printf("[UC] Temp = %.2f\n", temp);


                    if (last_temp <= 37.0 && temp > 37.0) {
                        printf("[UC] S1 triggered\n");
                        Inject_Trait();
                    }


                    if (temp > 39.0) {
                        printf("[UC] S2 triggered\n");
                        Inject_Trait();
                        Sleep(T * 1000);
                        if (temp>39) {
                            Inject_Trait();
                            printf("2nd injection");
                        }

                    }

                    last_temp = temp;
                }

                i = 0;
            }
            else {
                if (i < 99) buffer[i++] = c;
            }
        }
    }
}